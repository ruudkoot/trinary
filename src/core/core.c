/******************************************************************************/
/* Trinary Operating System Core                                              */
/* Copyright (c) 2004, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

extern kippointer;

void cmain(void);
void dmain(void);
void kdb_enter(void);

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
#include "ia32/api.c"


#include "vesa.c"

#include "ia32/gdt.c"
#include "ia32/tss.c"

#include "kdb.c"

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

    arch_api_init();

    //vesa_init();    /* This won't be in the real kernel. Just for testing!  */
    
    arch_gdt_init();
    arch_tss_init();

    logStatus(logSuccess);

    /* Enable multi-tasking.                                                  */
    logItem("Enabling Multi Tasking");

    arch_tss->esp0 = ipc_threadesp0[0];

    logHex("0xD001000", (*(unt32*)(0xD0001000)));
    logHex("0xD000FFC", (*(unt32*)(0xD0000FFC)));
    logHex("0xD000FF8", (*(unt32*)(0xD0000FF8)));
    logHex("0xD000FF4", (*(unt32*)(0xD0000FF4)));
    logHex("0xD000FF0", (*(unt32*)(0xD0000FF0)));
    logHex("0xD000FEC", (*(unt32*)(0xD0000FEC)));
    logHex("0xD000FE8", (*(unt32*)(0xD0000FE8)));

    logStatus(logSuccess);

    asm volatile
    (
        "movl $0xD0000FEC, %%esp;"
        "movl $0x2B, %%eax;"
        "movl %%eax, %%ds;"
        "movl %%eax, %%es;"
        "movl %%eax, %%fs;"
        "movl %%eax, %%gs;"
        "iretl;"
        ::
        "a" (ipc_threadstack[0])
    );

    logStatus(logSuccess);

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

