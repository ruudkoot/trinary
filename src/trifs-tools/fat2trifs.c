/******************************************************************************/
/* Trinary File System Tools : Convert FAT to TriFS                           */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* Only FAT32 support at the moment :-(                                       */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <memory.h>

#include "config.h"
#include "../lib/bitmap.c"

#include "trifs.h"


#pragma pack(1)
typedef struct
{
    unt8    jump[3];
    unt8    system[8];
    unt16   bytespersector;
    unt8    sectorspercluster;
    unt16   reservedsectors;
    unt8    numberoffats;
    unt16   rootentries;
    unt16   legacysectors;
    unt8    media;
    unt16   legacyfatsize;
    unt16   sectorspertrack;
    unt16   numberoftracks;
    unt32   hiddensectors;
    unt32   totalsectors;
    unt32   fatsize;
    unt16   extensionflags;
    unt16   filesystemversion;
    unt32   rootcluster;
    unt16   fsinfo;
    unt16   bootsectorbackup;
    unt8    reserved[12];
    unt8    drivenumber;
    unt8    reserved1;
    unt8    bootsignature;
    unt32   volid;
    unt8    label[11];
    unt8    fstype[8];

} fat_super_t;
#pragma pack()

int main(int argc, char* argv[])
{
    
    FILE*           debugfile;
    disk_t*         disk;
    unt8*           buffer;
    fat_super_t*    fat_super;
    unsigned        i;
    unsigned        j;
    void*           fat_bitmap;
    void*           trifs_bitmap;
    unsigned        diskbitmapsize;
    unt32*          fat_buffer;

    struct
    {
        unt32       fatmetadata;
        unt32       sectorsize;
        unt32       clustersize;
        unt32       blocksize;
    } ct;

    printf("Trinary File System Tools : Convert FAT32 to TriFS\n\r"
           "Copryright (c) 2003, Rudy Koot (Trinary Technologies)\n\r"
           "\n\r"
           "This program is free software; you can redistribute it and/or modify\n\r"
           "it under the terms of the GNU General Public License as published by\n\r"
           "the Free Software Foundation; either version 2 of the License, or\n\r"
           "(at your option) any later version.\n\r");


	disk = disk_open(argv[1]);
    disk->blocksize = 512;

    fat_super = malloc(disk->blocksize);

    disk_read(disk, ((unt8*)(fat_super)), 0, 1);

    printf("\n\rBIOS Parameter Block:\n\r");
    printf("    File System Creator: %.8s\n\r", fat_super->system);
    printf("    Bytes per Sector   : %i\n\r", fat_super->bytespersector);
    printf("    Sectors per Cluster: %i\n\r", fat_super->sectorspercluster);
    printf("    Reserved Sectors   : %i\n\r", fat_super->reservedsectors);
    printf("    Number of FATs     : %i\n\r", fat_super->numberoffats);
    printf("    Root Entries       : %i\n\r", fat_super->rootentries);
    printf("    Legacy Sectors     : %i\n\r", fat_super->legacysectors);
    printf("    Media              : %X\n\r", fat_super->media);
    printf("    Legacy FAT Size    : %i\n\r", fat_super->legacyfatsize);
    printf("    Sectors Per Track  : %i\n\r", fat_super->sectorspertrack);
    printf("    Number of Tracks   : %i\n\r", fat_super->numberoftracks);
    printf("    Hidden Sectors     : %i\n\r", fat_super->hiddensectors);
    printf("    Total Sectros      : %i\n\r", fat_super->totalsectors);
    printf("    FAT Size           : %i\n\r", fat_super->fatsize);
    printf("    Extension Flags    : %i\n\r", fat_super->extensionflags);
    printf("    File System Version: %X\n\r", fat_super->filesystemversion);
    printf("    Root Cluster       : %i\n\r", fat_super->rootcluster);
    printf("    File System Info   : %i\n\r", fat_super->fsinfo);
    printf("    Boot Sector Backup : %i\n\r", fat_super->bootsectorbackup);
    printf("    Drive Number       : %X\n\r", fat_super->drivenumber);
    printf("    Boot Signature     : %X\n\r", fat_super->bootsignature);
    printf("    Volume ID          : %X\n\r", fat_super->volid);
    printf("    Label              : %.11s\n\r", fat_super->label);
    printf("    File System Type   : %.8s\n\r", fat_super->fstype);

    
        printf("\n\rFile System Layout:\n\r");
    printf("    %.10i - %.10i: Boot Sector\n\r", 0, fat_super->reservedsectors - 1);
    printf("    %.10i - %.10i: FAT 1\n\r", fat_super->reservedsectors, fat_super->fatsize + fat_super->reservedsectors - 1);
    printf("    %.10i - %.10i: FAT 2\n\r", fat_super->fatsize + fat_super->reservedsectors, 2 * fat_super->fatsize + fat_super->reservedsectors - 1);
    printf("    %.10i - %.10i: Data Area\n\r", 2 * fat_super->fatsize + fat_super->reservedsectors, fat_super->totalsectors - 1);

    /* Setup the Conversion Table.                                            */

    ct.blocksize = 4096;

    ct.sectorsize = fat_super->bytespersector;
    ct.clustersize = fat_super->bytespersector * fat_super->sectorspercluster;
    ct.fatmetadata = (fat_super->reservedsectors + fat_super->fatsize * fat_super->numberoffats) * fat_super->bytespersector;

    if (ct.fatmetadata % ct.blocksize != 0)
    {
        printf("Sorry the FAT alignment of this disk SUCKS!!!");
        exit(1);
    }

    if (ct.clustersize < ct.blocksize)
    {
        printf("The new Block Size must be small or equal to the original Cluster Size.");
        exit(1);
    }

    printf("\n\rConversion Settings:\n\r");
    printf("    Block Size         : %i bytes\n\r", ct.blocksize);
    printf("    Sector Size        : %i bytes\n\r", ct.sectorsize);
    printf("    Cluster Size       : %i bytes\n\r", ct.clustersize);
    printf("    FAT Metadata Size  : %i blocks\n\r", ct.fatmetadata / ct.blocksize);

    

    printf("\n\rTriFS Settings:\n\r");
    printf("    Block Size         : %i kB\n\r", 4);
    printf("    Band Size          : %i MB\n\r", 256);


    printf("\n\rConverting File System:\n\r");

    printf("    Loading FAT\n\r");

    fat_buffer = malloc(fat_super->fatsize * fat_super->bytespersector);
    disk_read(disk, fat_buffer, fat_super->reservedsectors, fat_super->fatsize);
    
    printf("    Building FAT Bitmap\n\r");

    diskbitmapsize = fat_super->totalsectors / 8 + !!(fat_super->totalsectors / 8);
    fat_bitmap = malloc(diskbitmapsize);
    memset(fat_bitmap, 0, diskbitmapsize);
    
    for (i = 0; i < fat_super->reservedsectors + fat_super->fatsize * fat_super->numberoffats; i++)
    {
        bitset(fat_bitmap, i);
    }

    for (i = 0; i < fat_super->fatsize * fat_super->bytespersector / 4; i++)
    {
        if (fat_buffer[i] != 0)
        {
            for (j = 0; j < fat_super->sectorspercluster; j++)
            {
                bitset(fat_bitmap, i * fat_super->sectorspercluster + (fat_super->reservedsectors + fat_super->fatsize * fat_super->numberoffats) - (2 * fat_super->sectorspercluster) + j);
            }
        }
    }

    printf("    Building TriFS Bitmap\n\r");

    trifs_bitmap = malloc(diskbitmapsize);
    memset(trifs_bitmap, 0, diskbitmapsize);

    for (i = 0; i < fat_super->totalsectors / (256 * 1024 * 2); i++)
    {
        for (j = 0; j < 32; j++)
        {
            bitset(trifs_bitmap, i * (256 * 1024 * 2) + j);
        }
    }

    printf("    Moving Conflicting Clusters\n\r");

    printf("    Building Directory Structure\n\r");

    printf("    Updating Metadata\n\r");


    debugfile = fopen("c:\\fat.bitmap.dump", "wb");
    fwrite(fat_bitmap, diskbitmapsize, 1, debugfile);
    fclose(debugfile);

    debugfile = fopen("c:\\trifs.bitmap.dump", "wb");
    fwrite(trifs_bitmap, diskbitmapsize, 1, debugfile);
    fclose(debugfile);
    
    
    return 0;
}