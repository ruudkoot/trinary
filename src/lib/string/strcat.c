/******************************************************************************/
/* Core Library : Concatenate String                                          */
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

/******************************************************************************/
/* strcat - Concatenate String                                                */
/*                                                                            */
/* This fuction concatenates two strings (add the source string to the end of */
/* the destination string. It assumes there is enough space in the            */
/* destination to add the source string to it.                                */
/*                                                                            */
/* s    The destination string.                                               */
/* t    The source string.                                                    */
/* @    The destination string.                                               */
/******************************************************************************/
char* strcat(char* s, const char* t)
{
    string* c = s;

    /* Find the end of the destination string.                                */
    while (*s) s++;

    /* Copy the source sting to the destination string.                       */
    while (*s++ = *t++);

    return (c);
}

/******************************************************************************/
/* strncat - Concatenate String up to n Characters                            */
/*                                                                            */
/* This fuction concatenates two strings (add the source string to the end of */
/* the destination string. It assumes there is enough space in the            */
/* destination to add the source string to it. The total lenght of the        */
/* concatened string may not be larger than n characters. This includes the   */
/* NULL charecter.                                                            */
/*                                                                            */
/* s    The destination string.                                               */
/* t    The source string.                                                    */
/* n    The maximum lenght of the concatednated string.                       */
/* @    The destination string.                                               */
/******************************************************************************/

char * strncat (
        char * front,
        const char * back,
        size count
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
