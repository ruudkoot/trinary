/***
*memicmp.c - compare memory, ignore case
*
*   Copyright (c) 1988-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _memicmp() - compare two blocks of memory for lexical
*       order.  Case is ignored in the comparison.
*
*******************************************************************************/


#define _TOLOWER(c) ( ((c) >= 'A') && ((c) <= 'Z') ? ((c) - 'A' + 'a') :\
              (c) )

/***
*int _memicmp(first, last, count) - compare two blocks of memory, ignore case
*
*Purpose:
*   Compares count bytes of the two blocks of memory stored at first
*   and last.  The characters are converted to lowercase before
*   comparing (not permanently), so case is ignored in the search.
*
*Entry:
*   char *first, *last - memory buffers to compare
*   unsigned count - maximum length to compare
*
*Exit:
*   returns < 0 if first < last
*   returns 0 if first == last
*   returns > 0 if first > last
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _memicmp (
        const void * first,
        const void * last,
        unsigned int count
        )
{
        int f = 0;
        int l = 0;


            while ( count-- )
            {
                if ( (*(unsigned char *)first == *(unsigned char *)last) ||
                     ((f = _TOLOWER( *(unsigned char *)first )) ==
                      (l = _TOLOWER( *(unsigned char *)last ))) )
                {
                    first = (char *)first + 1;
                    last = (char *)last + 1;
                }
                else
                    break;
            }


        return ( f - l );
}
