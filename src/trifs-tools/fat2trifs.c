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
/* High 4-bit CLUSTER Triming!!!!!!!!!!                                       */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <string.h>

#include "config.h"
#include "../lib/container.c"
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

typedef struct
{
    unt8    name[8];
    unt8    ext[3];
    unt8    attribute;
    unt8    nt;
    unt8    ctime10th;
    unt16   ctime;
    unt16   cdate;
    unt16   adate;
    unt16   clusterhigh;
    unt16   mtime;
    unt16   mdate;
    unt16   clusterlow;
    unt32   size;
} fat_direntry_t;

typedef struct
{
    unt8    order;
    unt16   name1[5];
    unt8    attribute;
    unt8    type;
    unt8    checksum;
    unt16   name2[6];
    unt16   reserved;
    unt16   name3[2];
} fat_lfnentry_t;

typedef struct
{
    unt32   leadsignature;
    unt8    reserved1[480];
    unt32   signature;
    unt32   freecount;
    unt32   nextfree;
    unt32   reserved2;
    unt32   tailsignature;
} fat_fsinfo_t;

#pragma pack()

    struct
    {
        unt32       fatmetadata;
        unt32       sectorsize;
        unt32       clustersize;

        unt32       blocksize;
        unt32       bandsize;
        unt32       trifsmetadata;
        unt32       disksize;
    } ct;


typedef struct
{
    string  *filename;
    unt64   creation;
    unt64   modification;
    unt64   access;
} fat_file;

        unt32*          fat_buffer;

            fat_super_t*    fat_super;

#define block2cluster(block) (block < ct.fatmetadata ? 0 : ((block - ct.fatmetadata) / ct.clustersize + 2))
#define cluster2block(cluster) (((cluster - 2) * ct.clustersize) + ct.fatmetadata)


unt8 fat_attr_readonly  = 0x01;
unt8 fat_attr_hidden    = 0x02;
unt8 fat_attr_system    = 0x04;
unt8 fat_attr_volumeid  = 0x08;
unt8 fat_attr_directory = 0x10;
unt8 fat_attr_archive   = 0x20;
unt8 fat_attr_lfn       = 0x0F;
unt8 fat_attr_lfnmask   = 0x3F;
unt8 fat_lfn_lastentry  = 0x40;




int fat_read(disk_t* disk, void* buffer, unt32 cluster, unt32 address, unt32 size)
{
    unsigned i;
    unt8* temp;

    temp = malloc(ct.clustersize * ct.blocksize);

    for (i = 0; i < address / (ct.clustersize * ct.blocksize); i++)
    {
        cluster = fat_buffer[cluster];
        if (cluster >= 0x0FFFFFF7) return 0;
    }

    disk_read(disk, temp, cluster2block(cluster), ct.clustersize);
    memcpy(buffer, temp + (address % (ct.clustersize * ct.blocksize)), size);

    free(temp);

    return 1;
}

