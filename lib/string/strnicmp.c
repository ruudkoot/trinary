/***
*strnicmp.c - compare n chars of strings, ignoring case
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _strnicmp() - Compares at most n characters of two strings,
*       without regard to case.
*
*******************************************************************************/

/***
*int _strnicmp(first, last, count) - compares count char of strings, ignore case
*
*Purpose:
*       Compare the two strings for lexical order.  Stops the comparison
*       when the following occurs: (1) strings differ, (2) the end of the
*       strings is reached, or (3) count characters have been compared.
*       For the purposes of the comparison, upper case characters are
*       converted to lower case.
*
*Entry:
*       char *first, *last - strings to compare
*       size_t count - maximum number of characters to compare
*
*Exit:
*       returns <0 if first < last
*       returns 0 if first == last
*       returns >0 if first > last
*
*Exceptions:
*
*******************************************************************************/

int __cdecl strnicmp (
        const char * first,
        const char * last,
        size_t count
        )
{
        int f,l;


        if ( count )
        {


                do {
                    if ( ((f = (unsigned char)(*(first++))) >= 'A') &&
                         (f <= 'Z') )
                        f -= 'A' - 'a';

                    if ( ((l = (unsigned char)(*(last++))) >= 'A') &&
                         (l <= 'Z') )
                        l -= 'A' - 'a';

                } while ( --count && f && (f == l) );


            return( f - l );
        }

        return( 0 );
}
