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

    unt32 *arch_pm32_pagedirectory = 0x00610000;
    unt32 *arch_pm32_rootthread = 0xD0000000;
    unt32 *arch_pm32_pagetable;

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

    /* Create the Page Directory.                                             */
    arch_pm32_pagedirectory[0x000/4] = 0x00611007;
    arch_pm32_pagedirectory[0x004/4] = 0x00617007;
    arch_pm32_pagedirectory[0x008/4] = 0x00618007;
    arch_pm32_pagedirectory[0xD00/4] = 0x00616007;
    arch_pm32_pagedirectory[0xFF0/4] = 0x00615007;
    arch_pm32_pagedirectory[0xFF4/4] = 0x00612007;
    arch_pm32_pagedirectory[0xFF8/4] = 0x00613007;
    arch_pm32_pagedirectory[0xFFC/4] = 0x00614007;

    /* Create the Page Tables.                                                */
    for (i = 0; i < 1024; i++) ((unt32*)(0x00611000))[i] = i * 4096 + 0x000007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00612000))[i] = i * 4096 + 0xC00007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00613000))[i] = i * 4096 + 0x400007;
    for (i = 0; i < 1024; i++) ((unt32*)(0x00616000))[i] = i * 4096 + 0x1000007;
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
        "movl $0xFFC00000, %esp;"
        "ljmp $0x10, $0xFF800000;"
    );


    for(;;);

}
