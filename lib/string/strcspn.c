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
*int strcspn(string, control) - search for init substring w/o control chars
*
*Purpose:
*       returns the index of the first character in string that belongs
*       to the set of characters specified by control.  This is equivalent
*       to the length of the length of the initial substring of string
*       composed entirely of characters not in control.  Null chars not
*       considered.
*
*Entry:
*       char *string - string to search
*       char *control - set of characters not allowed in init substring
*
*Exit:
*       returns the index of the first char in string
*       that is in the set of characters specified by control.
*
*Exceptions:
*
*******************************************************************************/

size_t __cdecl strcspn (
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
        count=0;
        map[0] |= 1;    /* null chars not considered */
        while (!(map[*str >> 3] & (1 << (*str & 7))))
        {
                count++;
                str++;
        }
        return(count);
}
