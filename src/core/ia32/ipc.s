/******************************************************************************/
/* Inter Process Communication                                                */
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
    
    /* Retreive the state of the receiving thread.                            */
    movl _ipc_threadstate(,%eax,4), %ebx;
    
    /* Make sure it is waiting to receive.                                    */
    cmpl $2, %ebx;
    jne _asm_nwait;

    /* Let the current thread wait.                                           */
    movl _ipc_currentthread, %ebp;
    movl $2, _ipc_threadstate(,%ebp,4);

    /* Save ESP and EDI of the current thread.                                */
    movl %esp, _ipc_threadstack(,%ebp,4);
    movl %edi, _ipc_threadedi(,%ebp,4);

    /* Restore ESP and EDI of the receiver thread.                            */
    movl _ipc_threadstack(,%eax,4), %esp;
    movl _ipc_threadedi(,%eax,4), %edi;

    /* Store EIP of the current thread.                                       */
    movl $spawnpoint, _ipc_threadeip(,%ebp,4);

    /* Switch Addres Space.                                                   */
    movl _ipc_threadspace(,%eax,4), %ebp;
    movl %ebp, %cr3;

    /* Restore EIP of the receiver thread.                                    */
    movl _ipc_threadeip(,%eax,4), %ebx;
    pushl %ebx;
    ret;

    /* We shouldn't spawn here!                                               */
    cli;
    hlt;
    
spawnpoint:

    iretl;

_asm_nwait:
    push $em;
    call _panic;

.data

em: .asciz "IPC FAILURE: THREAD NOT WAITING!";

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
