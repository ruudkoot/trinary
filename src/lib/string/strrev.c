/******************************************************************************/
/*                                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/***
*strrev.c - reverse a string in place
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _strrev() - reverse a string in place (not including
*       '\0' character)
*
*******************************************************************************/

/***
*char *_strrev(string) - reverse a string in place
*
*Purpose:
*       Reverses the order of characters in the string.  The terminating
*       null character remains in place.
*
*Entry:
*       char *string - string to reverse
*
*Exit:
*       returns string - now with reversed characters
*
*Exceptions:
*
*******************************************************************************/

char * _strrev (
        char * string
        )
{
        char *start = string;
        char *left = string;
        char ch;

        while (*string++)                 /* find end of string */
                ;
        string -= 2;

        while (left < string)
        {
                ch = *left;
                *left++ = *string;
                *string-- = ch;
        }

        return(start);
}
