/******************************************************************************/
/* IA-32 Specific PCI Management                                              */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

unsigned pci_readConfig1(unsigned bus, unsigned device, unsigned function, unsigned reg);
unsigned pci_readConfig2(unsigned bus, unsigned device, unsigned function, unsigned reg);

unsigned pci_readConfig(unsigned bus, unsigned device, unsigned function, unsigned reg)
{
    pci_readConfig1(bus, device, function, reg);
}

unsigned inline ioRead32(unsigned port)
{
    unsigned value;
    
    asm ("inl %%dx, %%eax" : "=a" (value) : "d" (port));

    return value;
}

void inline ioWrite8(unsigned port, unsigned value)
{
    asm ("outb %%al, %%dx" : : "a" (value), "d" (port));
}

void inline ioWrite32(unsigned port, unsigned value)
{
    asm ("outl %%eax, %%dx" : : "a" (value), "d" (port));
}

unsigned pci_readConfig1(unsigned bus, unsigned device, unsigned function, unsigned reg)
{
    ioWrite32(0x0CF8,
        0x80000000 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | ((reg & 0x3F << 2)));
    return ioRead32(0x0CFC);
}

unsigned pci_readConfig2(unsigned bus, unsigned device, unsigned function, unsigned reg)
{
    ioWrite8(0x0CF8, 0xF0 | ((function & 0x07) << 1 ));
    ioWrite8(0x0CFA, bus & 0xFF);
    return ioRead32(0xC000 | ((device & 0x1f) << 8) | ((reg & 0x3f) << 2));
}
