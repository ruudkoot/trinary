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
*strspn.c - find length of initial substring of chars from a control string
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines strspn() - finds the length of the initial substring of
*       a string consisting entirely of characters from a control string.
*
*       defines strcspn()- finds the length of the initial substring of
*       a string consisting entirely of characters not in a control string.
*
*       defines strpbrk()- finds the index of the first character in a string
*       that is not in a control string
*
*******************************************************************************/



/***
*char *strpbrk(string, control) - scans string for a character from control
*
*Purpose:
*       Finds the first occurence in string of any character from
*       the control string.
*
*Entry:
*       char *string - string to search in
*       char *control - string containing characters to search for
*
*Exit:
*       returns a pointer to the first character from control found
*       in string.
*       returns NULL if string and control have no characters in common.
*
*Exceptions:
*
*******************************************************************************/


char * __cdecl strpbrk (
        const char * string,
        const char * control
        )
{
        const unsigned char *str = (unsigned char *)string;
        const unsigned char *ctrl = (unsigned char *)control;

        unsigned char map[32];
        int count;

        /* Clear out bit map */
        for (count=0; count<32; count++)
                map[count] = 0;

        /* Set bits in control map */
        while (*ctrl)
        {
                map[*ctrl >> 3] |= (1 << (*ctrl & 7));
                ctrl++;
        }

        /* 1st char in control map stops search */
        while (*str)
        {
                if (map[*str >> 3] & (1 << (*str & 7)))
                        return((char *)str);
                str++;
        }
        return(0);


}
