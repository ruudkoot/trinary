/******************************************************************************/
/* System Initialization                                                      */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#include "../lib/config.c"
#include "../lib/lib.c"

#include "repository.c"

#include "ia32/ibm/log.c"
#include "ia32/ibm/disk.c"

#include "ibm.c"
#include "trifs.c"
#include "fat.c"
#include "ext2.c"

void entry(void)
{
    /**/

    log_item("Initializing Repository");
    log_status(log_status_success);
    log_subitem("Trinary File System");
    log_subitem("FAT12 / FAT16 / FAT32");
    log_subitem("Ext2 FS");

    disk_init();
    
    return;
}
