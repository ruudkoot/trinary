/******************************************************************************/
/* Mithrill Operating System : Core : VESA Support                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void vesa_init(void)
{
    unsigned i;
    
    logItem("Initializing VESA Management");

    for (i = 0; i < 0x7FFC; i++)
    {
        if (!memcmp(i + 0xC0000, "PMID", 4))
        {
            logHex("PMID Signature Found @", i);
            logHex("PM Entry Point", ((unsigned short*)(i + 4)));

            asm ("cli;hlt;");
        }
    }


}
