/******************************************************************************/
/* Trinary File System Tools : Install Boot Sector                            */
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
    unsigned char* boot;
    unsigned char* super;

    blocksize = 512;
    boot = malloc(blocksize);
    super = malloc(blocksize);

    opendevice(argv[1]);
    blocksize = 512;
    readblock(0, 1, boot);
    closedevice();

    opendevice(argv[2]);
    blocksize = 512;
    readblock(0, 1, super);

    memcpy(super, boot, 32);
    memcpy(super + 256, boot + 256, 256);

    writeblock(0, 1, super);
    closedevice();
}
