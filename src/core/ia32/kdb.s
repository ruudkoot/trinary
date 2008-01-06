/******************************************************************************/
/* Mithrill Core : IA-32 : Kernel Debugger                                    */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/


.global arch_kdb_keyboard;
.global arch_kdb_input;

.text

arch_kdb_keyboard:

        pushal;

        movl $0x60, %edx;
        inb %dx, %al;
        movb %al, arch_kdb_input;

        movb $0x20, %al;
        movl $0x20, %edx;
        outb %al, %dx

        popal;
        iretl;

.data

arch_kdb_input: .long 0x00000000;
