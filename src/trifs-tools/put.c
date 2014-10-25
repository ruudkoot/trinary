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

typedef struct
{
    char name[16];
    unt64 block;
    unt64 size;
} dir_entry_t;

int main(int argc, char* argv[])
{
    unsigned realsize;
    unsigned virtsize;
    FILE* put;
    dir_entry_t dir_entry[16];
    unsigned char* buffer;
    unsigned i;

    
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

    readblock(1, 1, dir_entry);

    for (i = 0; dir_entry[i].name[0] != '\0'; i++);

    strcpy(dir_entry[i].name, argv[3]);

    if (i > 0)
    {
        dir_entry[i].block = dir_entry[i-1].block + dir_entry[i-1].size;
    }
    else
    {
        dir_entry[0].block = 2;
    }

    dir_entry[i].size = virtsize / blocksize;

    writeblock(1, 1, dir_entry);

    buffer = malloc(virtsize);
    fseek(put, 0, SEEK_SET);
    fread(buffer, realsize, 1, put);
    
    writeblock(dir_entry[i].block, virtsize / blocksize, buffer);

    closedevice();
}

