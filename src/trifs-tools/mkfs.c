/******************************************************************************/
/* Trinary File System Tools : Make File System                               */
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

void help(void);
int makefs(void);
int makerd(void);
int parse(int argc, char* argv[]);

int version;

int config_blocks;
int config_bandsize;

typedef struct
{
    unt64 reserved[4];
    string type[8];
    unt64 id;
    unt64 a;
    unt64 b;
    unt64 c;
    unt64 d;
    unt64 e;
    unt64 f;
    unt64 g;
    unt64 h;
    unt64 i;
    unt64 j;
    unt64 k;
    unt64 l;
    unt64 m;
    unt64 n;
    unt64 o;
    unt64 p;
    unt64 q;
    unt64 r;
    unt64 s;
    unt64 t;
    unt64 u;
    unt64 v;
    unt64 w;
    unt64 x;
    unt64 y;
    unt64 z;
} rootdir;

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        help();
        exit(0);
    }

    config_blocks = atoi(argv[2]);
    printf ("mkfs: blocks = %i\n", config_blocks);

    config_bandsize = atoi(argv[3]);
    printf("mkfs: bandsize = %i\n", config_bandsize);

    blocksize = atoi(argv[4]);
    printf("mkfs: blocksize = %i\n", blocksize);

    createdevice(argv[1]);

    printf("Building File Allocation Structure\n");
    makefs();

    printf("Building Root Directory\n");
    makerd();
}

int makefs(void)
{
    union
    {
        superblock* sb;
        unsigned char* data;
    } root;

    unsigned char* t;
    unsigned char* b;
    unsigned char* n;

    unsigned i, j;

    root.data = malloc(blocksize);
    memset(root.data, 0, blocksize);
    memcpy(root.sb->type, "RootNode", 8);
    root.sb->blocksize = 512;
    root.sb->blockcount = 2880;
    root.sb->bandsize = 36;
    root.sb->initfilenode = 3;
    root.sb->logsize = 1;
    root.sb->platform = 0xFFFFFFFFFFFFFFFF;
    root.sb->rootdirectory = 0xDEADBEEFC0DEBABE;
    root.sb->fstype = 1;
    root.sb->uid = 0xBEBADEC0EFBEADDE;
    root.sb->version = 0x20030430;

    t = malloc(blocksize);
    memset(t, 0, blocksize);
    
    b = malloc(blocksize);
    memset(b, 0, blocksize);
    b[0] = 7;

    n = malloc(blocksize);
    memset(n, 'A', blocksize);

    for (i = 0; i < config_blocks; i += config_bandsize)
    {
        root.sb->id = i / config_bandsize;
        writeblock(i, 1, root.data);
        writeblock(i + 1, 1, t);
        writeblock(i + 2, 1, b);

        for (j = 3; j < config_bandsize; j++)
        {
            writeblock(i + j, 1, n);
        }
    }

    return 0;
}

int makerd(void)
{
    union
    {
        rootdir* rd;
        unsigned char* data;
    } root;

    root.data = malloc(blocksize);
    memset(root.data, 0, blocksize);
    memcpy(root.rd->type, "FileNode", 8);
    root.data[0x118] = 4;
    
    writeblock(3, 1, root.data);

    return 0;
}

int parse(int argc, char* argv[])
{
    return 1;
}

void help(void)
{
    printf("Usage: %s [options] device\n"
           "Options:\n"
           "  -b [SIZE], --block-size [SIZE]\n"
           "                             Use blocks of the specified size.\n"
           "  --help                     Displays this help screen.\n"
           "  -v, --verbose              Displays extra status information.\n"
           "  --version                  Displays the version\n"
           "  -w [COUNT], --wipe [COUNT] Wipes free disk space 1 or COUNT times.\n"
          );
}


