/******************************************************************************/
/* Mithrill : System Initializer : Heap Support                               */
/* Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                        */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This module implements a simple heap. Items can only be allocated, not     */
/* freed.                                                                     */
/******************************************************************************/

word heap_pointer;
word heap_end;

/******************************************************************************/
/* heap_init                            Initialize Heap                       */
/******************************************************************************/
void heap_init(word start, word size)
{
    heap_pointer = start;
    heap_end = start + size;

    mem_zero(start, size);
}

/******************************************************************************/
/* heap_alloc                           Allocate from Heap                    */
/******************************************************************************/
word heap_alloc(word size)
{
    word pointer;

    heap_pointer += size;

    return pointer;
}

/******************************************************************************/
/* heap_allocaligned                    Allocate from Heap (Aligned)          */
/******************************************************************************/
word heap_allocaligned(word size, word alignment)
{
    if (heap_pointer % alignment)
    {
        heap_pointer += heap_pointer % alignment;
    }
    
    heap_alloc(size);
}
