/******************************************************************************/
/* Scheduler                                                                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include "arch/ia32/schedule.c"

void sched_init(void)
{
    logItem("Initailizing Task Management");
    sched_arch_init();
}

/******************************************************************************/
/* sched_arch_shedule - Schedule Thread for Execution                         */
/*                                                                            */
/* This function selects a new (the best) thread for scheduling and starts    */
/* executing it. This function can be called anywhere in the kernel [1]. The  */
/* thread that called the function will resume execution at the point right   */
/* after the call to this function.                                           */
/*                                                                            */
/* The scheduler uses quite a compicated algorithm to select the best thread. */
/* to save space in the source code an make reading easy I've documented it   */
/* a separate document (doc/core/scheduler.thml). In short the scheduler must */
/* be able to make this operating system a true real-time system, maek sure   */
/* interrupt latencies are low, prevent starvation of processes, make sure    */
/* threads are scheduled in such a way that caches don't become dirty,        */
/* correct for unbalanced SMP systems, pair the best threads on Hyper         */
/* Threading processors, ...                                                  */
/*                                                                            */
/* As you can immedeately see this scheduler is quite a bit more complex that */
/* Linux' (which just implements a round robin scheduler with some support    */
/* for real time threads).                                                    */
/*                                                                            */
/* [1] Although it CAN be called from anywere in the kernel it SHOULD NOT be  */
/*     called from every random spot. For example it would be a bad idea to   */
/*     reschedule when your holding a spinlock.                               */
/*                                                                            */
/* THE REAL SCHEDULER ISN'T IMPLEMENTED YET!!!                                */
/******************************************************************************/
void sched_schedule(void)
{
    unsigned previous;

    previous = TEMP_sched_current;
    
    TEMP_sched_current++;
    if (TEMP_sched_current > 2) TEMP_sched_current = 1;

    sched_arch_switch(&(task[previous]), (&task[TEMP_sched_current]));
}
