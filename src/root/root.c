/******************************************************************************/
/* Trinary Operating System : Root Server                                     */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

#define NOMEM
#include "../lib/config.c"
#include "../lib/lib.c"

/******************************************************************************/
/* Thsi will one day become the root server, the server that provides basic   */
/* operating system features like process, file and network management which, */
/* unlike most popular operating systems, do not resides inside the kernel.   */
/*                                                                            */
/* At the moment it is used to test the core and it quite a mess for that     */
/* reason. It is highly unlikely that any of this code will make it into the  */
/* real root server.                                                          */
/******************************************************************************/

typedef unsigned short io_port_t;

typedef enum
{	ata_locationMaster,
	ata_locationSlave
}  ata_location_t;

typedef struct
{	io_port_t			portData;
	union
	{	io_port_t		portError;
		io_port_t		portFeatures;
	};
	io_port_t			portCount;
	io_port_t			portBlockLow;
	io_port_t			portBlockMid;
	io_port_t			portBlockHigh;
	io_port_t			portDevice;
	union
	{	io_port_t		portStatus;
		io_port_t		portCommand;
	};
	union
	{	io_port_t		portAlternate;
		io_port_t		portControl;
	};
}  ata_controller_t;

typedef struct
{	ata_controller_t	controller;
	ata_location_t		location;
} ata_disk_t;

typedef struct
{	ata_disk_t			disk;
	unsigned char		features;
	unsigned int		block;
	unsigned char		count;
	unsigned char		command;
} ata_command_t;

void ata_command(ata_command_t command);
void ata_clearInterrupt(ata_controller_t controller);
void ata_inputPio(ata_controller_t controller, unsigned char* buffer, unsigned n);
void ata_readSector(ata_disk_t disk, unsigned int block, unsigned char count);
void io_write(io_port_t port, unsigned char value);

void out(char* output)
{
    int i;
    unsigned source, destination;
    char* m = (char*)0xB8E68;

    for (i = 0; i < 22; i++)
    {
        source        = 0xB8000 + 160 * i + 488;
        destination    = 0xB8000 + 160 * i + 328;

        memcpy((void*)destination, (void*)source, 148);
    }

    while (*output)
    {
        *m = *output;
        m++;
        *m = 0x07;
        m++;
        output++;
    }
}

void cmain(void)
{
	unsigned i;
	char s[30];
    ata_disk_t disk;
    unsigned char buffer[513];
    unsigned char a;

    out("");
	out("");
	out("************************************************************");
    out("");
	out("Root Server Running!");
	out("");
    out("************************************************************");
    out("");
	out("");

    disk.location = ata_locationMaster;
    disk.controller.portData = 0x1f0;
    disk.controller.portError = 0x1f1;
    disk.controller.portCount = 0x1f2;
    disk.controller.portBlockLow = 0x1f3;
    disk.controller.portBlockMid = 0x1f4;
    disk.controller.portBlockHigh = 0x1f5;
    disk.controller.portDevice = 0x1f6;
    disk.controller.portCommand = 0x1f7;
    disk.controller.portAlternate = 0x3f6;

    /* TEST                                                                   */
    
    asm
    (
        "pushl %%ebp;"
        "int $0xC1;"
        "popl %%ebp"
        :
        "=a" (i)
    );

    u32toa(i, s, 10);
    out(s);

    asm
    (
        "pushl %%ebp;"
        "int $0xC2;"
        "popl %%ebp"
        :
        :
        "a" (i),
        "b" (0x00810000)
    );

    /* PING                                                                   */
    
    asm
    (
        "pushl %%ebp;"
        "int $0xC1;"
        "popl %%ebp"
        :
        "=a" (i)
    );

    u32toa(i, s, 10);
    out(s);

    asm
    (
        "pushl %%ebp;"
        "int $0xC2;"
        "popl %%ebp"
        :
        :
        "a" (i),
        "b" (0x00820000)
    );

    /* PONG                                                                   */
    
    asm
    (
        "pushl %%ebp;"
        "int $0xC1;"
        "popl %%ebp"
        :
        "=a" (i)
    );

    u32toa(i, s, 10);
    out(s);

    asm
    (
        "pushl %%ebp;"
        "int $0xC2;"
        "popl %%ebp"
        :
        :
        "a" (i),
        "b" (0x00828000)
    );

    /* Start threads.                                                         */

    asm
    (
        "pushl %%ebp;"
        "int $0xC3;"
        "popl %%ebp;"
        :
        :
        "a" (1)
    );

    asm
    (
        "pushl %%ebp;"
        "int $0xC3;"
        "popl %%ebp;"
        :
        :
        "a" (2)
    );

    asm
    (
        "pushl %%ebp;"
        "int $0xC3;"
        "popl %%ebp;"
        :
        :
        "a" (3)
    );


  /*  for (;;)
    {*/
        ata_readSector(disk, rand() * 1024, 1);

        asm
        (
            "pushl %%ebp;"
            "int $0xC0;"
            "popl %%ebp;"
            :
            :
            "a" (0),
            "d" (5)
        );

        ata_inputPio(disk.controller, buffer, 256);
        ata_clearInterrupt(disk.controller);

        for (i = 0; i < 512; i++)
        {
            if (buffer[i] == '\0') buffer[i] = ' ';
            if (i % 2)
            {
                a = buffer[i];
                buffer[i] = buffer[i-1];
                buffer[i-1] = a;
            }
        }

        buffer[60] = '\0';
        out(buffer);
  /*  }*/

    out("");
	out("");
	out("************************************************************");
    out("");
	out("Root Server Halted!");
	out("");
    out("************************************************************");
    out("");
	out("");

    for (;;);  
}

void ata_command(ata_command_t command)
{	io_write(command.disk.controller.portFeatures,	command.features);
	io_write(command.disk.controller.portCount,		command.count);
	io_write(command.disk.controller.portBlockLow,	(command.block & 0x000000FF) >> 0);
	io_write(command.disk.controller.portBlockMid,	(command.block & 0x0000FF00) >> 8);
	io_write(command.disk.controller.portBlockHigh,	(command.block & 0x00FF0000) >> 16);
	io_write(command.disk.controller.portDevice,
		((command.block & 0x0F000000) >> 24) + (command.disk.location << 4) + 0xE0);
	io_write(command.disk.controller.portCommand, command.command);
}

void ata_clearInterrupt(ata_controller_t controller)
{
    asm
    (
        "inb %%dx, %%al;"
        :
        :
        "d" (controller.portStatus)
    );
}

void ata_inputPio(ata_controller_t controller, unsigned char* buffer, unsigned n)
{
    asm
    (
        "cld;"
        "rep insw;"
        :
        :
        "c" (n),
        "d" (controller.portData),
        "D" (buffer)
    );
}

void ata_readSector(ata_disk_t disk, unsigned int block, unsigned char count)
{	ata_command_t	command;

	command.block		= block;
	command.count		= count;
	command.disk		= disk;
	command.features	= 0x00;
	command.command		= 0xEC;

	ata_command(command);
}

void io_write(io_port_t port, unsigned char value)
{
    asm
    (
        "outb %%al, %%dx;"
        :
        :
        "a" (value),
        "d" (port)
    );
}
