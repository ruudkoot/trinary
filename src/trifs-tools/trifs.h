/******************************************************************************/
/* Trinary File System Tools                                                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

FILE* device;
unsigned blocksize;

int opendevice(char* name)
{
    device = fopen(name, "a+b");

    if (device == NULL)
    {
        printf("mkfs: Could not open \'%s\'\n", name);
        exit(1);
    }
}

int readblock(unsigned block, unsigned count, unsigned char* buffer)
{
    fseek(device, block * blocksize, SEEK_SET);
    fread(buffer, blocksize, count, device);
}

int writeblock(unsigned block, unsigned count, unsigned char* buffer)
{
    fseek(device, block * blocksize, SEEK_SET);
    fwrite(buffer, blocksize, count, device);
    fflush(device);
}