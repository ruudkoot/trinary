/******************************************************************************/
/* File Utilities : Set File Size                                             */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

/******************************************************************************/
/* This utility sets the size of the files to a specified amount. If that     */
/* amount is smaller than the original file, the file is trucated, else it is */
/* padded with NULLs.                                                         */
/******************************************************************************/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	HANDLE file;
    unsigned oldsize, newsize, read;
    void *oldbuffer, *newbuffer;

    if (argc != 3)
    {
        puts("Trinary File Utilities : Set File Size\n"
             "Copyright (c) 2003, Rudy Koot (Trinary Technologies)");

        return 1;
    }
    
    file = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

    if (file == INVALID_HANDLE_VALUE)
    {
        printf("Error opening %s", argv[1]);
        return 1;
    }

    oldsize = GetFileSize(file, 0);
    oldbuffer = new unsigned char[oldsize];
    ReadFile(file, oldbuffer, oldsize, (unsigned long*)(&read), 0);
    
    newsize = atoi(argv[2]);

    if (newsize > oldsize)
    {
        newbuffer = new unsigned char[newsize];
        memset(newbuffer, 0, newsize);
        memcpy(newbuffer, oldbuffer, oldsize);

        SetFilePointer(file, 0, 0, FILE_BEGIN);
        WriteFile(file, newbuffer, newsize, (unsigned long*)(&read), 0);
    }
    else
    {
        SetFilePointer(file, newsize, 0, FILE_BEGIN);
        SetEndOfFile(file);
    }

    return 0;
}
