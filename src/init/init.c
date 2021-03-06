/******************************************************************************/
/* System Initialization                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* IMPORTANT THINGS TO DO: * Add support for a heap.                          */
/*                         * Defuck the source code.                          */
/******************************************************************************/

#define word unsigned int

#define NOMEM
#include "../lib/config.c"
#include "../lib/lib.c"

#include "mem.c"
#include "heap.c"

#include "repository.c"

#include "ia32/ibm/log.c"
#include "ia32/ibm/disk.c"
#include "ia32/ibm/system.c"
#include "ia32/ibm/a20.c"
#include "ia32/ibm/memory.c"

#include "ibm.c"
#include "trifs.c"
#include "fat.c"
#include "ext2.c"

extern void Aye(void);


struct
{
    unt16 limit __attribute__ ((packed));
    unt32 base __attribute__ ((packed));
}  idt48;

struct
{
    unt16 limit __attribute__ ((packed));
    unt32 base __attribute__ ((packed));
} gdt48;

struct
{
    unt16 w1 __attribute__ ((packed));
    unt16 w2 __attribute__ ((packed));
    unt8 b1 __attribute__ ((packed));
    unt8 t1 __attribute__ ((packed));
    unt8 t2 __attribute__ ((packed));
    unt8 b2 __attribute__ ((packed));
} gdt[3];

unt64 debugdata;

int disk_read(void* buffer, unsigned block, unsigned drive)
{

    unsigned cylinder, head, sector, temp;
    unsigned status;

    /* convert the sector number to a CHS address. We use the formula         *
     *     C = B / (Nh * Ns)                                                  *
     *     t = B % (Nh * Ns)                                                  *
     *     H = t / Ns                                                         *
     *     S = (t % Ns) + 1                                                   */

    cylinder    = block / (18 * 2);
    temp        = block % (18 * 2);
    head        = temp / 18;
    sector      = (temp % 18) + 1;

    asm
    (
        "stc;"
        "int $0x13;"
        "sti;"
        "jnc disk_read_done;"
        "xorw $0, %%ax;"
        "disk_read_done:"
        :
        "=a" (status)
        :
        "a" (0x0201),
        "b" (buffer),
        "c" (cylinder * 256 + sector),
        "d" (head * 256 + drive)
    );

    return (status >> 8);
}



void init8259(void)
{
    asm
    (
	    "mov $0x11, %al;"
	    "out %al, $0x20;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "out %al, $0xA0;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "mov $0x20, %al;"
	    "out %al, $0x21;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "mov $0x28, %al;"
	    "out %al, $0xA1;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "mov $0x04, %al;"
	    "out %al, $0x21;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "mov $0x02, %al;"
	    "out %al, $0xA1;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "mov $0x01, %al;"
	    "out %al, $0x21;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "out %al, $0xA1;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "mov $0x00, %al;"
	    "out %al, $0x21;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"

	    "out %al, $0xA1;"
	    "/*jmp .+2;*/"
	    "/*jmp .+2;*/"
    );
}



void entry(void)
{
    /**/

    unsigned i;
    unt8 buffer[2048];



    log_item("Initializing Repository");
    log_status(log_status_success);
    log_subitem("Trinary File System");
    log_subitem("FAT12 / FAT16 / FAT32");
    log_subitem("Ext2 FS");

    heap_init(0xD000, 0x1000);

    disk_init();

    trifs_list();
    trifs_load();

    /**/ memory_detect(); /**/

    asm
    (
        "movw $0x03F2, %dx;"
        "xorb %al, %al;"
        "outb %al, %dx;"

        "cli;"
    );

    a20_enable(0);

    init8259();

    idt48.limit = 0xABCD;
    idt48.base = 0x12345678;

    gdt48.limit = 2048;
    gdt48.base = ((unsigned)(gdt));

    gdt[0].b1 = 0; gdt[0].b2 = 0; gdt[0].w2 = 0;
    gdt[0].w1 = 0; gdt[0].t1 = 0; gdt[0].t2 = 0;

    gdt[2].b1 = 0; gdt[2].b2 = 0; gdt[2].w2 = 0;
    gdt[2].w1 = 0xFFFF; gdt[2].t1 = 0x9A; gdt[2].t2 = 0xCF;

    gdt[3].b1 = 0; gdt[3].b2 = 0; gdt[3].w2 = 0;
    gdt[3].w1 = 0xFFFF; gdt[3].t1 = 0x92; gdt[3].t2 = 0xCF;

    asm
    (
        "lidt %0;"
        "lgdt %1;"
        :
        :
        "m" (idt48),
        "m" (gdt48)
    );

	asm
    (
        "movl %%edx, code32start;"
        "xorl %%eax, %%eax;"
	    "movl %%eax, %%cr3;"
        "movl %%cr0, %%eax;"
	    "orl $0x00000001, %%eax;"
	    "movl %%eax, %%cr0;"
        "jmp flush;"
        "flush:"
        
        /* jmpi 0x0010, 0x10000 */
        ".byte 0x66, 0xea;"
        "code32start: .long 0x10000;"
        ".word 0x0010;"

        "cli; hlt;"
        :
        :
        "d" (((unsigned)(Aye)))
    );
   
    return;
}
