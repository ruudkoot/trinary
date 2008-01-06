/******************************************************************************/
/* System Initialization : Entry Point                                        */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

.arch i386, jumps;
.code16gcc;
.text;
.globl entry_start;

/******************************************************************************/
/* entry_start -                                                              */
/*                                                                            */
/* This function setups up the environment, and checks if we really have a    */
/* 32-bit processor.                                                          */
/******************************************************************************/

entry_start:

    /* Setup a real-mode stack, so interrupt can occur safely.                */
    cli;
    movw %cs, %ax;
    movw %ax, %ss;
    xorw %sp, %sp;
    sti;

    movw %ax, %ds;
    movw %ax, %es;

    /* Check if really heave a 32-bit processor. We do this by checking if we *
     * can modify the IOPL bits in the FLAGS register.                        */
    pushf;
    popw %ax;
    orw $0x3000, %ax;
    push %ax;
    popf;
    pushf;
    popw %ax;
    test $0x3000, %ax;
    jz entry_not32bit;

    /* Setup all the segments and the 32-bit stack.                           */
    movw %cs, %ax;
    movw %ax, %fs;
    movw %ax, %gs;
    xorl %esp, %esp;
    xorl %ebp, %ebp;

    /* And finally enter the real System Initializer.                         */
    call entry;

    /* If we somehow return from the function halt the system.                */
    1:
        hlt;
    jmp 1b;

/******************************************************************************/
/* not32bit - Not a 32-bit Processor                                          */
/*                                                                            */
/* We don't have a 32-bit processor. Print a message and halt the system.     */
/******************************************************************************/
entry_not32bit:

    /* Print the error message.                                               */
    movw $entry_error, %si;
    call entry_write;

    /* Wait until the user presses a key.                                     */
    xorb %ah, %ah;
    int $0x16;

    /* And reboot.                                                            */
    1:
        int $0x19;
    jmp 1b;

/******************************************************************************/
/* entry_write - Write String                                                 */
/*                                                                            */
/* This functions displays a string on the screen. We have to use a dedicated */
/* function, because the existing one uses 32-bit code, while we want to use  */
/* this function on 16-bit machines.                                          */
/******************************************************************************/
entry_write:
    cld;
    1:
                lodsb;
                orb %al, %al;
                jz 1f;
                movb $0x0E, %ah;
                movw $0x000F, %bx;
                int $0x10;
                jmp 1b;
    1:
                ret;

.data

entry_error: .ascii "This Operating System requires a 32-bit processor!\n\r\x7";
             .asciz "Press any key to reboot...\n\r";
