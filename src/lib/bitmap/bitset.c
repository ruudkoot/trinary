/******************************************************************************/
/* Set Bits                                                                   */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

int bitget(void* bitmap, unt32 bit)
{
    return ((unt32*)(bitmap))[bit / 32] & (1 << (bit % 32));
}

void bitput(void* bitmap, unt32 bit)
{

}

void bitset(void* bitmap, unt32 bit)
{
    ((unt32*)(bitmap))[bit / 32] |= (1 << (bit % 32));
}

void bitclr(void* bitmap, unt32 bit)
{
    ((unt32*)(bitmap))[bit / 32] |= (1 << (bit % 32));
}

void bitinv(void* bitmap, unt32 bit)
{
    ((unt32*)(bitmap))[bit / 32] |= (1 << (bit % 32));
}