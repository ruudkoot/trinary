/******************************************************************************/
/* Core Library : Concatenate String                                          */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

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
string* strcat(string* s,const string* t)
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
string* strncat(string* s, string* t, size n)
{
    string* c = s;

    /* Find the end of the destination string.                                */
    while (*s) s++;

    while (n--)
            if (!(*front++ = *back++))
                    return(start);

    *front = '\0';
    return(start);
}