/***
*tolower.c - convert character to lower case
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines function versions of _tolower() and tolower().
*
*******************************************************************************/

/* define function-like macro equivalent to _tolower()
 */
//#define mklower(c)  ( (c)-'A'+'a' )

/***
*int _tolower(c) - convert character to lower case
*
*Purpose:
*       _tolower() is simply a function version of the macro of the same name.
*
*Entry:
*       c - int value of character to be converted
*
*Exit:
*       returns int value of lower case representation of c
*
*Exceptions:
*
*******************************************************************************/

int __cdecl tolower (
        int c
        )
{
        if (c >= 'A' && c <= 'Z') c += ('a' - 'A');
		return c;
}
