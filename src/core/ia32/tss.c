/******************************************************************************/
/* Mithrill Core : IA-32 : Global Descriptor Table Management                 */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

struct
{
    word plt;
    word esp0;
    word ss0;
    word esp1;
    word ss1;
    word esp2;
    word ss2;
    word cr3;
    word eip;
    word eflags;
    word eax;
    word ecx;
    word edx;
    word ebx;
    word esp;
    word ebp;
    word esi;
    word edi;
    word es;
    word cs;
    word ss;
    word ds;
    word fs;
    word gs;
    word ldt;
    word iopmbbase;
} *arch_tss = ((void*)(0xFF490000));

word arch_tss_tempstack[1024];

void arch_tss_init(void)
{
    logItem("Initializing TSS Management");

    memset(arch_tss, 0, 104);

    arch_tss->esp0  = arch_tss_tempstack + 1024;
    arch_tss->ss0   = 0x0018;
    asm("movl %%cr3, %%eax;" : "=a" (arch_tss->cr3));

    asm("movl $0x08, %eax; ltr %ax;");

    logStatus(logSuccess);
}
