/******************************************************************************/
/* Mithrill Core : Inter Process Communication                                */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* Rudy Koot : Clean                                                          */
/* This is a clean implementation of the IPC set written by Rudy Koot. This   */
/* is a template for all other implementations for that set. It has not been  */
/* optimized and written to be easily understandable.                         */
/*                                                                            */
/* Rudy Koot : P6                                                             */
/* This implementaion of Rudy's set has been tuned for the P6 architecture.   */
/* Most branches have been eliminated through the use of conditional moves.   */
/******************************************************************************/

.global _asm_ipc;
.global _switch_switch;
.global _int_entry;

.global _ipc_currentthread;
.global _ipc_schedulethread;

.global _ipc_threadstate;
.global _ipc_threadstack;
.global _ipc_threadspace;
.global _ipc_threadedi;
.global _ipc_threadeip;
.global _ipc_threadesp0;

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

    /* If we are sending make sure the receiver can receive.                  */
    cmpl $0, %eax;
    je _asm_set_receive;
    movl _ipc_threadstate(,%eax,4), %ebx;
    cmpl $2, %ebx;
    jne _asm_send_error;

_asm_set_receive:

    /* If we are receiving go into the receive state.                         */
    cmpl $0, %edx;
    je _asm_send_unwait;

    /**************************************************************************/
    
    /* If we are waiting for an interrupt return if it is already pending.    */
    cmpl $5, %edx;
    jne _asm_set_continue;

    cmpl $0, _int_flag14;
    je _asm_set_continue;

    movl $0, _int_flag14;
    jmp _asm_ipc_return;


xxx: .asciz "IPC: INTERRUPT 14 PENDING!";
    
    /**************************************************************************/

_asm_set_continue:

    movl _ipc_currentthread, %ebp;
    movl $2, _ipc_threadstate(,%ebp,4);    

_asm_send_unwait:

    /* If we are sending let the target stop waiting.                         */
    cmpl $0, %eax;
    je _asm_thread_select;

    movl $1, _ipc_threadstate(,%eax,4);

_asm_thread_select:
    
    /* DOESNT WORK ENTIERLY YET, JUST ENOUGH FOR ping AND pong!               */
    /* AND SPECIAL HANDLING FOR root!                                         */

    /* If we are not sending select a thread to switch to.                    */
    
    /**************************************************************************/
    movl %eax, %ebp;

    cmpl $0, %eax;
    jne _asm_ipc_switch;

    movl %edx, %ebp;

    cmpl $5, %ebp;
    jne _asm_ipc_switch;

    movl $1, %ebp;
    /**************************************************************************/

_asm_ipc_switch:

    /* Switch the address space.                                              */
    movl _ipc_threadspace(,%ebp,4), %ebx;
    movl %ebx, %cr3;

    /* Switch ESP0.                                                           */
    movl _ipc_threadesp0(,%ebp,4), %ebx;
    movl %ebx, 0xFF490004;

    /* Update _ipc_currentthread.                                             */
    movl %ebp, _ipc_currentthread;

    /* Switch Kernel Stack.                                                   */
    movl _ipc_threadesp0(,%ebp,4), %esp;
    subl $20, %esp;

_asm_ipc_restore:

    /* If we are not sending restore the registers.                           */
    cmpl $0, %eax;
    jne _asm_ipc_return;

    movl -4(%esp), %eax;
    movl -8(%esp), %ecx;
    movl -12(%esp), %edx;
    movl -16(%esp), %ebx;
    movl -20(%esp), %ebp;
    movl -24(%esp), %esi;
    movl -28(%esp), %edi;

_asm_ipc_return:

    /* Restore the user segments.                                             */
    movl $0x2B, %ebx;
    movl %ebx, %ds;
    movl %ebx, %es;
    movl %ebx, %fs;
    movl %ebx, %gs;

    iretl;

_asm_send_error:

    movl $1234, %esi;

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

    /* Change ESP0.                                                           */
    movl _ipc_threadesp0(,%ebp,4), %eax;
    movl %eax, 0xFF490004;

    /* Switch Kernel Stack.                                                   */
    movl %eax, %esp;
    subl $20, %esp;

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

/******************************************************************************/

_int_entry:

    /* Save user state.                                                       */
    movl %eax, -4(%esp);
    movl %ecx, -8(%esp);
    movl %edx, -12(%esp);
    movl %ebx, -16(%esp);
    movl %ebp, -20(%esp);
    movl %esi, -24(%esp);
    movl %edi, -28(%esp);

    /* PRINT INTERRUPT COUNT!                                                 */
    incb 0xB8098;
    
    /* HARDISK INTERRUPT ACKNOWLEDGE!                                         */
    movw $0x1F7, %dx;
    inb %dx, %al;
    
    /* Clear the interrupt controllers.                                       */
    movl $0x20, %eax;
    movl $0xA0, %edx;
    outb %al, %dx;

    movl $0x20, %edx;
    outb %al, %dx;

    /* Restore the kernel segments.                                           */
    movl $0x18, %eax;
    movl %eax, %ds;
    movl %eax, %es;
    movl %eax, %fs;
    movl %eax, %gs;

    /* Update currentthread.                                                  */
    movl $0, %ebp;
    movl %ebp, _ipc_currentthread;

    /* Make sure it is waiting.                                               */
    movl _ipc_threadstate(,%ebp,4), %eax;
    cmpl $2, %eax; 
    jne _int_panic;

    /* Let the thread stop waiting.                                           */
    movl $1, _ipc_threadstate(,%ebp,4);

    /* Change ESP0.                                                           */
    movl _ipc_threadesp0(,%ebp,4), %eax;
    movl %eax, 0xFF490004;

    /* Switch Kernel Stack.                                                   */
    movl %eax, %esp;
    subl $20, %esp;

    /* Switch address space.                                                  */
    movl _ipc_threadspace(,%ebp,4), %eax;
    movl %eax, %cr3;

    /* Restore the user segments.                                             */
    movl $0x2B, %eax;
    movl %eax, %ds;
    movl %eax, %es;
    movl %eax, %fs;
    movl %eax, %gs;

    iretl;

_int_panic:

    /* Raise the interrupt flag.                                              */
    movl $1, _int_flag14;

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

_int_panicmessage: .asciz "PANIC: INTERRUPT HANDLER NOT WAITING!";

_int_flag14:        .long 0x00000000;

_ipc_currentthread: .long 0x00000000;
_ipc_schedulethread:.long 0x00000000;
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



