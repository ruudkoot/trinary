/******************************************************************************/
/* Legacy Run-Time Library Core                                               */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* The functions in this module should be or are merged into the new run-time */
/* library. Do not use any of these functions, please.                        */
/******************************************************************************/

int max(int a, int b)
{
	return (a > b) ? a : b;
}

/***
*xtoa.c - convert integers/longs to ASCII string
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       The module has code to convert integers/longs to ASCII strings.  See
*
*******************************************************************************/


/***
*char *_itoa, *_ltoa, *_ultoa(val, buf, radix) - convert binary int to ASCII
*       string
*
*Purpose:
*       Converts an int to a character string.
*
*Entry:
*       val - number to be converted (int, long or unsigned long)
*       int radix - base to convert into
*       char *buf - ptr to buffer to place result
*
*Exit:
*       fills in space pointed to by buf with string result
*       returns a pointer to this buffer
*
*Exceptions:
*
*******************************************************************************/

/* helper routine that does the main job. */

static void  xtoa (
        unsigned long val,
        char *buf,
        unsigned radix,
        int is_neg
        )
{
        char *p;                /* pointer to traverse string */
        char *firstdig;         /* pointer to first digit */
        char temp;              /* temp char */
        unsigned digval;        /* value of digit */

        p = buf;

        if (is_neg) {
            /* negative, so output '-' and negate */
            *p++ = '-';
            val = (unsigned long)(-(long)val);
        }

        firstdig = p;           /* save pointer to first digit */

        do {
            digval = (unsigned) (val % radix);
            val /= radix;       /* get next digit */

            /* convert to ascii and store */
            if (digval > 9)
                *p++ = (char) (digval - 10 + 'a');  /* a letter */
            else
                *p++ = (char) (digval + '0');       /* a digit */
        } while (val > 0);

        /* We now have the digit of the number in the buffer, but in reverse
           order.  Thus we reverse them now. */

        *p-- = '\0';            /* terminate string; p points to last digit */

        do {
            temp = *p;
            *p = *firstdig;
            *firstdig = temp;   /* swap *p and *firstdig */
            --p;
            ++firstdig;         /* advance to next two digits */
        } while (firstdig < p); /* repeat until halfway */
}

/* Actual functions just call conversion helper with neg flag set correctly,
   and return pointer to buffer. */

char * itoa (
        int val,
        char *buf,
        int radix
        )
{
        if (radix == 10 && val < 0)
            xtoa((unsigned long)val, buf, radix, 1);
        else
            xtoa((unsigned long)(unsigned int)val, buf, radix, 0);
        return buf;
}

char *  ltoa (
        long val,
        char *buf,
        int radix
        )
{
        xtoa((unsigned long)val, buf, radix, (radix == 10 && val < 0));
        return buf;
}

char *  ultoa (
        unsigned long val,
        char *buf,
        int radix
        )
{
        xtoa(val, buf, radix, 0);
        return buf;
}







/****************************/

/*
bool inline isalnum(const num8 c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

bool inline isalpha(const num8 c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool inline iscsym(const num8 c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_'));
}

bool inline isprint(const num8 c)
{
    return (c >= ' ' && c <= '~');
}

bool inline isascii(const num8 c)
{
    return (c >= 0x00 && c <= 0x7F);
}

bool inline isgraph(const num8 c)
{
    return (!(c >= 0x00 && c <= 0x7F));
}

bool inline islower(const num8 c)
{
    return (c >= 'a' && c <= 'z');
}

bool inline isxdigit(const num8 c)
{
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

bool inline isdigit(const num8 c)
{
    return (c >= '0' && c <= '9');
}

bool inline isupper(const num8 c)
{
    return (c >= 'A' && c <= 'Z');
}

bool inline isspace(const num8 c)
{
    return (c == ' ' || (c >= 0x09 && c <= 0x0D));
}

bool inline isctrl(const num8 c)
{
    return (!(c >= ' ' && c <= '~'));
}

bool inline iscsymf(const num8 c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'));
}

bool inline ispunct(const num8 c)
{
    return ((c >= '!' && c<= '/') || (c >= ':' && c<= '@') || (c >= '[' && c<= '`') || (c >= '{' && c<= '~'));
}

int inline tolower(const num8 c)
{
        if (c >= 'A' && c <= 'Z') c += ('a' - 'A');
        return c;
}

int inline toupper (const num8 c)
{
        if (c >= 'a' && c <= 'z') c += ('A' - 'a');
        return c;
}*/

