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
/* a separate document (doc/core/scheduler.html). In short the scheduler must */
/* be able to make this operating system a true real-time system, make sure   */
/* interrupt latencies are low, prevent starvation of processes, make sure    */
/* threads are scheduled in such a way that caches don't become dirty,        */
/* correct for unbalanced SMP systems, pair the best threads on Hyper         */
/* Threading processors, ...                                                  */
/*                                                                            */
/* As you can immediately see this scheduler is quite a bit more complex that */
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
    unsigned i;

    unsigned char* v;

    previous = ipc_currentthread;
    
    for (i = 0; i < 6; i++)
    {
        v = (unsigned char*)(0xB8000 + 2 * (56 + i));
        *v = ipc_threadstate[i] + '0';
        v++;
        *v = 0x17;
    }
    
    do
    {
        ipc_currentthread++;
        if (ipc_currentthread > 5) ipc_currentthread = 0;
    } while (ipc_threadstate[ipc_currentthread] != 1);


    sched_arch_switch(previous, ipc_currentthread);
}
