/******************************************************************************/
/* Boot : IA-32 : IBM : TriFS Boot Sector                                     */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

.arch i8086, jumps;
.code16;
.text;
.globl boot_entry;

/******************************************************************************/
/* This function is the entry point of the boot sector. The first thing we do */
/* is setting up the segments and stack frame. We only have 24 bytes, before  */
/* we have to jump to next section that is reserved for the boot code.        */
/******************************************************************************/
boot_entry:

    cli;
    xorw %ax, %ax;
    movw %ax, %ds;
    movw %ax, %es;
    movw %ax, %ss;
    movw $0x7C00, %sp;
    ljmp $0, $start;

boot_setcursorposition:
	movb $0x02, %ah
	movb $0x00, %bh
	int $0x10
	ret

    /* Pad the unused space with 0's or give an error message if we've        *
     * written to much code.                                                  */
    . = 24;

/******************************************************************************/
/* This section defines the physical disk geometry structure. It might be     */
/* nicer to use a BIOS call or probing to automagically detect these values,  */
/* but it's unlikely we have enough space in the boot sector to do that.      */
/******************************************************************************/
cylinders:      .word 80;
heads:          .word 2;
sectors:        .word 18;
sectorsize:     .word 512;

/******************************************************************************/
/* This section defines the Root Node.                                        */
/******************************************************************************/
type:           .quad 0;
id:             .quad 0;
a:              .quad 0;
blocksize:      .quad 0;
blockcount:     .quad 0;
bandsize:       .quad 0;
e:              .quad 0;
f:              .quad 0;
g:              .quad 0;
h:              .quad 0;
initfilenode:   .quad 0;
j:              .quad 0;
k:              .quad 0;
logsize:        .quad 0;
m:              .quad 0;
n:              .quad 0;
o:              .quad 0;
platform:       .quad 0;
q:              .quad 0;
rootdirectory:  .quad 0;
s:              .quad 0;
fstype:         .quad 0;
uid:            .quad 0;
version:        .quad 0;
w:              .quad 0;
x:              .quad 0;
y:              .quad 0;
z:              .quad 0;

boot_title:     .asciz "Mithrill"

boot_writestring:
	cld;
	1:
                lodsb;
                orb %al, %al;
                jz 1f;
                movb $0x0E, %ah;
                movw $0x000F, %bx;
                int $0x10;
                jmp 1b;
	1:
                ret;

/******************************************************************************/
/* This function locates Init on disk, loads it into mememory and executes    */
/* it.                                                                        */
/******************************************************************************/
start:

    /* Because this code will only be used for floppy disk we don't use the   *
     * interrupt 13 extensions, and will there fore be limited to disk sizes  *
     * of 528 MB or 8 GB (depending wheter or not the BIOS supports and uses  *
     * translation), which sould obviously be enough for floppy disk. This    *
     * should be changed, because this code can then also be used for         *
     * dedicated (unpartitioned) disks.                                       *
     *                                                                        *
     * Because we use 16 bit code and 32 bit divides and multiplies, the      *
     * maximum number of blocks is limited to 4 billion, which should still   *
     * be enough to support disks up to 2 TB. I want to add check, that 
     *
     * blocks aren't located above that limit.                                */
	
    /* Detect the type of videocard, so we can use the right color sheme.     */
    int $0x11;
	testb $0x30, %al;
	movw $0x0070, %bx
	movw $0x0007, %ax;
	je 1f;
	movb $0x1f, %bl
	movb $0x03, %al;
    1:
	int $0x10;

	/* Hide the cursor.                                                       */
	movw $0x2000, %cx;
	movb $0x01, %ah;
	int $0x10;

    /* Draw the titlebar.                                                     */
	movw $0x0800, %cx;
	movw $0x0900, %ax;
	int $0x10;

	movw $0x0600, %ax;
	movb $0x0F, %bh;
	movw $0x0102, %cx;
	movw $0x184F, %dx;
	int $0x10;

    /* Draw the caption.                                                      */
    movw $0x0024, %dx;
	call boot_setcursorposition;
	movw $boot_title, %si;
	call boot_writestring;

    /* Load the file node of Init into memory. The block of the node is       *
     * stored in the superblock. We can do this, because file nodes, usualy   *
     * don't move around. This has two advantage. We don't have to parse      *
     * large parts of the filesystem (at least the root directory, maybe even *
     * more directories, which is quite complex, because we have to take      *
     * heavy fragmentation into account, and parse the hashed and regular     *
     * filenames), which requires too much code and is quite slow, because of *
     * excesive disk access. An additional advantage is the fact that we can  *
     * choose any file to boot from.                                          *
     *                                                                        *
     * The size of the file node is limited to 32 kB, although it can be      *
     * extended to 64 kB or even more.                                        *
     *                                                                        */

    movw $1, %si;
    movw $0, %di;
    movw $0x8000, %bx;
    call loadblock;

    movw 0x8010, %si;
    movw 0x8012, %di;
    movw 0x8018, %cx;
    movw $0x1000, %bx;

    1:
        pushw %cx;
        pushw %si;
        pushw %di;
        pushw %bx;
        call loadblock;
        popw %bx;
        popw %di;
        popw %si;
        addw $512, %bx;
        addw $1, %si;
        adcw $0, %di;
        popw %cx;
    loop 1b;

    movw $0, %sp;
    ljmp $0x0000, $0x1000

/******************************************************************************/
/* loadblock - Load Block into Memory                                         */
/*                                                                            */
/* This function loads a block into memory independant of the disk's geometry */
/* or sector size.                                                            */
/*                                                                            */
/* THIS FUNCTION ASSUMES (AT THE MOMENT) THAT BOTH THE SECTOR AND THE BLOCK   */
/* SIZE ARE 512 BYTES!                                                        */
/******************************************************************************/
loadblock:

    /* Calculate the number of sectors per block. If DX doesn't equal 0 eiter *
     * the sector size or the block size was invalid. We do not check for     *
     * this condition at the moment.                                          */

    call loadsector;

    ret;

/******************************************************************************/
/* loadsector - Load Sector into Memory                                       */
/*                                                                            */
/* %di:%si: sector                                                            */
/* %bx: address to load                                                       */
/*                                                                            */
/* Destroys ALL registers (except SP)                                         */
/******************************************************************************/
loadsector:

    /* Convert the sector number to a CHS address. We use the formula         *
     *     C = B / (Nh * Ns)                                                  *
     *     t = B % (Nh * Ns)                                                  *
     *     H = t / Ns                                                         *
     *     S = (t % Ns) + 1                                                   */
    movw sectors, %ax;
    mulw heads;
    movw %ax, %bp;
    movw %si, %ax;
    movw %di, %dx;
    divw %bp;
    movb %al, %ch;
    movw %dx, %ax;
    xorw %dx, %dx;
    divw sectors;
    incw %dx
    movb %dl, %cl;
    movb %al, %dh;

    /* The drive to load the sectors from!                                    */
    xorb %dl, %dl;

    mov $0x0201, %ax;
    int $0x13;

    ret;

    . = 510;
    .byte 0x55;
    .byte 0xAA;