char*  strcat(char* dst, const char* src)
{
        char * cp = dst;
        while( *cp ) cp++;                   /* find end of dst */
        while( *cp++ = *src++ ) ;       /* Copy src to end of dst */
        return( dst );                  /* return dst */
}

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

char *  strncat (
        char * front,
        const char * back,
        int32 count
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
/***
*strchr.c - search a string for a given character
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines strchr() - search a string for a character
*
*******************************************************************************/

/***
*char *strchr(string, c) - search a string for a character
*
*Purpose:
*       Searches a string for a given character, which may be the
*       null character '\0'.
*
*Entry:
*       char *string - string to search in
*       char c - character to search for
*
*Exit:
*       returns pointer to the first occurence of c in string
*       returns NULL if c does not occur in string
*
*Exceptions:
*
*******************************************************************************/

char *  strchr (
        const char * string,
        int ch
        )
{
        while (*string && *string != (char)ch)
                string++;

        if (*string == (char)ch)
                return((char *)string);
        return(0);
}

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

char *  strrchr (
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


int strcmp (
        const char * src,
        const char * dst
        )
{
        int ret = 0 ;

        while( ! (ret = *(unsigned char *)src - *(unsigned char *)dst) && *dst)
                ++src, ++dst;

        if ( ret < 0 )
                ret = -1 ;
        else if ( ret > 0 )
                ret = 1 ;

        return( ret );
}

int  strncmp (
        const char * first,
        const char * last,
        int32 count
        )
{
        if (!count)
                return(0);

        while (--count && *first && *first == *last)
        {
                first++;
                last++;
        }

        return( *(unsigned char *)first - *(unsigned char *)last );
}

char* strcpy(char* s, const char* t)
{
    while (*(s++) = *(t++));

    return s;
}

char *  strncpy (
        char * dest,
        const char * source,
        int32 count
        )
{
        char *start = dest;

        while (count && (*dest++ = *source++))    /* copy string */
                count--;

        if (count)                              /* pad out with zeroes */
                while (--count)
                        *dest++ = '\0';

        return(start);
}

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

int32  strcspn (
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


/***
*stricmp.c - contains case-insensitive string comp routine _stricmp/_strcmpi
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains _stricmp(), also known as _strcmpi()
*
*******************************************************************************/


/***
*int _stricmp(dst, src), _strcmpi(dst, src) - compare strings, ignore case
*
*Purpose:
*       _stricmp/_strcmpi perform a case-insensitive string comparision.
*       For differences, upper case letters are mapped to lower case.
*       Thus, "abc_" < "ABCD" since "_" < "d".
*
*Entry:
*       char *dst, *src - strings to compare
*
*Return:
*       <0 if dst < src
*        0 if dst = src
*       >0 if dst > src
*
*Exceptions:
*
*******************************************************************************/

/* strcmpi */

int  stricmp(const char * dst, const char * src)
{
        int f,l;


            do {
                if ( ((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z') )
                    f -= ('A' - 'a');

                if ( ((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z') )
                    l -= ('A' - 'a');
            } while ( f && (f == l) );


        return(f - l);
}
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
*       int32 count - maximum number of characters to compare
*
*Exit:
*       returns <0 if first < last
*       returns 0 if first == last
*       returns >0 if first > last
*
*Exceptions:
*
*******************************************************************************/

int  strnicmp (
        const char * first,
        const char * last,
        int32 count
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
unsigned strlen(const char* s)
{
    const char* c = s;
    while (*c++);
    return (unsigned)(c - s - 1);
}
char* strlwr(char* s)
{
    while (*s++) if (*s >= 'A' && *s <= 'Z') *s += 'a' - 'A';
    return s;
}
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


char *  strpbrk (
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
char* strpst(char* s, const char* t)
{
    while (*t)
    {
        *(s++) = *(t++);
    };

    return s;
}
char* strnpst(char* s, const char* t, unsigned n)
{
    while (*t && n)
    {
        *(s++) = *(t++);
        n--;
    };

    return s;
}
/***
*strrev.c - reverse a string in place
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _strrev() - reverse a string in place (not including
*       '\0' character)
*
*******************************************************************************/

/***
*char *_strrev(string) - reverse a string in place
*
*Purpose:
*       Reverses the order of characters in the string.  The terminating
*       null character remains in place.
*
*Entry:
*       char *string - string to reverse
*
*Exit:
*       returns string - now with reversed characters
*
*Exceptions:
*
*******************************************************************************/

char *  _strrev (
        char * string
        )
{
        char *start = string;
        char *left = string;
        char ch;

        while (*string++)                 /* find end of string */
                ;
        string -= 2;

        while (left < string)
        {
                ch = *left;
                *left++ = *string;
                *string-- = ch;
        }

        return(start);
}
char *  _strset (
        char * string,
        int val
        )
{
        char *start = string;

        while (*string)
                *string++ = (char)val;

        return(start);
}
char *  _strnset (
        char * string,
        int val,
        int32 count
        )
{
        char *start = string;

        while (count-- && *string)
                *string++ = (char)val;

        return(start);
}
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

int32  strspn (
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
/***
*strstr.c - search for one string inside another
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines strstr() - search for one string inside another
*
*******************************************************************************/

/***
*char *strstr(string1, string2) - search for string2 in string1
*
*Purpose:
*       finds the first occurrence of string2 in string1
*
*Entry:
*       char *string1 - string to search in
*       char *string2 - string to search for
*
*Exit:
*       returns a pointer to the first occurrence of string2 in
*       string1, or NULL if string2 does not occur in string1
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

char *  strstr (
        const char * str1,
        const char * str2
        )
{
        char *cp = (char *) str1;
        char *s1, *s2;

        if ( !*str2 )
            return((char *)str1);

        while (*cp)
        {
                s1 = cp;
                s2 = (char *) str2;

                while ( *s1 && *s2 && !(*s1-*s2) )
                        s1++, s2++;

                if (!*s2)
                        return(cp);

                cp++;
        }

        return(0);

}
char* strupr(char* s)
{
    char* c;
    while (*s++) if (*s >= 'a' && *s <= 'z') *s += 'A' - 'a';
    return c;
}

/***
*memccpy.c - copy bytes until a character is found
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _memccpy() - copies bytes until a specifed character
*       is found, or a maximum number of characters have been copied.
*
*******************************************************************************/


/***
*char *_memccpy(dest, src, c, count) - copy bytes until character found
*
*Purpose:
*       Copies bytes from src to dest until count bytes have been
*       copied, or up to and including the character c, whichever
*       comes first.
*
*Entry:
*       void *dest - pointer to memory to receive copy
*       void *src  - source of bytes
*       int  c     - character to stop copy at
*       unsigned int count - max number of bytes to copy
*
*Exit:
*       returns pointer to byte immediately after c in dest
*       returns NULL if c was never found
*
*Exceptions:
*
*******************************************************************************/

void * memccpy (
        void * dest,
        const void * src,
        int c,
        unsigned count
        )
{
        while ( count && (*((char *)(dest = (char *)dest + 1) - 1) =
        *((char *)(src = (char *)src + 1) - 1)) != (char)c )
                count--;

        return(count ? dest : 0);
}

/***
*swab.c - block copy, while swapping even/odd bytes
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This module contains the routine _swab() which swaps the odd/even
*       bytes of words during a block copy.
*
*******************************************************************************/

/***
*void _swab(srcptr, dstptr, nbytes) - swap ODD/EVEN bytes during word move
*
*Purpose:
*       This routine copys a block of words and swaps the odd and even
*       bytes.  nbytes must be > 0, otherwise nothing is copied.  If
*       nbytes is odd, then only (nbytes-1) bytes are copied.
*
*Entry:
*       srcptr = pointer to the source block
*       dstptr = pointer to the destination block
*       nbytes = number of bytes to swap
*
*Returns:
*       None.
*
*Exceptions:
*
*******************************************************************************/

void swab (char *src, char *dest, int nbytes)
{
        char b1, b2;

        while (nbytes > 1) {
                b1 = *src++;
                b2 = *src++;
                *dest++ = b2;
                *dest++ = b1;
                nbytes -= 2;
        }
}

void* memcpy(void* s, void* t, unsigned n)
{
        void * ret = s;

        while (n--)
		{
                *(char *)s = *(char *)t;
                s = (char *)s + 1;
                t = (char *)t + 1;
        }

        return(ret);
}

/***
*memcmp.c - compare two blocks of memory
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines memcmp() - compare two memory blocks lexically and
*       find their order.
*
*******************************************************************************/


/***
*int memcmp(buf1, buf2, count) - compare memory for lexical order
*
*Purpose:
*       Compares count bytes of memory starting at buf1 and buf2
*       and find if equal or which one is first in lexical order.
*
*Entry:
*       void *buf1, *buf2 - pointers to memory sections to compare
*       unsigned count - length of sections to compare
*
*Exit:
*       returns < 0 if buf1 < buf2
*       returns  0  if buf1 == buf2
*       returns > 0 if buf1 > buf2
*
*Exceptions:
*
*******************************************************************************/

int memcmp (
        const void * buf1,
        const void * buf2,
        unsigned count
        )
{
        if (!count)
                return(0);

        while ( --count && *(char *)buf1 == *(char *)buf2 ) {
                buf1 = (char *)buf1 + 1;
                buf2 = (char *)buf2 + 1;
        }

        return( *((unsigned char *)buf1) - *((unsigned char *)buf2) );
}


/***
*memchr.c - search block of memory for a given character
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines memchr() - search memory until a character is
*       found or a limit is reached.
*
*******************************************************************************/


/***
*char *memchr(buf, chr, cnt) - search memory for given character.
*
*Purpose:
*       Searches at buf for the given character, stopping when chr is
*       first found or cnt bytes have been searched through.
*
*Entry:
*       void *buf  - memory buffer to be searched
*       int chr    - character to search for
*       unsigned cnt - max number of bytes to search
*
*Exit:
*       returns pointer to first occurence of chr in buf
*       returns NULL if chr not found in the first cnt bytes
*
*Exceptions:
*
*******************************************************************************/

void * memchr (
        const void * buf,
        int chr,
        unsigned cnt
        )
{
        while ( cnt && (*(unsigned char *)buf != (unsigned char)chr) ) {
                buf = (unsigned char *)buf + 1;
                cnt--;
        }

        return(cnt ? (void *)buf : 0);
}


/***
*memmove.c - contains memmove routine
*
*       Copyright (c) 1988-1997, Microsoft Corporation. All right reserved.
*
*Purpose:
*       memmove() copies a source memory buffer to a destination buffer.
*       Overlapping buffers are treated specially, to avoid propogation.
*
*******************************************************************************/

/***
*memmove - Copy source buffer to destination buffer
*
*Purpose:
*       memmove() copies a source memory buffer to a destination memory buffer.
*       This routine recognize overlapping buffers to avoid propogation.
*       For cases where propogation is not a problem, memcpy() can be used.
*
*Entry:
*       void *dst = pointer to destination buffer
*       const void *src = pointer to source buffer
*       unsigned count = number of bytes to copy
*
*Exit:
*       Returns a pointer to the destination buffer
*
*Exceptions:
*******************************************************************************/

void * memmove (
        void * dst,
        const void * src,
        unsigned count
        )
{
        void * ret = dst;


        if (dst <= src || (char *)dst >= ((char *)src + count)) {
                /*
                 * Non-Overlapping Buffers
                 * copy from lower addresses to higher addresses
                 */
                while (count--) {
                        *(char *)dst = *(char *)src;
                        dst = (char *)dst + 1;
                        src = (char *)src + 1;
                }
        }
        else {
                /*
                 * Overlapping Buffers
                 * copy from higher addresses to lower addresses
                 */
                dst = (char *)dst + count - 1;
                src = (char *)src + count - 1;

                while (count--) {
                        *(char *)dst = *(char *)src;
                        dst = (char *)dst - 1;
                        src = (char *)src - 1;
                }
        }


        return(ret);
}

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

int _memicmp (
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


void* memset(void* s, char i, unsigned n)
{
        void *start = s;

        while (n--) {
                *(char *)s = (char)i;
                s = (char *)s + 1;
        }

        return(start);
}

void* memsetw(void* s, short i, unsigned n)
{
        void *start = s;

        while (n--) {
                *(short *)s = (short)i;
                s = (short *)s + 1;
        }

        return(start);
}


void* memcpybw(void* s, void* t, unsigned n)
{
        void * ret = s;

        while (n--)
		{
                *(char *)s = *(char *)t;
                s = (char *)s + 2;
                t = (char *)t + 1;
        }

        return(ret);
}
