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
        
        logItem("Initailizing Task Management");
        sched_arch_init();
     

        asm volatile
        (
            "mov %%eax, %%esp;"
            "mov $0xFFFFFFFF, %%eax;"
            "mov $0xFFFFFFFF, %%ebx;"
            "mov $0xFFFFFFFF, %%ecx;"
            "mov $0xFFFFFFFF, %%edx;"
            "mov $0xFFFFFFFF, %%esi;"
            "mov $0xFFFFFFFF, %%edi;"
            "mov $0xFFFFFFFF, %%ebp;"
            "sti"
            ::
            "a" (task[0].esp)
        );

        for (;;) asm volatile ("hlt");
    /* :: TEMOPRARY ::  END  :: */

}
