/******************************************************************************/
/*                                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

char*  strcat(char* dst, const char* src)
{
        char * cp = dst;
        while( *cp ) cp++;                   /* find end of dst */
        while( *cp++ = *src++ ) ;       /* Copy src to end of dst */
        return( dst );                  /* return dst */
}