/******************************************************************************/
/* fat_builddirectory - Build Directory Structure from FAT Volume             */
/*                                                                            */
/* disk             The volume we're converting.                              */
/* cluster          The staring cluster of the directory.                     */
/* name             The name of the directory.                                */
/*                                                                            */
/* This function recursivly builds the TriFS directory structure form the     */
/* original FAT directory structure. Note that the name is only used for      */
/* diagnostic purposes, no file system structures are base on this value.     */
/******************************************************************************/
void fat_builddirectory(disk_t* disk, unt32 cluster, string* name, unsigned indent)
{
    unsigned    i, j;
    bool        finished;
    queue       filelist;
    fat_file    file;
    unt8        lfn[2048];
    unt16       lfnposition;

    union
    {
        fat_direntry_t  file;
        fat_lfnentry_t  name;
    } entry;
    
    /* Print the name of the directory we're converting.                      */
    for (i = 0; i < indent + 1; i++) printf(" ");
    printf("%.70s\n\r", name);


    finished = false;
    lfnposition = 0;
    queue_init(&filelist);
    
    /* Read and interpret each entry in the directory.                        */
    for
    (
        i = 0;
        fat_read(disk, &entry.file, cluster, 32 * i, 32) && !finished;
        i++
    )
    {
        /* First check wether we have a directory entry or a long filename    *
         * entry.                                                             */
        if ((entry.file.attribute & fat_attr_lfnmask) != fat_attr_lfn)
        {            
            switch (entry.file.name[0])
            {
                /* This and the folowing entries aren't used, so don't bother *
                 * continuing.                                                */
                case 0x00:
                {
                    finished = true;
                    break;
                }

                /* This entry part of a deleted file, so don't interpret it.  *
                 * (Shouldn't we place this file in the Recycle Bin?)         */
                case 0xE5:
                {
                    break;
                }

                /* This entry is either the current directory (.) or the      *
                 * parent directory (..). Just ignore them, we have no use    *
                 * for them.                                                  */
                case '.':
                {
                    break;
                }

                /* This entry means we actualy want to use 0xE5, so convert   *
                 * it and continue.                                           */
                case 0x05:
                {
                    entry.file.name[0] = 0xE5;
                    /* Don't break here.                                      */
                }

                /*  Well it apears we have a valid entry, so interpet it.     */
                default:
                {
                    file.filename = malloc(12);
                    memset(file.filename, 0, 12);
                    strncpy(file.filename, entry.file.name, 11);
                    
                    //REMOVE ALL ZEROES
                    for (j = 0; j < lfnposition * 26; j += 2)
                    {
                        lfn[j / 2] = lfn[j];
                        lfn[j / 2 + 1] = '\0';
                    }

                    queue_push(&filelist, &file);

                    if (entry.file.attribute & fat_attr_directory)
                    {
                        fat_builddirectory(disk, entry.file.clusterlow + entry.file.clusterhigh * 65536, lfnposition == 0 ? file.filename : lfn, indent + 1);
                    }

                    lfnposition = 0;

                    break;
                }
            }
        }
        else
        {
            memcpy(lfn + ((entry.name.order & 0x3F) - 1) * 26,      entry.name.name1, 10);
            memcpy(lfn + ((entry.name.order & 0x3F) - 1) * 26 + 10, entry.name.name2, 12);
            memcpy(lfn + ((entry.name.order & 0x3F) - 1) * 26 + 22, entry.name.name3, 4);
 
            lfnposition++;
        }
    }
}

/******************************************************************************/
/* fat_converttime - Convert FAT Time to TriFS Time                           */
/*                                                                            */
/* date             The date of a FAT file.                                   */
/* time             The time of a FAT file.                                   */
/* tenths           The tenthsd of a seconds time of a FAT file.              */
/*                                                                            */
/* returns          THe TriFS Time.                                           */
/*                                                                            */
/* The FAT time is the standard MS-DOS / Windows time and the TriFS time is   */
/* the time used by TriOS. The tenths is only stored with the creation time   */
/* and the access time is actualy just a date.                                */
/******************************************************************************/
unt64 fat_converttime(unt16 date, unt16 time, unt8 t)
{
    /* I haven't figured a conversion algorithm out yet!                      */

    //unsigned y, m, d, h, m, s, t;



    return 0;
}

