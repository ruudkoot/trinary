/******************************************************************************/
/* Mithrill Core : Inter Process Communication                                */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

.global _kippointer;
.global _entry;

_entry:
movl %eax, _kippointer;
jmp cmain;

_kippointer: .long 0x00000000;
