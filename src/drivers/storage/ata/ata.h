/******************************************************************************/
/* ATA Disk Server                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

enum ata_location_t
{	ata_locationMaster,
	ata_locationSlave
};

struct ata_controller_t
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
};

struct ata_disk_t
{	ata_controller_t	controller;
	ata_location_t		location;
};

struct ata_command_t
{	ata_disk_t			disk;
	unsigned char		features;
	unsigned int		block;
	unsigned char		count;
	unsigned char		command;
};

void ata_command(ata_command_t command);
void ata_inputPio(ata_controller_t controller, unsigned char* buffer, unsigned n);
void ata_readSector(ata_disk_t disk, unsigned int block, unsigned char count);
