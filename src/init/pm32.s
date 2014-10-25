/******************************************************************************/
/* System Initialization                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

.extern pm32;

.global Aye;

.text;

Aye:

    /* Setup the stack and data segments.                                     */
    mov $0x18, %ax;
    mov %ax, %ss;
    mov %ax, %ds;
    mov %ax, %es;
    mov %ax, %fs;
    mov %ax, %gs;

    jmp pm32;

    cli;hlt;
