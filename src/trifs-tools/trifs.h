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

typedef struct
{
    unt64 reserved[4];
    string type[8];
    unt64 id;
    unt64 a;
    unt64 blocksize;
    unt64 blockcount;
    unt64 bandsize;
    unt64 e;
    unt64 f;
    unt64 g;
    unt64 h;
    unt64 initfilenode;
    unt64 j;
    unt64 k;
    unt64 logsize;
    unt64 m;
    unt64 n;
    unt64 o;
    unt64 platform;
    unt64 q;
    unt64 rootdirectory;
    unt64 s;
    unt64 fstype;
    unt64 uid;
    unt64 version;
    unt64 w;
    unt64 x;
    unt64 y;
    unt64 z;
} superblock;

int readblock(unsigned block, unsigned count, unsigned char* buffer);

int createdevice(char* name)
{
    device = fopen(name, "w+b");

    if (device == NULL)
    {
        printf("mkfs: Could not open \'%s\'\n", name);
        exit(1);
    }

    return 0;
}

int opendevice(char* name)
{
    union
    {
        unsigned char* data;
        superblock* sb;
    } root;
    
    device = fopen(name, "r+b");

    if (device == NULL)
    {
        printf("mkfs: Could not open \'%s\'\n", name);
        exit(1);
    }

    blocksize = 256;
    root.data = malloc(blocksize);
    readblock(0, 1, root.data);

    blocksize = root.sb->blocksize;
    free(root.data);

    return 0;
}

void closedevice(void)
{
    fclose(device);
}

int readblock(unsigned block, unsigned count, unsigned char* buffer)
{
    fseek(device, block * blocksize, SEEK_SET);
    fread(buffer, blocksize, count, device);
    fflush(device);

    return 0;
}

int writeblock(unsigned block, unsigned count, unsigned char* buffer)
{
    fseek(device, block * blocksize, SEEK_SET);
    fwrite(buffer, blocksize, count, device);
    fflush(device);
    return 0;
}

/******************************************************************************/

typedef struct
{
	FILE* file;
	unt32 blocksize;
} disk_t;

disk_t* disk_open(string* name)
{
    disk_t* disk;
    disk = malloc(sizeof(disk_t));

    if (disk == NULL)
    {
        printf("trifs: Out of Memory");
        exit(1);
    }

    disk->file = fopen(name, "r+b");

    if (disk->file == NULL)
    {
        printf("trifs: Could not open \'%s\'\n", name);
        exit(1);
    }

	return disk;
}

void disk_read(disk_t* disk, unt8* buffer, unt64 block, unt64 count)
{
    fseek(disk->file, block * disk->blocksize, SEEK_SET);
    fread(buffer, disk->blocksize, count, disk->file);
    fflush(disk->file);
}

void disk_write(disk_t* disk, unt8* buffer, unt64 block, unt64 count)
{
    fseek(disk->file, block * disk->blocksize, SEEK_SET);
    fwrite(buffer, disk->blocksize, count, disk->file);
    fflush(disk->file);
}

void disk_close(FILE* disk)
{
	fclose(disk);
}