/******************************************************************************/
/* Symetric Multi-Processing                                                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include "ia32/smp.c"

/******************************************************************************/
/* smp_init - Initialize SMP Management                                       */
/*                                                                            */
/* SMP Management is initialized by searching for the MP Floating Pointer     */
/* Structure and, if applicable, the MP Configuration Table. Next, the Local  */
/* APIC and I/O APICs are configured. The AP booted using trampoline code.    */
/* OS structures are updated to reflect the system configuration and control  */
/* is returned to the system.                                                 */
/******************************************************************************/
void smp_init(void)
{
   logItem("Initializing SMP Management");

    /* Until we get real SMP, just fake the core into thinking that there is  *
     * only one CPU.                                                          */

/*    cpu_count = 1;
    cpu_list = heap_alloc(sizeof(smp_cpu));

    cpu_list[0].hid = 0;
    cpu_list[0].status = smp_cpu_status_idle;

    logStatus(logSuccess);

    logNote("SMP support has been disabled for this release!");
    logSubItem("Processor Count", "1");*/

    smp_arch_init();
}
