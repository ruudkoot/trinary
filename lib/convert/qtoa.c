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

static void __stdcall x64toa (      /* stdcall is faster and smaller... Might as well use it for the helper. */
        unsigned __int64 val,
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

        if ( is_neg )
        {
            *p++ = '-';         /* negative, so output '-' and negate */
            val = (unsigned __int64)(-(__int64)val);
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

char * __cdecl _i64toa (
        __int64 val,
        char *buf,
        int radix
        )
{
        x64toa((unsigned __int64)val, buf, radix, (radix == 10 && val < 0));
        return buf;
}

char * __cdecl _ui64toa (
        unsigned __int64 val,
        char *buf,
        int radix
        )
{
        x64toa(val, buf, radix, 0);
        return buf;
}
