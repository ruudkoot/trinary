/******************************************************************************/
/* Mithrill : System Initializer : IA-32 : IBM : Memory Detection             */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

typedef struct
{
    unt32 entry;
    unt32 index;
    unt64 base;
    unt64 size;
    unt64 type;
    char description[32];
} memory_item;

bool memory_detect_0088(void);
bool memory_detect_008a(void);
bool memory_detect_00c7(void);
bool memory_detect_da88(void);
bool memory_detect_e801(void);
bool memory_detect_e820(void);

void memory_findroms(void);

bool memory_detect(void)
{
    /* Phoenix */
    log_item("E820"); memory_detect_e820();
    
    /* Phoenix */
    log_item("E801"); memory_detect_e801();
    
    /* Phoenix */
    log_item("008A"); memory_detect_008a();

    /* AMI */
    log_item("DA88"); memory_detect_da88();
    
    /* AT */
    log_item("0088"); memory_detect_0088();
    
    /* PS/2 */
    log_item("00C7"); memory_detect_00c7();

    /* XT */
    log_item("IN12"); //memory_detect_int12();

    memory_findroms();
    
    return 0;
}

/* UNRELIABLE! NOT ALL BIOSes SET CF */
bool memory_detect_0088(void)
{
    unsigned a, d;
    unsigned cf;

    asm
    (
        "stc;"
        "int $0x15;"
        "movl $0, %0;"
        "jnc 1f;"
        "movl $1, %0;"
        "1:"
        :
        "=g" (cf),
        "=a" (a)
        :
        "a" (0x00000088)    /* Function   : 0088h                             */
    );

    if (cf) return false;

    a &= 0xFFFF;

    log_hex("AX", a);
}

/*
INT 15 U - AMI PCI BIOS - GET EXTENDED MEMORY SIZE
	AX = DA88h
Return: CF clear (successful)
	AX = 0000h
	CL:BX = extended memory size in KBytes
SeeAlso: AH=88h

*/

bool memory_detect_da88(void)
{
    unsigned b, c;
    unsigned cf;

    asm
    (
        "stc;"
        "int $0x15;"
        "movl $0, %0;"
        "jnc 1f;"
        "movl $1, %0;"
        "1:"
        :
        "=g" (cf),
        "=b" (b),
        "=c" (c)
        :
        "a" (0x0000DA88)    /* Function   : DA88h                             */
    );

    if (cf) return false;

    b &= 0xFFFF;
    c &= 0x00FF;

    log_hex("BX", b);
    log_hex("CL", c);
}

bool memory_detect_008a(void)
{
    unsigned a, d;
    unsigned cf;

    asm
    (
        "stc;"
        "int $0x15;"
        "movl $0, %0;"
        "jnc 1f;"
        "movl $1, %0;"
        "1:"
        :
        "=g" (cf),
        "=a" (a),
        "=d" (d)
        :
        "a" (0x0000008A),   /* Function   : 008Ah                             */
        "d" (0)
    );

    if (cf) return false;

    a &= 0xFFFF;
    d &= 0xFFFF;

    log_hex("AX", a);
    log_hex("DX", d);
}

/*
INT 15 - SYSTEM - later PS/2s - RETURN MEMORY-MAP INFORMATION
	AH = C7h
	DS:SI -> user supplied memory map table (see #00526)
Return: CF set on error
	CF clear if successful
Notes:	call AH=C0h and examine bit 4 of feature byte 2 to check if this
	  function is supported
	IBM classifies this function as optional
	Windows95 OSR2 reportedly does not support this function even though
	  INT 15/AH=C0h indicates that it is available (observed on several
	  different systems)
SeeAlso: AH=C0h,AH=C9h,AH=D1h,AX=E820h

Format of memory-map table structure:
Offset	Size	Description	(Table 00526)
 00h	WORD	length of table (excluding this word)
 02h	DWORD	local memory between 1M and 16M, in 1K blocks
 06h	DWORD	local memory between 16M and 4G, in 1K blocks
 0Ah	DWORD	system memory between 1M and 16M, in 1K blocks
 0Eh	DWORD	system memory between 16M and 4G, in 1K blocks
 12h	DWORD	cacheable memory between 1M and 16M, in 1K blocks
 16h	DWORD	cacheable memory between 16M and 4G, in 1K blocks
 1Ah	DWORD	1K blocks before start of non-system memory between 1M and 16M
 1Eh	DWORD	1K blocks before start of non-system memory between 16M and 4G
 22h	WORD	start segment of largest free block from C0000h-DFFFFh
 24h	WORD	size of largest free block
 26h	DWORD	reserved
*/

