/******************************************************************************/
/* System Initialization                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/* Page-Directory Entry     Page-Table Entry        Combined Effect           */
/* Privilege    Access Type Privilege   Access Type Privilege Access Type     */
/* User         Read-Only   User        Read-Only   User        Read-Only     */
/* User         Read-Only   User        Read-Write  User        Read-Only     */
/* User         Read-Write  User        Read-Only   User        Read-Only     */
/* User         Read-Write  User        Read-Write  User        Read/Write    */
/* User         Read-Only   Supervisor  Read-Only   Supervisor  Read/Write*   */
/* User         Read-Only   Supervisor  Read-Write  Supervisor  Read/Write*   */
/* User         Read-Write  Supervisor  Read-Only   Supervisor  Read/Write*   */
/* User         Read-Write  Supervisor  Read-Write  Supervisor  Read/Write    */
/* Supervisor   Read-Only   User        Read-Only   Supervisor  Read/Write*   */
/* Supervisor   Read-Only   User        Read-Write  Supervisor  Read/Write*   */
/* Supervisor   Read-Write  User        Read-Only   Supervisor  Read/Write*   */
/* Supervisor   Read-Write  User        Read-Write  Supervisor  Read/Write    */
/* Supervisor   Read-Only   Supervisor  Read-Only   Supervisor  Read/Write*   */
/* Supervisor   Read-Only   Supervisor  Read-Write  Supervisor  Read/Write*   */
/* Supervisor   Read-Write  Supervisor  Read-Only   Supervisor  Read/Write*   */
/* Supervisor   Read-Write  Supervisor  Read-Write  Supervisor  Read/Write    */

#define unt8 unsigned char
#define unt16 unsigned short
#define unt32 unsigned int
#define unt64 unsigned long long

static char* _strcpy(char* s, const char* t)
{
	while (*(s++) = *(t++));

	return s;
}

static char* _strnpst(char* s, const char* t, unsigned n)
{
	while (*t && n)
	{
		*(s++) = *(t++);
		n--;
	};

	return s;
}

static void _u32toa (unt32 value, char *string, unt8 radix)
{
        char *i, *s, t, d;

        s = i = string;

        do
        {   d = value % radix;
            value /= radix;

            if (d > 9)
                *i++ = d + 'A' - 10;
            else
                *i++ = d + '0';
        } while (value > 0);

        *i-- = '\0';

        do 
        {   t = *i;
            *i = *s;
            *s = t;

            --i;
            ++s;
        } while (s < i);
}


unsigned _strlen(const char* s)
{
	const char* c = s;
	while (*c++);
	return (unsigned)(c - s - 1);
}

void* _memcpy(void* s, const void* t, unsigned n)
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

int _max(int a, int b)
{
	return (a > b) ? a : b;
}



#include "log.c"

typedef struct
{
    unt32   magic;
} kip;

typedef struct
{
    unt8    ident[16];
    unt16   type;
    unt16   machine;
    unt32   version;
    unt32   entry;
    unt32   phoff;
    unt32   shoff;
    unt32   flags;
    unt16   ehsize;
    unt16   phentsize;
    unt16   phnum;
    unt16   shentsize;
    unt16   shnum;
    unt16   shstrndx;
} elf32_header __attribute__ ((packed));

