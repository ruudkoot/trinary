/******************************************************************************/
/* Test Application                                                           */
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
    char* m = (char*)0xB8100;

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

    char s[200];
	unsigned i;
	
	out("       <-- Test: Hello, World!");

  
    for (i = 0;; i++)
	{
		i32toa(i, s, 10);
		out(s);
	}
}