bool memory_detect_00c7(void)
{
    unsigned char buffer[42];
    unsigned cf;

    /* Retrieve BIOS Feature Byte 2.                                          */
    asm
    (
        "stc;"
        "int $0x15;"
        "movl $0, %0;"
        "jc 2f;"
        "testb $10, %%es:6(%%bx);"
        "jnc 2f;"
        "1:"
        "movl $1, %0;"
        "2:"
        :
        "=g" (cf)
        :
        "a" (0x000000C0)    /* Function   : 00C0h                             */
    );

    if (!cf) return false;

    asm
    (
        "clc;"
        "int $0x15;"
        "movl $0, %0;"
        "jnc 1f;"
        "movl $1, %0;"
        "1:"
        :
        "=g" (cf)
        :
        "a" (0x000000C7),   /* Function   : 00C7h                             */
        "S" (buffer)
    );

    if (cf) return false;

    /* Perhaps we should also enumerate the DDT entries? (0xD1)               */

    log_hex("C7", buffer[0]);
}

bool memory_detect_e801(void)
{
    unsigned a, b, c, d;
    unsigned cf;

    asm
    (
        "stc;"
        "int $0x15;"
        "movl $0, %0;"
        "jnc 1f;"
        "movl $1, %0;"
        "1:"
        :
        "=g" (cf),
        "=a" (a),
        "=b" (b),
        "=c" (c),
        "=d" (d)
        :
        "a" (0x0000E801),   /* Function   : E801h                             */
        "b" (0),
        "c" (0),
        "d" (0)
    );

    if (cf) return false;

    a &= 0xFFFF;
    b &= 0xFFFF;
    c &= 0xFFFF;
    d &= 0xFFFF;

    log_hex("AX", a);
    log_hex("BX", b);
    log_hex("CX", c);
    log_hex("DX", d);
}

/******************************************************************************/
/* memory_detect_e820                   Detect Memory (BIOS Function E820h)   */
/******************************************************************************/
bool memory_detect_e820(void)
{
    unsigned char buffer[20];
    unsigned c, d, i, cf, ec;
    
    log_item("Detecting Memory");

    memset(buffer, 0, 20);

    c = 0;

    do
    {
        asm
        (
            "clc;"
            "int $0x15;"
            "movl $0, %0;"
            "jnc 1f;"
            "movl $1, %0;"
            "1:"
            :
            "=g" (cf),
            "=a" (ec),
            "=b" (d)
            :
            "a" (0x0000E820),   /* Function   : E820h                         */
            "b" (c),            /* Part       : 0                             */
            "c" (20),           /* Buffer Size: 20 bytes                      */
            "d" (0x534D4150),   /* Key        : 'SMAP'                        */
            "D" (buffer)
        );

        if (cf && (ec & 0xFF00) == 0x8600)
        {
            log_item("E820 NOT SUPPORTED! SYSTEM HALTED!");
            for(;;);
        }

        if (!cf)
        {

            log_hex("Identifier", c);
            log_hex("  Base", (*(unsigned*)(buffer + 0)));
            log_hex("  Lenght", (*(unsigned*)(buffer + 8)));
            log_hex("  Type", (*(unsigned*)(buffer + 16)));

            c = d;
        }

    } while (c != 0 || cf);
}

/*
INT 12 - BIOS - GET MEMORY SIZE
Return: AX = kilobytes of contiguous memory starting at absolute address 00000h
Note:	this call returns the contents of the word at 0040h:0013h; in PC and
	  XT, this value is set from the switches on the motherboard
SeeAlso: INT 11"BIOS",INT 2F/AX=4A06h,INT 4C"Tandy 2000",MEM 0040h:0013h


  */

void memory_findroms(void)
{
    unsigned i, t;

    struct
    {
        unsigned o;
        unsigned s;
    } c;

    for (i = 0xC000; i < 0xFFFF; i += 128)
    {
        asm
        (
            "movw %%ax, %%es;"
            "movl %%es:0, %%edx;"
            "movw %%ds, %%ax;"
            "movw %%ax, %%es;"
            :
            "=d" (t)
            :
            "a" (i)
        );

        if ((t & 0xFFFF) == 0xAA55)
        {
            log_hex("Found ROM", i);
            log_dec("Size", ((t >> 16) & 0xFF) * 512);

            c.o = 3;
            c.s = i;

           /* asm
            (
                "lcall *(%%bx);"
                :
                :
                "b" (&c)
            );*/
        }
    }
}