void pm32(void)
{
    unsigned i;

    unt32 *arch_pm32_pagedirectory = 0x00610000;
    unt32 *arch_pm32_rootthread = 0xD0000000;
    unt32 *arch_pm32_pagetable;

    kip   *arch_kip = 0x00700000;

    /* Zero fill kernel memory.                                               */
    asm
    (
        "rep stosl;"
        :
        :
        "a" (0x00000000),               /* Value        : 0x00000000          */
        "c" (0x00100000),               /* Lenght       :    4 MB             */
        "D" (0x00600000)                /* Start        :    4 MB             */
    );

    /* Move Core from 0x00020000 to 0x00400000.                               */
    asm
    (
        "rep movsl;"
        :
        :
        "c" (0x00004000),               /* Lenght       :   64 kB             */
        "S" (0x00020000),               /* Source       :  128 kB             */  
        "D" (0x00400000)                /* Destination  :    4 MB             */
    );

    /* Move Root from 0x00060000 to 0x00800000.                               */
    asm
    (
        "rep movsl;"
        :
        :   "c" (0x00010000),           /* Lenght       :  256 kB             */
            "S" (0x00060000),           /* Source       :  384 kB             */  
            "D" (0x00800000)            /* Destination  :    8 MB             */
    );

    /* Build the Kernel Information Page.                                     */
    arch_kip->magic = 0xDEADBEEF;

    /* Move Core from 0x00401000 to 0x00400000.                               */
    asm
    (
        "rep movsl;"
        :
        :
        "c" (0x00004000),               /* Lenght       :   64 kB             */
        "S" (0x00401000),               /* Source       :    4 MB +    4 kB   */  
        "D" (0x00400000)                /* Destination  :    4 MB             */
    );

    /* Create the Page Directory.                                             */
    arch_pm32_pagedirectory[0x000/4] = 0x00611007;
    arch_pm32_pagedirectory[0x004/4] = 0x00617007;
    arch_pm32_pagedirectory[0x008/4] = 0x00618007;

    arch_pm32_pagedirectory[0x00C/4] = 0x00503007;
    arch_pm32_pagedirectory[0x010/4] = 0x00504007;
    arch_pm32_pagedirectory[0x014/4] = 0x00505007;
    arch_pm32_pagedirectory[0x018/4] = 0x00506007;
    arch_pm32_pagedirectory[0x01C/4] = 0x00507007;
    arch_pm32_pagedirectory[0x020/4] = 0x00508007;
    arch_pm32_pagedirectory[0x024/4] = 0x00509007;
    arch_pm32_pagedirectory[0x028/4] = 0x0050A007;
    arch_pm32_pagedirectory[0x02C/4] = 0x0050B007;
    arch_pm32_pagedirectory[0x030/4] = 0x0050C007;
    arch_pm32_pagedirectory[0x034/4] = 0x0050D007;
    arch_pm32_pagedirectory[0x038/4] = 0x0050E007;
    arch_pm32_pagedirectory[0x03C/4] = 0x0050F007;

    arch_pm32_pagedirectory[0xD00/4] = 0x00616007;
    arch_pm32_pagedirectory[0xFF0/4] = 0x00615007;
    arch_pm32_pagedirectory[0xFF4/4] = 0x00612007;
    arch_pm32_pagedirectory[0xFF8/4] = 0x00613007;
    arch_pm32_pagedirectory[0xFFC/4] = 0x00614007;

    /* Create the Page Tables.                                                */
    for (i = 0; i < 1024; i++) ((unt32*)(0x00611000))[i] = i * 4096 + 0x000007;

    for (i = 0; i < 1024; i++) ((unt32*)(0x00500000))[i] = i * 4096 + 0x0000007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00501000))[i] = i * 4096 + 0x0400007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00502000))[i] = i * 4096 + 0x0800007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00503000))[i] = i * 4096 + 0x0C00007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00504000))[i] = i * 4096 + 0x1000007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00505000))[i] = i * 4096 + 0x1400007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00506000))[i] = i * 4096 + 0x1800007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00507000))[i] = i * 4096 + 0x1C00007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00508000))[i] = i * 4096 + 0x2000007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00509000))[i] = i * 4096 + 0x2400007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x0050A000))[i] = i * 4096 + 0x2800007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x0050B000))[i] = i * 4096 + 0x2C00007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x0050C000))[i] = i * 4096 + 0x3000007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x0050D000))[i] = i * 4096 + 0x3400007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x0050E000))[i] = i * 4096 + 0x3800007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x0050F000))[i] = i * 4096 + 0x3C00007;

    for (i = 0; i < 1024; i++) ((unt32*)(0x00612000))[i] = i * 4096 + 0xC00007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00613000))[i] = i * 4096 + 0x400007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00616000))[i] = i * 4096 + 0xE00007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00617000))[i] = i * 4096 + 0x400007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00618000))[i] = i * 4096 + 0x800007;

    (*(unt32*)(0x00614000)) = 0x00610007;
    (*(unt32*)(0x00614004)) = 0x00611007;
    (*(unt32*)(0x00614D00)) = 0x00616007;
    (*(unt32*)(0x00614FF0)) = 0x00615007;
    (*(unt32*)(0x00614FF4)) = 0x00612007;
    (*(unt32*)(0x00614FF8)) = 0x00613007;
    (*(unt32*)(0x00614FFC)) = 0x00614007;

    /* Enable Paging.                                                         */
    asm
    (
        "movl $0x00610000, %eax;"
        "movl %eax, %cr3;"
        "movl %cr0, %eax;"
        "orl $0x80000000, %eax;"
        "movl %eax, %cr0;"
    );

    /* Create the Root thread.                                                */
    arch_pm32_rootthread[1023] = 0x0000002B;    /* User SS                    */
    arch_pm32_rootthread[1022] = 0x00802000;    /* User ESP                   */
    arch_pm32_rootthread[1021] = 0x00003202;    /* User EFLAGS                */
    arch_pm32_rootthread[1020] = 0x00000023;    /* User CS                    */
    arch_pm32_rootthread[1019] = 0x00800000;    /* User EIP                   */
    arch_pm32_rootthread[1018] = 0xAAAAAAAA;    /* User EAX                   */
    arch_pm32_rootthread[1017] = 0xCCCCCCCC;    /* User ECX                   */
    arch_pm32_rootthread[1016] = 0xDDDDDDDD;    /* User EDX                   */
    arch_pm32_rootthread[1015] = 0xBBBBBBBB;    /* User EBX                   */
    arch_pm32_rootthread[1014] = 0x00802000;    /* User EBP                   */
    arch_pm32_rootthread[1013] = 0xEEEEEEEE;    /* User ESI                   */
    arch_pm32_rootthread[1012] = 0xFFFFFFFF;    /* User EDI                   */

    /* Start Core.                                                            */
    asm
    (
        "movl $0x00700000, %eax;"       /* KIP Pointer.                       */
        "movl $0xFFC00000, %esp;"
        "ljmp $0x10, $0xFF800000;"
    );


    for(;;);

}
