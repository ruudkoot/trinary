/******************************************************************************/
/* System Initialization : Architecture Specific System Initialization        */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

unt8 sys_arch_io_read8(unt16 port);
unt16 sys_arch_io_read16(unt16 port);
unt32 sys_arch_io_read32(unt16 port);
void sys_arch_io_write8(unt16 port, unt8 value);
void sys_arch_io_write16(unt16 port, unt16 value);
void sys_arch_io_write32(unt16 port, unt32 value);

/******************************************************************************/
/* sys_arch_io_read8 - Read a byte from an I/O port                           */
/******************************************************************************/
unt8 sys_arch_io_read8(unt16 port)
{
    unt8 value;

    asm("inb %%dx, %%al;" : "=a" (value) : "d" (port));

    return value;
}


/******************************************************************************/
/* sys_arch_io_read16 - Read a word from an I/O port                          */
/******************************************************************************/
unt16 sys_arch_io_read16(unt16 port)
{
    unt16 value;

    asm("inw %%dx, %%ax;" : "=a" (value) : "d" (port));

    return value;
}


/******************************************************************************/
/* sys_arch_io_read32 - Read a dword from an I/O port                         */
/******************************************************************************/
unt32 sys_arch_io_read32(unt16 port)
{
    unt32 value;

    asm("inl %%dx, %%eax;" : "=a" (value) : "d" (port));

    return value;
}


/******************************************************************************/
/* sys_arch_io_write8 - Write a byte to an I/O port                           */
/******************************************************************************/
void sys_arch_io_write8(unt16 port, unt8 value)
{
    asm("outb %%al, %%dx;" : : "a" (value), "d" (port));
}


/******************************************************************************/
/* sys_arch_io_write16 - Write a word to an I/O port                          */
/******************************************************************************/
void sys_arch_io_write16(unt16 port, unt16 value)
{
    asm("outw %%ax, %%dx;" : : "a" (value), "d" (port));
}


/******************************************************************************/
/* sys_arch_io_write32 - Write a dword to an I/O port                         */
/******************************************************************************/
void sys_arch_io_write32(unt16 port, unt32 value)
{
    asm("outl %%eax, %%dx;" : : "a" (value), "d" (port));
}


void sys_arch_kbc_sendcommand(unt8 command)
{
    sys_arch_io_write8(0x64, command);
}

void sys_arch_kbc_senddata(unt8 data)
{
    sys_arch_io_write8(0x60, data);
}

unt8 sys_arch_kbc_readdata(void)
{
    return sys_arch_io_read8(0x60);
}

void sys_arch_kbc_waitsend(void)
{
    while (sys_arch_io_read8(0x64) & 0x02);
}

void sys_arch_kbc_waitread(void)
{
    while (sys_arch_io_read8(0x64) & 0x01);
}


void sys_arch_sig_disable(void)
{
    asm("cli;");
}

void sys_arch_sig_enable(void)
{
    asm("sti;");
}
