/******************************************************************************/
/* Compiler Configuration (GCC 2 & 3)                                         */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/* Types */
typedef enum {false = 0, true = !0} bool;

typedef signed char                 int8;
typedef signed short int            int16;
typedef signed int                  int32;
typedef signed long long int        int64;

typedef unsigned char               unt8;
typedef unsigned short int          unt16;
typedef unsigned int                unt32;
typedef unsigned long long int      unt64;

typedef void*                       pointer;
typedef unsigned char               string;

typedef unt32                       size;

/* Attributes */
//HTF do give this the atrribute CODE READONLY and more of that $#!+.
//The p2align 4,,7 cause UDs because they 0 no NOPs (90h) in DATA.
//LD would be to late I'd guess. Don't know where to do in GCC. And
//OBJCOPY is too much work.
//#define discardable                 __attribute__ ((__section__ (".text.init")))
#define discardable
