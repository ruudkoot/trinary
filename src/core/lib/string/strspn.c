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
*int strspn(string, control) - find init substring of control chars
*
*Purpose:
*       Finds the index of the first character in string that does belong
*       to the set of characters specified by control.  This is
*       equivalent to the length of the initial substring of string that
*       consists entirely of characters from control.  The '\0' character
*       that terminates control is not considered in the matching process.
*
*Entry:
*       char *string - string to search
*       char *control - string containing characters not to search for
*
*Exit:
*       returns index of first char in string not in control
*
*Exceptions:
*
*******************************************************************************/

size_t __cdecl strspn (
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

        /* 1st char NOT in control map stops search */
        if (*str)
        {
                count=0;
                while (map[*str >> 3] & (1 << (*str & 7)))
                {
                        count++;
                        str++;
                }
                return(count);
        }
        return(0);
}
