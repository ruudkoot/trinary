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
*strncat.c - append n chars of string to new string
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines strncat() - appends n characters of string onto
*       end of other string
*
*******************************************************************************/


/***
*char *strncat(front, back, count) - append count chars of back onto front
*
*Purpose:
*       Appends at most count characters of the string back onto the
*       end of front, and ALWAYS terminates with a null character.
*       If count is greater than the length of back, the length of back
*       is used instead.  (Unlike strncpy, this routine does not pad out
*       to count characters).
*
*Entry:
*       char *front - string to append onto
*       char *back - string to append
*       unsigned count - count of max characters to append
*
*Exit:
*       returns a pointer to string appended onto (front).
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl strncat (
        char * front,
        const char * back,
        size_t count
        )
{
        char *start = front;

        while (*front++)
                ;
        front--;

        while (count--)
                if (!(*front++ = *back++))
                        return(start);

        *front = '\0';
        return(start);
}
