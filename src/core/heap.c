/******************************************************************************/
/* Heap Management                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This module implements the Core's Heap Management.                         */
/******************************************************************************/

unsigned heap_start;

void heap_init(void)
{
    logItem("Initializing Heap Management");
    heap_start = 0xC0100000;
    logStatus(logSuccess);
}

void* heap_alloc(unsigned size)
{
    unsigned address;
    address = heap_start;
    
    heap_start += size;
    heap_start += heap_start % 32;

    return ((void*)address);
}

void heap_free(void* address)
{
    return;
}
