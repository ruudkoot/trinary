/******************************************************************************/
/* Trinary Operating System Core                                              */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include "compiler.c"

#include "lib/lib.c"

#include "rtl.c"
#include "heap.c"

#include "lib/container.c"

#include "log.c"
#include "debug.c"

#include "schedule.c"

#include "system.c"
#include "cpu.c"
#include "memory.c"
#include "signal.c"
#include "smp.c"



#include "pci/pci.c"

void sigSwitch(void);

/* :: TEMPORARY :: BEGIN :: */
    void task1(void);
    void task2(void);
    void task3(void);
    void task4(void);
    void task5(void);
    void task6(void);
    void task7(void);
    void task8(void);
    void task9(void);
    void task10(void);
/* :: TEMOPRARY ::  END  :: */

int cmain(void)
{
    char s[20];
    unsigned stop, time, i;
    
    /* :: TEMPORARY :: BEGIN :: */
        logStatus(logSuccess);
    /* :: TEMOPRARY ::  END  :: */

    /* Initialize Heap Management */
        logItem("Initializing Heap Management");
        heap_init(0xC0100000);
        logStatus(logSuccess);

    /* Initialize System Management */
        logItem("Initializing System Management");
        sysInit();
        logStatus(logSuccess);

    /* Initialize Processor Management */
        logItem("Initializing Processor Management");
        prcInit();

    /* Initialize Signal Management */
        logItem("Initializing Signal Management");
        sig_init();
        logStatus(logSuccess);

    /* Initialize SMP Management */
        logItem("Initializing SMP Management");
        logStatus(logSuccess);
        smp_init();
        
    /* Initialize Memory Management */
        logItem("Initializing Memory Management");
        mmInit();
        logStatus(logSuccess);

    /* :: TEMPORARY :: BEGIN :: */
        logNote("The following parameters were set at compile time!");
        logSubItem("Physical Memory", "16378 kB");
        logSubItem("Reserved Memory", "1024 kB");

        //pci_probe();
        
        for (i = 1; i < 11; i++)
        {   task[i].eax = i+1;
            task[i].ebx = i+1;
            task[i].ecx = i+1;
            task[i].edx = i+1;
            task[i].esi = i+1;
            task[i].edi = i+1;
            task[i].ebp = (unsigned)(task[i].stack)+256*4-1;
            task[i].esp = (unsigned)(task[i].stack)+256*4-1;
            task[i].efl = 0x00000200;       //IOPL = 0 / IF = 1
        }

        task[1].stack[255] = 0x00000200;
        task[1].stack[254] = 0x0008;
        task[1].stack[253] = ((unsigned)(task1));
        task[1].stack[252] = 0xAAAAAAAA;
        task[1].stack[251] = 0xBBBBBBBB;
        task[1].stack[250] = 0xCCCCCCCC;
        task[1].stack[249] = 0xDDDDDDDD;
        task[1].stack[248] = 0xEEEEEEEE;
        task[1].stack[247] = 0xFFFFFFFF;
        task[1].stack[246] = 0x99999999;
        task[1].esp = ((unsigned)(task[1].stack + 246));

        task[2].stack[255] = 0x00000200;
        task[2].stack[254] = 0x0008;
        task[2].stack[253] = ((unsigned)(task2));
        task[2].stack[252] = 0xAAAAAAAA;
        task[2].stack[251] = 0xBBBBBBBB;
        task[2].stack[250] = 0xCCCCCCCC;
        task[2].stack[249] = 0xDDDDDDDD;
        task[2].stack[248] = 0xEEEEEEEE;
        task[2].stack[247] = 0xFFFFFFFF;
        task[2].stack[246] = 0x99999999;
        task[2].esp = ((unsigned)(task[2].stack + 246));

        XXX = task[2].esp;
        
        sched_arch_init();

        asm volatile ("mov %%eax, %%esp; jmp _task1" :: "a" (task[1].esp));

        for (;;) asm volatile ("hlt");
    /* :: TEMOPRARY ::  END  :: */

}

/* :: TEMPORARY :: BEGIN :: */
void task1(void)
{
    static unsigned i = 0;
    char s[20];

    asm volatile ("sti");
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(2, 4, s);
    }
}

void task2(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(3, 4, s);
    }
}

void task3(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(4, 4, s);
    }
}

void task4(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(5, 4, s);
    }
}

void task5(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(6, 4, s);
    }
}

void task6(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(7, 4, s);
    }
}

void task7(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(8, 4, s);
    }
}

void task8(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(9, 4, s);
    }
}

void task9(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(10, 4, s);
    }
}

void task10(void)
{
    static unsigned i = 0;
    char s[20];
    
    for (;;)
    {
        i++;
        itoa(i, s, 10);
        panicWrite(11, 4, s);
    }
}
/* :: TEMOPRARY ::  END  :: */

