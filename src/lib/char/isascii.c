/******************************************************************************/
/* Core Library :                                                             */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

bool isascii(const unsigned char c)
{
	return (c >= 0x00 && c <= 0x7F);
}
