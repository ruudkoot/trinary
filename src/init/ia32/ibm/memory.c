/******************************************************************************/
/* Mithrill : System Initializer : IA-32 : IBM : Memory Detection             */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

bool memory_detect(void)
{
    unsigned char buffer[20];
    unsigned c, d, i;
    
    log_item("Detecting Memory");

    memset(buffer, 0, 20);

    c = 0;

    do
    {
        asm
        (
            "int $0x15;"
            :
            "=b" (d)
            :
            "a" (0x0000E820),   /* Function   : E820h                         */
            "b" (c),            /* Part       : 0                             */
            "c" (20),           /* Buffer Size: 20 bytes                      */
            "d" (0x534D4150),   /* Key        : SMAP                          */
            "D" (buffer)
        );

        log_hex("Identifier", c);
        log_hex("  Base", (*(unsigned*)(buffer + 0)));
        log_hex("  Lenght", (*(unsigned*)(buffer + 8)));
        log_hex("  Type", (*(unsigned*)(buffer + 16)));

        c = d;

    } while (c != 0);
}
