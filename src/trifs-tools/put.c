/******************************************************************************/
/* Trinary File System Tools : Put File Into Image                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <memory.h>

#include "config.h"
#include "trifs.h"

int main(int argc, char* argv[])
{
    unsigned realsize;
    unsigned virtsize;
    FILE* put;
    unsigned char* blah;
    unsigned* buffer;
    unsigned mask;
	unsigned bit;
    unsigned* bufferIterator;
    int i;
    
    opendevice(argv[2]);

    put = fopen(argv[1], "rb");

    if (put == NULL)
    {
        printf("put: error opening '%s'\n", argv[1]);
        exit(1);
    }

    fseek(put, 0, SEEK_END);
    realsize = ftell(put);
    
    if (realsize % blocksize == 0)
    {
        virtsize = realsize;
    }
    else
    {
        virtsize = realsize + blocksize - (realsize % blocksize);
    }

    blah = malloc(virtsize + blocksize);
    buffer = malloc(blocksize);
    memset(blah, 0, virtsize + blocksize);

    fseek(put, 0, SEEK_SET);
    fread(blah + blocksize, realsize, 1, put);

    readblock(2, 1, ((unsigned char*)(buffer)));
    memcpy(blah + 32, "FileNode", 8);
    (*(unsigned*)(blah + 0x118)) = 4;
    (*(unsigned*)(blah + 0x120)) = virtsize / blocksize;
 
    for (i = 0; i < virtsize / blocksize + 1; i++)
    {
        bufferIterator = buffer;
        mask = 1;
        bit = 0;
    
        //Search for an entry that contains a free page
        while (*bufferIterator == 0xFFFFFFFF) bufferIterator++;

        //Search for a bit that indicates a free page
        while (*bufferIterator & mask)
        {
            mask <<= 1;
            bit++;
        }

        *bufferIterator |= mask;

        writeblock(32 * (bufferIterator - buffer) + bit, 1, blah + blocksize * i);
        printf("%i\n", 32 * (bufferIterator - buffer) + bit);
    }

    writeblock(2, 1, buffer);



}
