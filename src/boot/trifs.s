/******************************************************************************/
/* Boot Sector for TriFS Disks                                                */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

.arch i8086, jumps
.code16
.text

jmp abc

.balign 32, 0xAB
.fill 224, 1, 0xCD

abc:

cli
hlt

.balign 256, 0xEF
