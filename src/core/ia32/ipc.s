/******************************************************************************/
/* Mithrill Core : Inter Process Communication                                */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/


.global _asm_ipc;
.global _ipc_currentthread;
.global _ipc_threadstate;
.global _ipc_threadstack;
.global _ipc_threadspace;
.global _ipc_threadedi;
.global _ipc_threadeip;
.global _ipc_threadesp0;

.global _switch_switch;

.text


/******************************************************************************/
/* eax: send to                         from                                  */
/* ebx: IGNORED                         mr1                                   */
/* edx: receive from        sysexit     UNDEFINED                             */
/* ecx: timeouts            sysexit     UNDEFINED                             */
/* esi: mr0                             mr0                                   */
/* edi: utcb                            PRESERVED                             */
/* ebp: IGNORED                         mr2                                   */
/* esp: IGNORED                         PRESERVED                             */
/*                                                                            */
/* TS0: dead                                                                  */
/* TS1: running                                                               */
/* TS2: waiting                                                               */
/* TS3: sending                                                               */
/******************************************************************************/

_asm_ipc:

    /* Check if we are a receive IPC.                                         */
    cmp $0, %eax;
    je c1;

    /* Retrieve the state of the receiving thread.                            */
    movl _ipc_threadstate(,%eax,4), %ebx;
    cmp $2, %ebx;
    je c1;

    mov $1234, %esi;
    iretl;

c1:

    /* Check if we are a receive IPC.                                         */
    cmp $0, %eax;
    jne c2;

    /* WE SHOULD SWITCH TO THE SCHEDULER THREAD OR SELECT A GOOD THREAD
       JUST SWITCHING TO THREAD 4 WILL DO FOR NOW. THIS WILL EMULATE A CLOSED
       RECEIVE TO THREAD 4.                                                   */
    movl $4, %eax;
    
    /* Hmmm... We're waiting!                                                 */
    movl _ipc_currentthread, %ebp;
    movl $2, _ipc_threadstate(,%ebp,4);

c2:

    /* Save the state of the current thread.                                  */    
    movl _ipc_currentthread, %ebp;
    movl %edi, _ipc_threadedi(,%ebp,4);
    movl %esp, _ipc_threadstack(,%ebp,4);
    movl $spawnpoint, _ipc_threadeip(,%ebp,4);

    /* Restore the state of the next thread.                                  */
    movl _ipc_threadspace(,%eax,4), %ebx;
    movl %ebx, %cr3;
    movl _ipc_threadedi(,%eax,4), %edi;
    movl _ipc_threadstack(,%eax,4), %esp;
    movl _ipc_threadeip(,%eax,4), %ebx;
    movl $1, _ipc_threadstate(,%eax,4);
    
    movl %eax, _ipc_currentthread;
    
    pushl %ebx;
    ret;

spawnpoint:

    iretl;

/******************************************************************************/

_switch_switch:

    /* Save user state.                                                       */
    push %eax;
    push %ecx;
    push %edx;
    push %ebx;
    push %ebp;
    push %esi;
    push %edi;

    movl $0x20, %eax;
    movl $0x20, %edx;
    outb %al, %dx;

    /* Restore the kernel segments.                                           */
    movl $0x18, %eax;
    movl %eax, %ds;
    movl %eax, %es;
    movl %eax, %fs;
    movl %eax, %gs;

    /* Do we need to save the stack pointer?                                  */
    movl _ipc_currentthread, %ebp;
    movl %esp, _ipc_threadstack(,%ebp,4);

    /* Determine the next thread.                                             */
    incl _ipc_currentthread;
    cmpl $2, _ipc_currentthread;
    jb switch_1;
    movl $0, _ipc_currentthread;

switch_1:

    /* Switch kernel stacks.                                                  */
    movl _ipc_currentthread, %ebp;
    movl _ipc_threadstack(,%ebp,4), %esp;

    /* Change ESP0.                                                           */
    movl _ipc_threadesp0(,%ebp,4), %eax;
    movl %eax, 0xFF490004;

    /* Switch address space.                                                  */
    movl _ipc_threadspace(,%ebp,4), %eax;
    movl %eax, %cr3;

    /* Restore the user segments.                                             */
    movl $0x2B, %eax;
    movl %eax, %ds;
    movl %eax, %es;
    movl %eax, %fs;
    movl %eax, %gs;

    /* Restore user state.                                                    */
    pop %edi;
    pop %esi;
    pop %ebp;
    pop %ebx;
    pop %edx;
    pop %ecx;
    pop %eax;

    iretl;

.data

em: .asciz "IPC FAILURE: THREAD NOT WAITING!";
abc: .asciz "EVERYTHING GOES!";
mes: .asciz "Current Thread";
mes2: .asciz "New Thread";
m_esp: .asciz "ESP";
m_stack: .asciz "Stack Data";

_ipc_currentthread: .long 0x00000000;
_ipc_threadstate:   .long 0;
                    .long 1;
                    .long 2;
                    .long 3;
                    .long 4;
                    .long 5;
_ipc_threadstack:   .long 0;
                    .long 1;
                    .long 2;
                    .long 3;
                    .long 4;
                    .long 5;
_ipc_threadspace:   .long 0;
                    .long 1;
                    .long 2;
                    .long 3;
                    .long 4;
                    .long 5;
_ipc_threadedi:     .long 0;
                    .long 1;
                    .long 2;
                    .long 3;
                    .long 4;
                    .long 5;
_ipc_threadeip:     .long 0;
                    .long 1;
                    .long 2;
                    .long 3;
                    .long 4;
                    .long 5;
_ipc_threadesp0:    .long 0;
                    .long 1;
                    .long 2;
                    .long 3;
                    .long 4;
                    .long 5;


