/******************************************************************************/
/* System Hardware Initialization                                             */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

void sys_arch_init(void);
unt8 sys_arch_ioread8(unt16 port);
unt16 sys_arch_ioread16(unt16 port);
unt32 sys_arch_ioread32(unt16 port);
void sys_arch_iowrite8(unt16 port, unt8 value);
void sys_arch_iowrite16(unt16 port, unt16 value);
void sys_arch_iowrite32(unt16 port, unt32 value);
void sys_arch_timer_init(void);
void sys_arch_timer_setfrequency(unt8 timer, unt32 frequency);

/******************************************************************************/
/* sys_arch_init - Initialize System Hardware                                 */
/*                                                                            */
/* This function initializes some of the system hardware that has to be       */
/* managed by the micro-kernel itself (interval timer, interrupt controller). */
/******************************************************************************/
void sys_arch_init(void)
{
    sys_arch_timer_init();
}

/******************************************************************************/
/* sys_arch_ioread8 - Read Byte from I/O Port                                 */
/*                                                                            */
/* This function reads a byte from one of the processor's I/O ports.          */
/******************************************************************************/
unt8 sys_arch_ioread8(unt16 port)
{
    unt8 value;
    
    asm ("inb %%dx, %%al" : "=a" (value) : "d" (port));

    return value;
}

/******************************************************************************/
/* sys_arch_ioread16 - Read Word from I/O Port                                */
/*                                                                            */
/* This function reads a word from one of the processor's I/O ports.          */
/******************************************************************************/
unt16 sys_arch_ioread16(unt16 port)
{
    unt16 value;
    
    asm ("inw %%dx, %%ax" : "=a" (value) : "d" (port));

    return value;
}

/******************************************************************************/
/* sys_arch_ioread32 - Read Double Word from I/O Port                         */
/*                                                                            */
/* This function reads a double word from one of the processor's I/O ports.   */
/******************************************************************************/
unt32 sys_arch_ioread32(unt16 port)
{
    unt32 value;
    
    asm ("inl %%dx, %%eax" : "=a" (value) : "d" (port));

    return value;
}

/******************************************************************************/
/* sys_arch_iowrite8 - Write Byte to I/O Port                                 */
/*                                                                            */
/* This function writes a byte to one of the processor's I/O ports.           */
/******************************************************************************/
void sys_arch_iowrite8(unt16 port, unt8 value)
{
    asm ("outb %%al, %%dx" : : "a" (value), "d" (port));
}

/******************************************************************************/
/* sys_arch_iowrite16 - Write Word to I/O Port                                */
/*                                                                            */
/* This function writes a word to one of the processor's I/O ports.           */
/******************************************************************************/
void sys_arch_iowrite16(unt16 port, unt16 value)
{
    asm ("outw %%ax, %%dx" : : "a" (value), "d" (port));
}

/******************************************************************************/
/* sys_arch_iowrite32 - Write Double Word to I/O Port                         */
/*                                                                            */
/* This function writes a double word to one of the processor's I/O ports.    */
/******************************************************************************/
void sys_arch_iowrite32(unt16 port, unt32 value)
{
    asm ("outl %%eax, %%dx" : : "a" (value), "d" (port));
}

/******************************************************************************/
/* sys_arch_timer_init - Initialize the Programmable Interval Timer (PIT)     */
/*                                                                            */
/* This function initializes the Intel 8254 PIT, which is present on all IBM  */
/* compatible machines.                                                       */
/*                                                                            */
/* Note: The 8254 PIT might not be available on all IA-32 machines. We should */
/* probably make a hierachical achitecture system that could look something   */
/* like this: Trinary => IA-32 => IBM.                                        */
/******************************************************************************/
void sys_arch_timer_init(void)
{
    sys_arch_timer_setfrequency(0, 2000);
}

/******************************************************************************/
/* sys_arch_timer_setfrequency - Set Timer Frequency                          */
/*                                                                            */
/* This function set the frequency of the PIT. It assumes a base clock of     */
/* 1.193181 MHz.                                                              */
/******************************************************************************/
void sys_arch_timer_setfrequency(unt8 timer, unt32 frequency)
{
    unt16 divider;

    if (frequency < 19) panic("PIT Frequency too small!");

    /* Note that my frequency differs from some standard frequencies you      *
     * find in other programs. Many use 1193180, because some of the standard *
     * works say the freqeuncy is 1.19318 MHz, this is a rounding error. The  *
     * true frequency is 1.193181666... Mhz. I've rounded it down instead of  *
     * up, because a higher frequency causes less noticable error that a      *
     * lower frequency.                                                       */
    divider = 1193181 / frequency;

    logDec("PIT : Frequency", frequency);
    logDec("PIT : Divider", divider);
   

    sys_arch_iowrite8(0x43, 0x34);
    sys_arch_iowrite8(0x40, divider & 0xFF);
    sys_arch_iowrite8(0x40, divider >> 8);
}
