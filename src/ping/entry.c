/******************************************************************************/
/* Entry Stub                                                                 */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

extern void cmain(void);

void _entry(void)
{
    cmain();
    asm ("cli");
    asm ("hlt");
}

void __stack_chk_fail(void)
{
    asm ("cli");
    asm ("hlt");
}
