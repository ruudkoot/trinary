/******************************************************************************/
/* Compiler Configuration                                                     */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/*  600 Microsoft C 6.0 */
/*  800 Microsoft C 8.0 */ /*1.0*/
/*  800 Microsoft C 8.5 */ /*1.5*/
/*  900 */ /* __int64 support */ /*2.0*/
/* 1000 Microsoft Visual C++ 4.0 */
/* 1100 Microsoft Visual C++ 5.0 */
/* 1200 Microsoft Visual C++ 6.0 */
/*      Microsoft Visual C++ 7.0 (.NET) */

/* GNU C Compiler                                                             */
#ifdef __GNUC__
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

#define packed

#define discardable
#endif /* __GNUC__ */

/* Microsoft C / Microsoft Visual C++                                         */
#ifdef _MSC_VER 
    typedef signed char                 int8;
    typedef signed short                int16;
    typedef signed int                  int32;
    typedef signed __int64              int64;

    typedef unsigned char               unt8;
    typedef unsigned short              unt16;
    typedef unsigned int                unt32;
    typedef unsigned __int64            unt64;

    typedef void*                       pointer;
    typedef unsigned char               string;

    typedef unt32                       size;
#define discardable

#define packed __declspec(align(1))
#endif /* _MSC_VER */
