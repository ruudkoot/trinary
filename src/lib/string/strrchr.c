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
*strrchr.c - find last occurrence of character in string
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines strrchr() - find the last occurrence of a given character
*       in a string.
*
*******************************************************************************/


/***
*char *strrchr(string, ch) - find last occurrence of ch in string
*
*Purpose:
*       Finds the last occurrence of ch in string.  The terminating
*       null character is used as part of the search.
*
*Entry:
*       char *string - string to search in
*       char ch - character to search for
*
*Exit:
*       returns a pointer to the last occurrence of ch in the given
*       string
*       returns NULL if ch does not occurr in the string
*
*Exceptions:
*
*******************************************************************************/

char * strrchr (
        const char * string,
        int ch
        )
{
        char *start = (char *)string;

        while (*string++)                       /* find end of string */
                ;
                                                /* search towards front */
        while (--string != start && *string != (char)ch)
                ;

        if (*string == (char)ch)                /* char found ? */
                return( (char *)string );

        return(0);
}
