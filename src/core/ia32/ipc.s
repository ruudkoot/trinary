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

    /* Restore the kernel segments.                                           */
    movl $0x18, %ebx;
    movl %ebx, %ds;
    movl %ebx, %es;
    movl %ebx, %fs;
    movl %ebx, %gs;

    

_asm_ipc_return:

    /* Restore the user segments.                                             */
    movl $0x2B, %ebx;
    movl %ebx, %ds;
    movl %ebx, %es;
    movl %ebx, %fs;
    movl %ebx, %gs;

    iretl;

/******************************************************************************/

_switch_switch:

    /* Save user state.                                                       */
    movl %eax, -4(%esp);
    movl %ecx, -8(%esp);
    movl %edx, -12(%esp);
    movl %ebx, -16(%esp);
    movl %ebp, -20(%esp);
    movl %esi, -24(%esp);
    movl %edi, -28(%esp);

    /* Clear the interrupt controller.                                        */
    movl $0x20, %eax;
    movl $0x20, %edx;
    outb %al, %dx;

    /* Restore the kernel segments.                                           */
    movl $0x18, %eax;
    movl %eax, %ds;
    movl %eax, %es;
    movl %eax, %fs;
    movl %eax, %gs;

    /* Display the current thread.                                            */
    xorl %eax, %eax;
    xorl %ebx, %ebx;
    addl $0xB80A0, %eax;
    addl $0x1F30, %ebx;
    addl _ipc_currentthread, %ebx;
    movw %bx, (,%eax);

    /* Save the stack pointer.                                                */
    movl _ipc_currentthread, %ebp;
    movl %esp, _ipc_threadstack(,%ebp,4);

next_thread:

    /* Determine the next thread.                                             */
    incl _ipc_currentthread;
    cmpl $4, _ipc_currentthread;
    jb switch_1;
    movl $0, _ipc_currentthread;

switch_1:

    movl _ipc_currentthread, %ebp;

    /* Display the status of the threads.                                     */
    xorl %eax, %eax;
    xorl %ebx, %ebx;
    addl _ipc_currentthread, %eax;
    shll $1, %eax;
    addl $0xB8000, %eax;
    addl $0x1F30, %ebx;
    addl _ipc_threadstate(,%ebp,4), %ebx;
    movw %bx, (,%eax);

    /* Make sure it is runnable.                                              */
    movl _ipc_threadstate(,%ebp,4), %eax;
    cmpl $2, %eax; 
    je next_thread;

    /* Display the selected thread.                                           */
    xorl %eax, %eax;
    xorl %ebx, %ebx;
    addl $0xB80A2, %eax;
    addl $0x1F30, %ebx;
    addl _ipc_currentthread, %ebx;
    movw %bx, (,%eax);

standard_switch:

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
    movl -4(%esp), %eax;
    movl -8(%esp), %ecx;
    movl -12(%esp), %edx;
    movl -16(%esp), %ebx;
    movl -20(%esp), %ebp;
    movl -24(%esp), %esi;
    movl -28(%esp), %edi;

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


