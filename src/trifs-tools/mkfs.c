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

#include "trifs.h"

void help(void);
int parse(int argc, char* argv[]);

int version = 0;

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        help();
        exit(0);
    }

    parse(argc, argv);

    opendevice(argv[1]);
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


