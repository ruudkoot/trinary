/******************************************************************************/
/* System Initialization                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void log_writestring(char* s)
{
    asm
    (
        "cld;"
	    "LoopWriteMessage:"
                    "lodsb;"
                    "orb %%al, %%al;"
                    "jz DoneWriteMessage;"
                    "movb $0x0E, %%ah;"
                    "movw $0x000F, %%bx;"
                    "int $0x10;"
                    "jmp LoopWriteMessage;"
	    "DoneWriteMessage:"
    :
    :
        "S" (s)
    );
}
