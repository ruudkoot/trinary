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

#define unt32 unsigned int

void pm32(void)
{
    unsigned i;

    unt32 *arch_pm32_pagedirectory = /*0x00400000*/0x00010000;
    unt32 *arch_pm32_pagetable;

    /* Move Core and Root from 0x00020000 to 0x00100000.                      */
    asm
    (
        "rep movsl;"
        :
        :
        "c" (0x00080000),
        "S" (0x00020000),
        "D" (0x00100000)
    );

    /* Zero fill kernel memory.                                               */
    asm
    (
        "rep stosl;"
        :
        :
        "a" (0x00000000),               /* Value : 0x00000000                 */
        "c" (0x00001600),               /* Lenght: .. MB                      */
        "D" (0x00010000)                /* Start : . MB                       */
    );

    /* Create the Page Directory.                                             */
    arch_pm32_pagedirectory[0x000/4] = 0x00011007;
    arch_pm32_pagedirectory[0xD00/4] = 0x00016007;
    arch_pm32_pagedirectory[0xFF0/4] = 0x00015007;
    arch_pm32_pagedirectory[0xFF4/4] = 0x00012007;
    arch_pm32_pagedirectory[0xFF8/4] = 0x00013007;
    arch_pm32_pagedirectory[0xFFC/4] = 0x00014007;

    /* Create the Page Tables.                                                */
    for (i = 0; i < 1024; i++) ((unt32*)(0x00011000))[i] = i * 4096 + 0x000007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00012000))[i] = i * 4096 + 0x500007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00013000))[i] = i * 4096 + 0x100007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00016000))[i] = i * 4096 + 0xF00007;

    (*(unt32*)(0x00014000)) = 0x00010007;
    (*(unt32*)(0x00014004)) = 0x00011007;
    (*(unt32*)(0x00014D00)) = 0x00016007;
    (*(unt32*)(0x00014FF0)) = 0x00015007;
    (*(unt32*)(0x00014FF4)) = 0x00012007;
    (*(unt32*)(0x00014FF8)) = 0x00013007;
    (*(unt32*)(0x00014FF8)) = 0x00014007;

    /* Start Core.                                                            */
    asm
    (
        "movl $0x00010000, %eax;"
        "movl %eax, %cr3;"
        "movl %cr0, %eax;"
        "orl $0x80000000, %eax;"
        "movl %eax, %cr0;"
        
        "movl $0xFFC00000, %esp;"
        "ljmp $0x10, $0xFF800000;"
    );


    for(;;);

}
