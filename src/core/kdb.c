/******************************************************************************/
/* Mithrill Code : Kernel Debugger                                            */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include "ia32/kdb.c"

void kdb_enter(void)
{
    char s[2] = {'\0', '\0'};
    
    arch_kdb_enter();

    while (true)
    {
        s[0] = arch_kdb_getkey();
        arch_kdb_putchar(s[0]);
        arch_kdb_input = 0;
    }
}
