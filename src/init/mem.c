/******************************************************************************/
/* Mithrill :                                                                 */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void mem_zero(word address, word size)
{
    asm
    (
        "rep stosl;"
        :
        :
        "a" (0),
        "c" (size / 4),
        "D" (address)
    );
}
