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

extern unsigned ipc_threadstate[6];
extern unsigned ipc_threadstack[6];
extern unsigned ipc_threadspace[6];
extern unsigned ipc_threadedi[6];
extern unsigned ipc_threadeip[6];
extern unsigned ipc_threadesp0[6];

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

    i = 0;

    for (;;)
    {
        i++;
        u32toa(i, s, 10);
        panicWrite(0, 3, s);
        panicWrite(0, 0, "K1:");
    }
}

void task2(void)
{
    unsigned i = 0;
    char s[20];

    i = 1000;

    for (;;)
    {
        i++;
        u32toa(i, s, 10);
        panicWrite(1, 3, s);
        panicWrite(1, 0, "K2:");
    }
}

typedef struct
{
    unt32 esp;
    unt32 eip;
    unsigned space;
    unsigned ipcstate;
    unt32 stack[4096];
} sched_arch_task;

sched_arch_task task[6];

void sched_arch_switch(unsigned current, unsigned next);

void sched_arch_init(void)
{
    unsigned i;
    
    ipc_currentthread = 0;

    ipc_threadstack[0] = ((unsigned)(task[0].stack + 4096));
    ipc_threadstack[1] = ((unsigned)(task[1].stack + 4084));
    ipc_threadstack[2] = ((unsigned)(task[2].stack + 4084));
    ipc_threadstack[3] = ((unsigned)(task[3].stack + 4084));
    ipc_threadstack[4] = ((unsigned)(task[4].stack + 4084));
    ipc_threadstack[5] = ((unsigned)(task[5].stack + 4084));

    ipc_threadesp0[0] = ((unsigned)(task[0].stack + 4096));
    ipc_threadesp0[1] = ((unsigned)(task[1].stack + 4096));
    ipc_threadesp0[2] = ((unsigned)(task[2].stack + 4096));
    ipc_threadesp0[3] = ((unsigned)(task[3].stack + 4096));
    ipc_threadesp0[4] = ((unsigned)(task[4].stack + 4096));
    ipc_threadesp0[5] = ((unsigned)(task[5].stack + 4096));

    ipc_threadeip[0] = ((unsigned)(0x80000000));
    ipc_threadeip[1] = ((unsigned)(0x80000000));
    ipc_threadeip[2] = ((unsigned)(0x80000000));
    ipc_threadeip[3] = ((unsigned)(0x80000000));
    ipc_threadeip[4] = ((unsigned)(0x80000000));
    ipc_threadeip[5] = ((unsigned)(0x80000000));

    ipc_threadspace[0] = 0x00900000;
    ipc_threadspace[1] = 0x00901000;
    ipc_threadspace[2] = 0x00902000;
    ipc_threadspace[3] = 0x00903000;
    ipc_threadspace[4] = 0x00904000;
    ipc_threadspace[5] = 0x00905000;

    ipc_threadstate[0] = 1;
    ipc_threadstate[1] = 1;
    ipc_threadstate[2] = 1;
    ipc_threadstate[3] = 1;
    ipc_threadstate[4] = 1;
    ipc_threadstate[5] = 1;

    for (i = 0; i < 4096; i++)
    {
        task[0].stack[i] = 0xAAAAAAAA;
        task[1].stack[i] = 0xBBBBBBBB;
        task[2].stack[i] = 0xCCCCCCCC;
        task[3].stack[i] = 0xDDDDDDDD;
        task[4].stack[i] = 0xEEEEEEEE;
        task[5].stack[i] = 0xFFFFFFFF;
    }

    for (i = 1; i < 4; i++)
    {
        task[i].stack[4095] = 0x2B;         /* SS                             */
        task[i].stack[4094] = 0x80002000;   /* ESP                            */
        task[i].stack[4093] = 0x00000202;   /* EFLAGS                         */
        task[i].stack[4092] = 0x23;         /* CS                             */
        task[i].stack[4091] = 0x80000000;   /* EIP                            */
        task[i].stack[4090] = 0xAAAAAAAA;   /* EAX                            */
        task[i].stack[4089] = 0xCCCCCCCC;   /* ECX                            */
        task[i].stack[4088] = 0xDDDDDDDD;   /* EDX                            */
        task[i].stack[4087] = 0xBBBBBBBB;   /* EBX                            */
        task[i].stack[4086] = 0x99999999;   /* EBP                            */
        task[i].stack[4085] = 0xEEEEEEEE;   /* ESI                            */
        task[i].stack[4084] = 0xFFFFFFFF;   /* EDI                            */
    }

    logStatus(logSuccess);

    logHex("Task 0 : Entry Point", ((unsigned)(ipc_threadeip[0])));
    logHex("Task 0 : Stack : Start", ((unsigned)(task[0].stack)));
    logHex("Task 0 : Stack : End", ((unsigned)(task[0].stack + 4096)));
    logHex("Task 0 : Stack : Pointer", ((unsigned)(ipc_threadstack[0])));

    logHex("Task 1 : Entry Point", ((unsigned)(ipc_threadeip[1])));
    logHex("Task 1 : Stack : Start", ((unsigned)(task[1].stack)));
    logHex("Task 1 : Stack : End", ((unsigned)(task[1].stack + 4096)));
    logHex("Task 1 : Stack : Pointer", ((unsigned)(ipc_threadstack[1])));

}

