/******************************************************************************/
/* Scheduler                                                                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This module implements the preemptive scheduler. It's pretty simple at the */
/* moment, but we can implement some nifty algorithms to make it much more    */
/* powerful. You should think of dynamic quantums, real-time support,         */
/* optimized SMP and HyperThreading support, ...                              */
/******************************************************************************/

unsigned TEMP_sched_current;
unsigned TEMP_ESP;

void task0(void);
void task1(void);
void task2(void);

void task0(void)
{
    asm volatile ("cli; hlt;");
    panic("EXECUTING TASK 0!!!");
}

void task1(void)
{
    unsigned i = 0;
    char s[20];

    i = 33333;

    for (;;)
    {
        i++;
        u32toa(i, s, 10);
        panicWrite(2, 4, s);
    }
}

void task2(void)
{
    unsigned i = 0;
    char s[20];

    i = 33333;
    
    for (;;)
    {
        i+=2;
        u32toa(i, s, 10);
        panicWrite(3, 4, s);
    }
}

typedef struct
{
    unt32 esp;
    unt32 eip;
    unt32 stack[4096];
} sched_arch_task;

sched_arch_task task[3];

/**/ void pci_probe(void); /**/

void sched_arch_switch(sched_arch_task* current, sched_arch_task* next);

void sched_arch_init(void)
{
    unsigned i;
    
    TEMP_sched_current = 0;

    task[0].esp = ((unsigned)(task[0].stack + 4096));
    task[1].esp = ((unsigned)(task[1].stack + 4096));
    task[2].esp = ((unsigned)(task[2].stack + 4096));


    
    task[0].eip = ((unsigned)(task0));
    task[1].eip = ((unsigned)(task1));
    task[2].eip = ((unsigned)(task2));

    for (i = 0; i < 4096; i++)
    {
        task[0].stack[i] = 0xAAAAAAAA;
        task[1].stack[i] = 0xBBBBBBBB;
        task[2].stack[i] = 0xCCCCCCCC;
    }

    logStatus(logSuccess);

    logHex("Task 1 : Entry Point", ((unsigned)(task[1].eip)));
    logHex("Task 1 : Stack : Start", ((unsigned)(task[1].stack)));
    logHex("Task 1 : Stack : End", ((unsigned)(task[1].stack + 4096)));
    logHex("Task 1 : Stack : Pointer", ((unsigned)(task[1].esp)));

}

/******************************************************************************/
/* sched_arch_switch - Switch to Thread                                       */
/*                                                                            */
/* This is THE function. It took me a long time to figure out how to          */
/* implement it. It looks pretty much the same at the one in Linux. Why did   */
/* took me such a long time to find the solution? Well basically because I    */
/* overlooked one important fact. This function is always called in           */
/* kernel mode. Thsi function is called by the ascheduler, which in it's turn */
/* is called by an interrupt. The interrupt handler saves all the registers   */
/* for us, so we only have to save the point were the thread has to be        */
/* restarted, which is right after this function (well actualy some were at   */
/* the end of this function) and save the kernel stack pointer. We also have  */
/* to do some extra handling to make sure things like the debug registers and */
/* the FPU are stored and restored.                                           */
/******************************************************************************/
void sched_arch_savecontext(void);

void sched_arch_switch(sched_arch_task* current, sched_arch_task* next)
{
    asm volatile
    (
        "pushl %%esi; pushl %%edi; pushl %%ebp;"
        /* Store the ESP of the current thread.                               */
        "movl %%esp, %0"                                                  "\n\t"
        /* Restore the ESP of the new thread                                  */
        "movl %2, %%esp"                                                  "\n\t"
        /* Store the EIP of the current thread.                               */
        "movl $1f, %1"                                                    "\n\t"
        /* Restore the EIP of the previous thread.                            */
        "pushl %3"                                                        "\n\t"
        /* Reenable interrupts (I'll have to think about this!!!)             */
        "sti"                                                             "\n\t"
        /* Save some extra parts of the context.                              */
        "ret"                                                             "\n\t"
        /* This is the spawnpoint (all thread continue execution here).       */
        "1:"                                                              "\n\t"
        "popl %%ebp; popl %%edi; popl %%esi;"
        :
        /* Outputs                                                            */
        /*     0: ESP of the current thread.                                  */
        "=m" (current->esp),
        /*     1: EIP of the current thread.                                  */
        "=m" (current->eip)
        :
        /* Inputs                                                             */
        /*     2: ESP of the next thread.                                     */
        "m" (next->esp),
        /*     3: EIP of the next thread.                                     */
        "m" (next->eip)        
    );
}

void sched_arch_savecontext(void)
{
}