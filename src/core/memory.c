/******************************************************************************/
/* Memory Management                                                          */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include "ia32/memory.c"

void discardable mm_init(void)
{
    mm_arch_init();
}

word vm_pnt;

void vm_init(word a)
{
    vm_pnt = a;
}

word vm_alloc(void)
{
    return (vm_pnt += 4096);
}

word vm_phys(word v)
{
    return ( (v - 0xD0000000) + 0x00E00000 );
}
