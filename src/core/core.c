/******************************************************************************/
/* Trinary Operating System Core                                              */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void cmain(void);
void dmain(void);

#define NOMEM
#include "../lib/config.c"
#include "../lib/lib.c"

#include "log.c"
#include "debug.c"

void sys_arch_timer_setfrequency(unt8 timer, unt32 frequency);


#include "heap.c"
#include "schedule.c"

#include "system.c"
//#include "cpu.c"
#include "memory.c"
#include "space.c"
#include "signal.c"
#include "smp.c"


#include "syscall.c"

/******************************************************************************/

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

    logSubItem("Compiler", COMPILER);

    /* Initialize the basic core modules.                                     */
    heap_init();
    sys_init();
    //cpu_init();
    sig_init();
    //smp_init();
    mm_init();
    sched_init();
    syscall_init();
	space_init();

    space_create(1);
    space_create(1);

    space_switch(0x500000);
    space_switch(0x501000);

    space_map(((word*)(0xFF000000)), (word)0x80000000);

    space_switch(0x500000);

    /* Enable multi-tasking.                                                  */
    logItem("Enabling Multi Tasking");

    asm volatile
    (
        "mov %%eax, %%esp;"
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
    logStatus(logSuccess);
    
    for (;;) asm volatile ("hlt");
}
