/******************************************************************************/
/* Scheduler                                                                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This module implements the preemptive scheduler. It's pretty simple at the */
/* moment, but we can implement some nifty algorithms to make it much more    */
/* powerful. You should think of dynamic quantums, real-time support,         */
/* optimized SMP and HyperThreading support, ...                              */
/******************************************************************************/

extern unsigned ipc_threadstate[6];
extern unsigned ipc_threadstack[6];
extern unsigned ipc_threadspace[6];
extern unsigned ipc_threadedi[6];
extern unsigned ipc_threadeip[6];
extern unsigned ipc_threadesp0[6];

typedef struct
{
    unt32 esp;
    unt32 eip;
    unsigned space;
    unsigned ipcstate;
    unt32 stack[4096];
} sched_arch_task;

sched_arch_task task[6];

void sched_arch_init(void)
{
    unsigned i;
    
    ipc_currentthread = 0;

    ipc_threadstack[0] = ((unsigned)(task[0].stack + 4096));
    ipc_threadstack[1] = ((unsigned)(task[1].stack + 4091));
    ipc_threadstack[2] = ((unsigned)(task[2].stack + 4091));
    ipc_threadstack[3] = ((unsigned)(task[3].stack + 4091));
    ipc_threadstack[4] = ((unsigned)(task[4].stack + 4091));
    ipc_threadstack[5] = ((unsigned)(task[5].stack + 4091));

    ipc_threadesp0[0] = ((unsigned)(task[0].stack + 4096));
    ipc_threadesp0[1] = ((unsigned)(task[1].stack + 4096));
    ipc_threadesp0[2] = ((unsigned)(task[2].stack + 4096));
    ipc_threadesp0[3] = ((unsigned)(task[3].stack + 4096));
    ipc_threadesp0[4] = ((unsigned)(task[4].stack + 4096));
    ipc_threadesp0[5] = ((unsigned)(task[5].stack + 4096));

    ipc_threadeip[0] = ((unsigned)(0x80000000));
    ipc_threadeip[1] = ((unsigned)(0x80000000));
    ipc_threadeip[2] = ((unsigned)(0x80000000));
    ipc_threadeip[3] = ((unsigned)(0x80000000));
    ipc_threadeip[4] = ((unsigned)(0x80000000));
    ipc_threadeip[5] = ((unsigned)(0x80000000));

    ipc_threadspace[0] = 0x00900000;
    ipc_threadspace[1] = 0x00901000;
    ipc_threadspace[2] = 0x00902000;
    ipc_threadspace[3] = 0x00903000;
    ipc_threadspace[4] = 0x00904000;
    ipc_threadspace[5] = 0x00905000;

    ipc_threadstate[0] = 1;
    ipc_threadstate[1] = 1;
    ipc_threadstate[2] = 1;
    ipc_threadstate[3] = 1;
    ipc_threadstate[4] = 1;
    ipc_threadstate[5] = 1;

    for (i = 0; i < 4096; i++)
    {
        task[0].stack[i] = 0xAAAAAAAA;
        task[1].stack[i] = 0xBBBBBBBB;
        task[2].stack[i] = 0xCCCCCCCC;
        task[3].stack[i] = 0xDDDDDDDD;
        task[4].stack[i] = 0xEEEEEEEE;
        task[5].stack[i] = 0xFFFFFFFF;
    }

    for (i = 1; i < 4; i++)
    {
        task[i].stack[4095] = 0x2B;         /* SS                             */
        task[i].stack[4094] = 0x80002000;   /* ESP                            */
        task[i].stack[4093] = 0x00003202;   /* EFLAGS                         */
        task[i].stack[4092] = 0x23;         /* CS                             */
        task[i].stack[4091] = 0x80000000;   /* EIP                            */
        task[i].stack[4090] = 0xAAAAAAAA;   /* EAX                            */
        task[i].stack[4089] = 0xCCCCCCCC;   /* ECX                            */
        task[i].stack[4088] = 0xDDDDDDDD;   /* EDX                            */
        task[i].stack[4087] = 0xBBBBBBBB;   /* EBX                            */
        task[i].stack[4086] = 0x99999999;   /* EBP                            */
        task[i].stack[4085] = 0xEEEEEEEE;   /* ESI                            */
        task[i].stack[4084] = 0xFFFFFFFF;   /* EDI                            */
    }

    logStatus(logSuccess);

    logHex("Task 0 : Entry Point", ((unsigned)(ipc_threadeip[0])));
    logHex("Task 0 : Stack : Start", ((unsigned)(task[0].stack)));
    logHex("Task 0 : Stack : End", ((unsigned)(task[0].stack + 4096)));
    logHex("Task 0 : Stack : Pointer", ((unsigned)(ipc_threadstack[0])));

    logHex("Task 1 : Entry Point", ((unsigned)(ipc_threadeip[1])));
    logHex("Task 1 : Stack : Start", ((unsigned)(task[1].stack)));
    logHex("Task 1 : Stack : End", ((unsigned)(task[1].stack + 4096)));
    logHex("Task 1 : Stack : Pointer", ((unsigned)(ipc_threadstack[1])));

}
