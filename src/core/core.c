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


#include "vesa.c"

#include "ia32/gdt.c"

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
    //cpu_init();   /* Removed this from the core. Need to trim it down.      */
    sig_init();
    //smp_init();   /* Nice, but WAAAAAY too slow when debuggin'.             */
    mm_init();
    sched_init();
    syscall_init();
	space_init();

    //vesa_init();    /* This won't be in the real kernel. Just for testing!    */
    
    arch_gdt_init();

    space_create(1);
    space_create(2);
    space_create(3);
    space_create(4);
    space_switch(0x900000);

    space_map(((word*)(0xFF000000)), 0x80000000);

    logItem("Downloading Root");

    memcpy(0x80000000, 0xFF840000, 16 * 1024);

    space_switch(0x901000);

    space_map(((word*)(0xFF001000)), 0x80000000);


    logItem("Downloading Test");

    memcpy(0x80000000, 0xFF850000, 16 * 1024);

    space_switch(0x902000);

    space_map(((word*)(0xFF002000)), 0x80000000);


    logItem("Downloading Ping");

    memcpy(0x80000000, 0xFF860000, 16 * 1024);

    space_switch(0x903000);

    space_map(((word*)(0xFF003000)), 0x80000000);


    logItem("Downloading Pong");

    memcpy(0x80000000, 0xFF868000, 16 * 1024);

    /* Enable multi-tasking.                                                  */
    logItem("Enabling Multi Tasking");

    asm volatile
    (
        "mov %%eax, %%esp;"
        "sti"
        ::
        "a" (ipc_threadstack[0])
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
