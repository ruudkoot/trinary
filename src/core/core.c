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

#include "lib.c"

#include "lib/container.c"

#include "log.c"
#include "debug.c"

#include "heap.c"

#include "schedule.c"

#include "system.c"
#include "cpu.c"
#include "memory.c"
#include "signal.c"
#include "smp.c"

/******************************************************************************/
/* cmain - Entry Point                                                        */
/*                                                                            */
/* This is the first entry point. You should only do basic core               */
/* initialization here, because multi-tasking isn't enabled yet.              */
/******************************************************************************/
void cmain(void)
{
    /* Check the previous item to indicated the core was booted correctly.    */
    logStatus(logSuccess);

    /* Initialize the basic core modules.                                     */
    heap_init();
    sys_init();
    cpu_init();
    sig_init();
    smp_init();
    mm_init();
    sched_init();

    /* Enable multi-tasking.                                                  */

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
}

/******************************************************************************/
/* dmain - Multi-Tasking Entry Point                                          */
/*                                                                            */
/* This is the second entry point of the core. Multi-Tasking is enabled for   */
/* this one.                                                                  */
/******************************************************************************/
void dmain(void)
{
}
