/******************************************************************************/
/* Mithrill Code : Kernel Debugger                                            */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

extern void arch_kdb_keyboard(void);
extern long arch_kdb_input;

void arch_kdb_enter(void)
{
    arch_kdb_input = 0;
    sig_arch_setinterruptgate(0x21, arch_kdb_keyboard);
}

unsigned char arch_kdb_getkey(void)
{
    unsigned char key;

    unsigned char arch_kdb_keytable[128] =
    {
        /* 0x00 */  ' ', ' ', '1', '2', '3', '4', '5', '6',
        /* 0x00 */  '7', '8', '9', '0', '-', '=', ' ', ' ',
        /* 0x10 */  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
        /* 0x00 */  'o', 'p', '[', ']', ' ', ' ', 'a', 's',
        /* 0x00 */  'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
        /* 0x00 */  '\'','`', ' ', '\\','z', 'x', 'c', 'v',
        /* 0x00 */  'b', 'n', 'm', ',', '.', '/', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0x00 */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };

    asm ("sti;");

    while (arch_kdb_input == 0 || arch_kdb_input >= 0x80)
    {
        asm ("hlt;");
        key = arch_kdb_keytable[arch_kdb_input];
    }

    return key;
}

void arch_kdb_putchar(unsigned char c)
{
    static pos = 0;
    unsigned short* v = ((unsigned short*)(0xB0000));
    int i;

    v[1920 + pos] = 0x0700 + c;

    pos++;

    if (pos >= 80)
    {
        for (i = 0; i < 1920; i++)
        {
            v[i] = v[i + 80];
        }

        for (i = 1920; i < 2000; i++)
        {
            v[i] = 0;
        }

        pos = 0;
    }
}
