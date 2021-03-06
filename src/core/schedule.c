/******************************************************************************/
/* Scheduler                                                                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

extern unsigned ipc_currentthread;

#include "ia32/schedule.c"

void sched_init(void)
{
    logItem("Initailizing Task Management");
    sched_arch_init();
}
