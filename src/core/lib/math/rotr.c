/***
*rotr.c - rotate an unsigned integer right
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _rotr() - performs a rotate right on an unsigned integer.
*
*******************************************************************************/




/***
*unsigned _rotr(val, shift) - int rotate right
*
*Purpose:
*       Performs a rotate right on an unsigned integer.
*
*       [Note:  The _lrotl entry is based on the assumption
*       that sizeof(int) == sizeof(long).]
*Entry:
*       unsigned val:   value to rotate
*       int    shift:   number of bits to shift by
*
*Exit:
*       returns rotated value
*
*Exceptions:
*       None.
*
*******************************************************************************/


unsigned __cdecl rotr (
        unsigned val,
        int shift
        )
{
        register unsigned lobit;        /* non-zero means lo bit set */
        register unsigned num = val;    /* number to rotate */

        shift &= 0x1f;                  /* modulo 32 -- this will also make
                                           negative shifts work */

        while (shift--) {
                lobit = num & 1;        /* get high bit */
                num >>= 1;              /* shift right one bit */
                if (lobit)
                        num |= 0x80000000;  /* set hi bit if lo bit was set */
        }

        return num;
}

