/******************************************************************************/
/* Core Library :                                                             */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/***
*toupper.c - convert character to uppercase
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines function versions of _toupper() and toupper().
*
*******************************************************************************/

//#define mkupper(c)  ( (c)-'a'+'A' )

/***
*int _toupper(c) - convert character to uppercase
*
*Purpose:
*       _toupper() is simply a function version of the macro of the same name.
*
*Entry:
*       c - int value of character to be converted
*
*Exit:
*       returns int value of uppercase representation of c
*
*Exceptions:
*
*******************************************************************************/

int  toupper (
        int c
        )
{
        if (c >= 'a' && c <= 'z') c += ('A' - 'a');
		return c;
}
