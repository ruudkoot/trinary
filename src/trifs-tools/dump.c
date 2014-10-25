/******************************************************************************/
/* Trinary File System Tools : Dump File System                               */
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
    union
    {
        superblock* sb;
        unsigned char* data;
    } root;

    FILE* tape;
    unsigned char* buf;
    unsigned i;

    opendevice(argv[1]);

    tape = fopen(argv[2], "wb");

    if (tape == NULL)
    {
        printf("dump: error opening %s", argv[2]);
        exit(1);
    }

    blocksize = 256;
    root.data = malloc(blocksize);

    blocksize = root.sb->blocksize;

    free(root.data);

    root.data = malloc(blocksize);
    buf = malloc(blocksize);

    readblock(0, 1, root.data);

    for (i = 0; i < 2880 /*root.sb->blockcount*/; i++)
    {
        readblock(i, 1, buf);
        fwrite(buf, blocksize, 1, tape);
    }

    return 0;
}