int main(int argc, char* argv[])
{
    
    FILE*           debugfile;
    disk_t*         disk;
    unt8*           buffer;
    unt8*           clusterbuffer;

    unsigned        i;
    unsigned        j;
    unsigned        k;
    void*           fat_bitmap;
    void*           trifs_bitmap;
    unsigned        diskbitmapsize;
    unt32*          cluster_buffer;

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
    ct.bandsize = (256 * 1024 * 1024) / ct.blocksize;
    ct.trifsmetadata = 4;

    ct.sectorsize = fat_super->bytespersector;
    ct.clustersize = (fat_super->bytespersector * fat_super->sectorspercluster) / ct.blocksize;
    ct.fatmetadata = ((fat_super->reservedsectors + fat_super->fatsize * fat_super->numberoffats) * fat_super->bytespersector) / ct.blocksize;
    ct.disksize = (fat_super->totalsectors * fat_super->bytespersector) / ct.blocksize;

    if (((fat_super->reservedsectors + fat_super->fatsize * fat_super->numberoffats) * fat_super->bytespersector) % ct.blocksize != 0)
    {
        printf("Sorry the FAT alignment of this disk SUCKS!!!");
        exit(1);
    }

    if (ct.blocksize > (fat_super->bytespersector * fat_super->sectorspercluster))
    {
        printf("The new Block Size must be small or equal to the original Cluster Size.");
        exit(1);
    }

    printf("\n\rConversion Settings:\n\r");
    printf("    Block Size         : %i bytes\n\r", ct.blocksize);
    printf("    Band Size          : %i blocks\n\r", ct.bandsize);
    printf("    Sector Size        : %i bytes\n\r", ct.sectorsize);
    printf("    Cluster Size       : %i blocks\n\r", ct.clustersize);
    printf("    FAT Metadata Size  : %i blocks\n\r", ct.fatmetadata);
    printf("    TriFS Metadata Size: %i blocks\n\r", ct.trifsmetadata);
    printf("    Disk Size          : %i blocks\n\r", ct.disksize);

    printf("\n\rConverting File System:\n\r");

    printf("    Loading FAT\n\r");

    fat_buffer = malloc(fat_super->fatsize * fat_super->bytespersector);
    disk_read(disk, fat_buffer, fat_super->reservedsectors, fat_super->fatsize);
    
    /* Build the FAT Bitmap, by reserving the FAT Meta Data and the allocated *
     * freestore.                                                             */
    printf("    Building FAT Bitmap\n\r");

    diskbitmapsize = ((fat_super->totalsectors * fat_super->bytespersector) / ct.blocksize + 7) / 8;
    fat_bitmap = malloc(diskbitmapsize);
    memset(fat_bitmap, 0, diskbitmapsize);
    
    for (i = 0; i < ct.fatmetadata; i++)
    {
        bitset(fat_bitmap, i);
    }

    for (i = 0; i < (fat_super->fatsize * fat_super->bytespersector) / 4; i++)
    {
        if (fat_buffer[i] != 0)
        {
            for (j = 0; j < ct.clustersize; j++)
            {
                bitset(fat_bitmap, i * ct.clustersize + j);
            }
        }
    }

    /* Build the TriFS Bitmap, by reserving the TriFS Meta Data.              */
    printf("    Building TriFS Bitmap\n\r");

    trifs_bitmap = malloc(diskbitmapsize);
    memset(trifs_bitmap, 0, diskbitmapsize);

    for (i = 0; i < ct.disksize; i += ct.bandsize)
    {
        for (j = 0; j < ct.trifsmetadata; j++)
        {
            bitset(trifs_bitmap, i + j);
        }
    }

    printf("    Moving Conflicting Clusters\n\r");


    disk->blocksize = ct.blocksize;
    buffer = malloc(ct.clustersize * ct.blocksize);

    for (i = 0; i < ct.disksize; i++)
    {
        if (bitget(trifs_bitmap, i) && bitget(fat_bitmap, i) && block2cluster(i) != 0)
        {
            printf("        %i (%i) ", i, block2cluster(i));

            for (j = 0; j < (fat_super->fatsize * fat_super->bytespersector) / 4; j++)
            {
                if (fat_buffer[j] == 0)
                {
                    printf("=> %i (%i)\n\r", j, cluster2block(j));
                    
                    disk_read(disk, buffer, i, ct.clustersize);
                    disk_write(disk, buffer, cluster2block(j), ct.clustersize);

                    for (k = 0; k < (fat_super->fatsize * fat_super->bytespersector) / 4; k++)
                    {
                        if (fat_buffer[k] == block2cluster(i))
                        {
                            fat_buffer[k] = j;
                            break;
                        }
                    }

                    fat_buffer[j] = block2cluster(i);

                    break;
                }
            }
        }
    }

    printf("    Building Directory Structure\n\r");

    fat_builddirectory(disk, fat_super->rootcluster, ":", 0);

    printf("    Updating Metadata\n\r");

    debugfile = fopen("c:\\fat.bitmap.dump", "wb");
    fwrite(fat_bitmap, diskbitmapsize, 1, debugfile);
    fclose(debugfile);

    debugfile = fopen("c:\\trifs.bitmap.dump", "wb");
    fwrite(trifs_bitmap, diskbitmapsize, 1, debugfile);
    fclose(debugfile);
    
    
    return 0;
}