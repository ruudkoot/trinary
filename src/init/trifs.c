/******************************************************************************/
/* System Initialization : File System : Trinary File System                  */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

unt8 trifs_buffer[512];

void trifs_init(void)
{
}

void trifs_list(void)
{
    unt8 i;

    log_item("Disk Contents");
    
    disk_read(trifs_buffer, 1, 0);

    log_status(log_status_success);

    for (i = 0; i < 16; i++)
    {
        if (trifs_buffer[32*i] != '\0')
        {
            log_subitem(trifs_buffer + 32 * i);
        }
    }

}

void trifs_load(void)
{
    unt8 i, block, size;

    log_item("Loading Core");
    
    disk_read(trifs_buffer, 1, 0);

    size = (*(unsigned*)(trifs_buffer + 56));
    block = (*(unsigned*)(trifs_buffer + 48));

    for (i = 0; i < size; i++)
    {
        disk_read(trifs_buffer, block + i, 0);

        asm
        (
            "movw $0x2000, %%ax;"
            "movw %%ax, %%es;"
            "rep movsw;"
            "movw %%cs, %%ax;"
            "movw %%ax, %%es;"
            :
            :
            "c" (256),
            "S" (trifs_buffer),
            "D" (512 * i)
        );
    }

    log_status(log_status_success);

    log_item("Loading Root");
    
    disk_read(trifs_buffer, 1, 0);

    size = (*(unsigned*)(trifs_buffer + 88));
    block = (*(unsigned*)(trifs_buffer + 80));

    for (i = 0; i < size; i++)
    {
        disk_read(trifs_buffer, block + i, 0);

        asm
        (
            "movw $0x6000, %%ax;"
            "movw %%ax, %%es;"
            "rep movsw;"
            "movw %%cs, %%ax;"
            "movw %%ax, %%es;"
            :
            :
            "c" (256),
            "S" (trifs_buffer),
            "D" (512 * i)
        );
    }

    log_status(log_status_success);

	log_item("Loading Test");
    
    disk_read(trifs_buffer, 1, 0);

    size = (*(unsigned*)(trifs_buffer + 120));
    block = (*(unsigned*)(trifs_buffer + 112));

    for (i = 0; i < size; i++)
    {
        disk_read(trifs_buffer, block + i, 0);

        asm
        (
            "movw $0x7000, %%ax;"
            "movw %%ax, %%es;"
            "rep movsw;"
            "movw %%cs, %%ax;"
            "movw %%ax, %%es;"
            :
            :
            "c" (256),
            "S" (trifs_buffer),
            "D" (512 * i)
        );
    }

    log_status(log_status_success);

    log_item("Loading Ping");
    
    disk_read(trifs_buffer, 1, 0);

    size = (*(unsigned*)(trifs_buffer + 152));
    block = (*(unsigned*)(trifs_buffer + 144));

    for (i = 0; i < size; i++)
    {
        disk_read(trifs_buffer, block + i, 0);

        asm
        (
            "movw $0x8000, %%ax;"
            "movw %%ax, %%es;"
            "rep movsw;"
            "movw %%cs, %%ax;"
            "movw %%ax, %%es;"
            :
            :
            "c" (256),
            "S" (trifs_buffer),
            "D" (512 * i)
        );
    }

    log_status(log_status_success);

    log_item("Loading Pong");
    
    disk_read(trifs_buffer, 1, 0);

    size = (*(unsigned*)(trifs_buffer + 184));
    block = (*(unsigned*)(trifs_buffer + 176));

    for (i = 0; i < size; i++)
    {
        disk_read(trifs_buffer, block + i, 0);

        asm
        (
            "movw $0x8800, %%ax;"
            "movw %%ax, %%es;"
            "rep movsw;"
            "movw %%cs, %%ax;"
            "movw %%ax, %%es;"
            :
            :
            "c" (256),
            "S" (trifs_buffer),
            "D" (512 * i)
        );
    }

    log_status(log_status_success);
}
