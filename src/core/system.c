/******************************************************************************/
/*                                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void discardable sys_init(void)
{
    logItem("Initializing System Management");

    asm ("outb %%al,%%dx"::"a" (0x26),"d" (0x43));     //MACRO!!!
    asm ("outb %%al,%%dx"::"a" (255),"d" (0x40));     //MACRO!!!

    logStatus(logSuccess);
}
