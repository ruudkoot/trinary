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

void panicWrite(unsigned r, unsigned c, char* s)
{
    unsigned char* v;
    v = (unsigned char*)(0xB8000 + 160 * r + 2 * c);
    //Write a special strcpy() for this!
    memcpybw(v, s, strlen(s));
}

void cmain(void)
{
    unsigned i = 0;
    char s[20];

    panicWrite(7, 7, "Root Server Running!");

    i = 33333;
    
    for (;;)
    {
        i+=2;
        u32toa(i, s, 10);
        panicWrite(2, 4, s);
    }
}
