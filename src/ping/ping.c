/******************************************************************************/
/* Ping Application                                                           */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#define NOMEM
#include "../lib/config.c"
#include "../lib/lib.c"

void out(char* output)
{
    int i;
    char* m = (char*)0xB80A8;

    while (*output)
    {
        *m = *output;
        m++;
        *m = 0x07;
        m++;
        output++;
    }
}

void cmain(void)
{
    unsigned i, o, d;
    char s[20];
    
    for (i = 0;; i++)
	{
		asm volatile
        (
            "pushl %%ebp;"
            "int $0xC0;"
            "popl %%ebp;"
            :
            "=S" (o),
            "=D" (d),
            "=b" (d),
            "=d" (d)
            :
            "a" (3),
            "d" (3),
            "S" (i)
        );

        if ((o != 1234) && ((i % 1000) == 0))
        {
            u32toa(o, s, 10);
            out(s);
        }
	}

}
