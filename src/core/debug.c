/******************************************************************************/
/* Debugging Helper Functions                                                 */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/


void panic(char* title);
void panicWrite(unsigned r, unsigned c, char* s);
void panicHalt(void);

void panic(char* title)
{
    unsigned char* v;
    unsigned i;


    panicWrite(2, 41 - strlen(title) / 2, title);
    //panicWrite(23, 15, "SYSTEM HALTED! PRESS [RESET] TO REBOOT YOUR COMUTER.");

    panicHalt();
}

void panicWrite(unsigned r, unsigned c, char* s)
{
    unsigned char* v;
    v = (unsigned char*)(0xB8000 + 160 * r + 2 * c);
    //Write a special strcpy() for this!
    memcpybw(v, s, strlen(s));
}

void panicHalt(void)
{
    asm ("cli");
    asm ("hlt");
}