/******************************************************************************/
/* sched_arch_switch - Switch to Thread                                       */
/*                                                                            */
/* This is THE function. It took me a long time to figure out how to          */
/* implement it. It looks pretty much the same as the one in Linux. Why did   */
/* it took me such a long time to find the solution? Well basically because I */
/* overlooked one important fact. This function is always called in           */
/* kernel mode. This function is called by the scheduler, which in it's turn  */
/* is called by an interrupt. The interrupt handler saves all the registers   */
/* for us, so we only have to save the point were the thread has to be        */
/* restarted, which is right after this function (well actualy some were at   */
/* the end of this function) and save the kernel stack pointer. We also have  */
/* to do some extra handling to make sure things like the debug registers and */
/* the FPU are stored and restored.                                           */
/******************************************************************************/
void sched_arch_savecontext(void);

void sched_arch_switch(unsigned current, unsigned next)
{
    asm volatile
    (
  
        /* Store the ESP of the current thread.                               */
        "movl %%esp, %0"                                                  "\n\t"
        /* Restore the ESP of the new thread                                  */
        "movl %2, %%esp"                                                  "\n\t"
        /* Store the EIP of the current thread.                               */
        "movl $1f, %1"                                                    "\n\t"
        /* Restore the EIP of the previous thread.                            */
        "pushl %3"                                                        "\n\t"
        /* Switch address spaces.                                             */
        "movl %4, %%eax"                                                  "\n\t"
        "movl %%eax, %%cr3"                                               "\n\t"
        /* Reenable interrupts (I'll have to think about this!!!)             */
        "sti"                                                             "\n\t"
        /* Save some extra parts of the context.                              */
        "ret"                                                             "\n\t"
        /* This is the spawnpoint (all thread continue execution here).       */
        "1:"                                                              "\n\t"
        :
        /* Outputs                                                            */
        /*     0: ESP of the current thread.                                  */
        "=m" (ipc_threadstack[current]),
        /*     1: EIP of the current thread.                                  */
        "=m" (ipc_threadeip[current])
        :
        /* Inputs                                                             */
        /*     2: ESP of the next thread.                                     */
        "m" (ipc_threadstack[next]),
        /*     3: EIP of the next thread.                                     */
        "m" (ipc_threadeip[next]),        
        /*     4: CR3 of the next thread.                                     */
        "m" (ipc_threadspace[next])
    );
}

void sched_arch_savecontext(void)
{
}
