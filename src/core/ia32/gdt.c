/******************************************************************************/
/* Mithrill Core : IA-32 : Global Descriptor Table Management                 */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#define arch_gdt_accessed       0x00000100
#define arch_gdt_readable       0x00000200  /* Code Segments                  */
#define arch_gdt_writable       0x00000200  /* Data Segments                  */
#define arch_gdt_conforming     0x00000400  /* Code Segments                  */
#define arch_gdt_direction      0x00000400  /* Data Segments                  */
#define arch_gdt_present        0x00008000
#define arch_gdt_avail          0x00100000  /* Available for the Core         */
#define arch_gdt_reserved       0x00200000  /* Reserved Bit (DO NOT SET)      */
#define arch_gdt_default        0x00400000
#define arch_gdt_big            0x00400000
#define arch_gdt_granularity    0x00800000

#define arch_gdt_tss32          0x00000900
#define arch_gdt_data           0x00001000
#define arch_gdt_code           0x00001800


struct
{
    word a;
    word b;
} *arch_gdt_table = ((void*)(0xFF480000));

void arch_gdt_init(void)
{    
    logItem("Initializing GDT Management");

    (*(unsigned short*)(0xFF480002)) = 0x0800;
    (*(word*)(0xFF480004)) = 0xFF480000;

    /*    0     0x00    Null Selector                                         */
    /*    1     0x08    TSS Selector                                          */
    /*    2     0x10    Kernel Code                                           */
    /*    3     0x18    Kernel Data                                           */
    /*    4     0x20    User Code                                             */
    /*    5     0x28    User Data                                             */
    /*    6     0x30    UTCB Segment                                          */
    /*    7     0x38    LDT Selector                                          */
    
    arch_gdt_set
    (
        1,
        0xFF490000,
        4096,
        arch_gdt_tss32,
        0,
        arch_gdt_present
    );

    arch_gdt_set
    (
        2,
        0x00000000,
        0xFFFFF,
        arch_gdt_code,
        0,
        arch_gdt_accessed
        | arch_gdt_present
        | arch_gdt_default
        | arch_gdt_granularity
    );

    arch_gdt_set
    (
        3,
        0x00000000,
        0xFFFFF,
        arch_gdt_data,
        0,
        arch_gdt_accessed
        | arch_gdt_present
        | arch_gdt_big
        | arch_gdt_granularity
        | arch_gdt_writable
    );

        arch_gdt_set
    (
        4,
        0x00000000,
        0xFFFFF,
        arch_gdt_code,
        3,
        arch_gdt_accessed
        | arch_gdt_present
        | arch_gdt_default
        | arch_gdt_granularity
    );

    arch_gdt_set
    (
        5,
        0x00000000,
        0xFFFFF,
        arch_gdt_data,
        3,
        arch_gdt_accessed
        | arch_gdt_present
        | arch_gdt_big
        | arch_gdt_granularity
        | arch_gdt_writable
    );

    asm("lgdt 0xFF480002;");

    logStatus(logSuccess);
}

void arch_gdt_set(word entry, word base, word limit, word type, word privelege,
                  word flags)
{
    arch_gdt_table[entry].a =
        (limit & 0x0000FFFF) | (base << 16);

    arch_gdt_table[entry].b =
        ((base & 0x00FF0000) >> 16) | (base & 0xFF000000) | (limit & 0x000F0000)
        | type | (privelege << 13) | flags;

    logHex("b", arch_gdt_table[entry].b);
}
