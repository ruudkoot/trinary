/******************************************************************************/
/* Trinary Operating System : Root Server                                     */
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

/******************************************************************************/
/* Thsi will one day become the root server, the server that provides basic   */
/* operating system features like process, file and network management which, */
/* unlike most popular operating systems, do not resides inside the kernel.   */
/*                                                                            */
/* At the moment it is used to test the core and it quite a mess for that     */
/* reason. It is highly unlikely that any of this code will make it into the  */
/* real root server.                                                          */
/******************************************************************************/

void out(char* output)
{
    int i;
    unsigned source, destination;
    char* m = (char*)0xB8E68;

    for (i = 0; i < 22; i++)
    {
        source        = 0xB8000 + 160 * i + 488;
        destination    = 0xB8000 + 160 * i + 328;

        memcpy((void*)destination, (void*)source, 148);
    }

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
	unsigned i;
	char s[30];

    out("");
	out("");
	out("************************************************************");
    out("");
	out("Root Server Running!");
	out("");

  
    for (i = 0;; i++)
	{
		i32toa(i, s, 16);
		out(s);
	}
}
