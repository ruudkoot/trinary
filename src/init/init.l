/******************************************************************************/
/* Trinary Operating System Core Link Script                                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

ENTRY(entry_start)
SECTIONS
{
    .text 0x00000000 :
    {
        *(.text)
    }

    .rodata :
    {
        . = ALIGN(4096);
        *(.rodata)
    }

    .data :
    {
        . = ALIGN(4096);
        *(.data)
    }

    .bss :
    {
        . = ALIGN(4096);
        *(.bss)
    }
}
