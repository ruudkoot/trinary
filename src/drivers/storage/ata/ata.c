/******************************************************************************/
/* ATA Disk Server                                                            */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

//Based on the ATA/ATAPI-7 Working Draft 1a (November 2002)

//I want to start out by removing some false informations about the ATA
//standard:
//
//    The 504/528 MB Limit: This is a shortcomming of the BIOS, not of the ATA
//                          standard. Since we bypass the BIOS we are not
//                          affectede by it in any way.
//    The 8 GB Limit      : This is again a BIOS limit that does not affect us.
//    The 1024 Cyl Limit  : You guessed it! Another BIOS limit.
//    The 128 GB Limit    : No not another BIOS limit. This IS an ATA limit.
//                          Luckily for us it has been solved with LBA48.
//    EIDE / Ultra ATA    : These are just some of the buzzwords made up by the
//                          marketing departments of hard disk manufactures.
//                          Forget them. They are just fancy words for some of
//                          the (unfinished) ATA standards.
//    PIO Mode 5          : While this is not an official ATA mode, many hard
//                          disks support this mode to increase speed on
//                          computers that do not support DMA.
//    Either DMA or PIO   : Windows and some BIOSes let you think hard disks
//                          must work in either PIO or DMA mode. This is not
//                          true. You can sent both readPIO and readDMA
//                          requests to disk disk. You do not have to switch it
//                          to DMA mode for example.
//    Megabyte            : Remember that a Megabyte, a Meg, an MB are 1048576
//                          bytes. Most of the time, though, manufacturers
//                          gives their specifications in Mebabytes that are
//                          1000000 bytes in size to let their products look
//                          4.8576% more impressive.
//
//
//ATA drives support the following addressing modes:
//
//    CHS28: 127.5 GB ( 16 heads * 255 sectors * 65536 cyls)
//    LBA28: 128.0 GB (2^28 blocks)
//    LBA48: 128.0 PB (2^48 blocks)
//
//    INT13: 504.0 MB ( 16 heads *  63 sectors *  1024 cyls)
//    LARGE:   7.9 GB (256 heads *  63 sectors *  1024 cyls)   
//
//
//ATA drives support the following PIO modes:
//
//    Mode 0: 600 ns =   3.3 MB/s (ATA-1)
//    Mode 1: 383 ns =   5.2 MB/s (ATA-1)
//    Mode 2: 240 ns =   8.3 MB/s (ATA-1)
//    Mode 3: 180 ns =  11.1 MB/s (ATA-2)
//    Mode 4: 120 ns =  16.6 MB/s (ATA-2)
//    Mode 5:  90 ns =  22.2 MB/s (propietary)
//
//
//ATA drives support the following Single-Word DMA modes (obsolete from ATA-3):
//
//    Mode 0: 960 ns =   2.1 MB/s (ATA-1)
//    Mode 1: 480 ns =   4.2 MB/s (ATA-1)
//    Mode 2: 240 ns =   8.4 MB/s (ATA-1)
//
//
//ATA drives support the following Multi-Word DMA modes:
//
//    Mode 0: 480 ns =   4.2 MB/s (ATA-1)
//    Mode 1: 150 ns =  12.2 MB/s (ATA-2)
//    Mode 2: 120 ns =  16.6 MB/s (ATA-2)
//
//
//ATA drives support the following Ultra DMA modes:
//
//    Mode 0: 240 ns =  16.6 MB/s (ATA-4)
//    Mode 1: 160 ns =  25.0 MB/s (ATA-4)
//    Mode 2: 120 ns =  33.3 MB/s (ATA-4) (Ultra ATA)
//    Mode 3:  90 ns =  44.4 MB/s (ATA-5)
//    Mode 4:  60 ns =  66.6 MB/s (ATA-5)
//    Mode 5:  40 ns = 100.0 MB/s (ATA-6)
//    Mode 6:  30 ns = 133.3 MB/s (ATA-7)
//
//
//ATA controllers use the following resources by default:
//
//    #  I/O RANGE 1  I/O 2  IRQ    DMA
//    1  01F0h-01F7h  03F6h  14     (3)
//    2  0170h-0177h  0376h  15/10  (5)
//    3  01E8h-01EFh  03EEh  12/11
//    4  0168h-016Fh  036Eh  10/9
//
//    DMA Channels wwere only used on the XT. It was to slow for ATs and
//    Ultra DMA uses a dedicated DMA chip integrated in the southbridge.
//
//The following IDE chipsets contain bugs and will corrupt your data!
//
//    CMD640x
//    PC-Tech RZ-1000 (http://www.intel.com/procs/support/rz1000/index.htm)

//00  ************  NOP
//03  CF  CFA REQUEST EXTENDED ERROR CODE
//08  **  DEVICE RESET

// 1x  **  RECALIBRATE

//20  **  READ SECTOR(S)
//*21  **  READ SECTOR(S) WITHOUT RETRY
//*22  **  READ LONG SECTOR(S)
//*23  **  READ LONG SECTOR(S) WITHOUT RETRY
//24  **  READ SECTOR(S) EXT
//25  **  READ DMA EXT
//26  **  READ DMA QUEUED EXT
//27  HP  READ NATIVE MAX ADDRESS EXT
//29  **  READ MULTIPLE EXT
//2A  ST  READ STREAM DMA
//2B  ST  READ STREAM PIO
//2F  LO  READ LOG EXT
//30  **  WRITE SECTOR(S)
//*31  **  WRITE SECTOR(S) WITHOUT RETRY
//*32  **  WRITE LONG SECTOR(S)
//*33  **  WRITE LONG SECTOR(S) WITHOUT RETRY
//34  **  WRITE SECTOR(S) EXT
//35  **  WRITE DMA EXT
//36  **  WRITE DMA QUEUED EXT
//37  HP  SET MAX ADDRESS EXT
//38  CF  CFA WRITE SECTORS WITHOUT ERASE
//39  **  WRITE MULTIPLE EXT
//3A  ST  WRITE STREAM DMA
//3B  ST  WRITE STREAM PIO
//*3C  **  WRITE VERIFY SECTOR(S)
//3D  **  WRITE DMA FUA EXT
//3E  **  WRITE DMA QUEUED FUA EXT
//3F  **  WRITE LOG EXT
//40  **  READ VERIFY SECTOR(S)
//*41  **  READ VERIFY SECTOR(S) WITHOUT RETRY
//42  **  READ VERIFY SECTOR(S) EXT
//*50  XX  FORMAT TRACK
//51  ST  CONFIGURE STREAM
//*7x  **  SEEK
//*8x  **  [VENDOR SPECIFIC 3]
//87  CF  CFA TRANSLATE SECTOR
//90  **  EXECUTE DEVICE DIAGNOSTIC
//*91  **  INITIALIZE DRIVE PARAMETERS
//92  **  DOWNLOAD MICROCODE
//*94  PM  STANDBY IMMEDIATE
//*95  PM  IDLE IMMEDIATE
//*96  PM  STANDBY
//*97  PM  IDLE
//*98  PM  CHECK POWER MODE
//*99  PM  SLEEP
//*9A ** [VENDOR SPECIFIC 1]
//A0  PA  PACKET
//A1  PA  IDENTIFY PACKET DEVICE
//A2  PA  SERVICE
//B0  SM  SMART
//B1  DC  DEVICE CONFIGURATION
//C0  CF  CFA ERASE SECTORS
//*C1  **  [VENDOR SPECIFIC 2]
//*C2  **  [VENDOR SPECIFIC 2]
//*C3  **  [VENDOR SPECIFIC 2]
//C4  **  READ MULTIPLE
//C5  **  WRITE MULTIPLE
//C6  **  SET MULTIPLE MODE
//C7  **  READ DMA QUEUED
//C8  **  READ DMA
//*C9 **  READ DMA WITHOUT RETRY
//CA  **  WRITE DMA
//*CB **  WRITE DMA
//CC  **  WRITE DMA QUEUED
//CD  CF  CFA WRITE MULTIPLE WITHOUT ERASE
//CE  **  WRITE MULTIPLE FUA EXT
//D1  MC  CHECK MEDIA CARD TYPE
//DA  RM  GET MEDIA STATUS
//*DB **  ACKNOWLEDGE MEDIA CHANGE
//*DC **  POST BOOT
//*DD **  PRE BOOT
//DE  RM  MEDIA LOCK
//DF  RM  MEDIA UNLOCK
//E0  PM  STANDBY IMMEDIATE
//E1  PM  IDLE IMMEDIATE
//E2  PM  STANDBY
//E3  PM  IDLE
//E4  **  READ BUFFER
//E5  PM  CHECK POWER MODE
//E6  PM  SLEEP
//E7  **  FLUSH CACHE
//*E7 **  REST
//E8  **  WRITE BUFFER
//*E9 **  WRITE SAME
//EA  **  FLUSH CACHE EXT
//*EA **  RESTORE DRIVE STATE
//*EA **  ATA-3 SECURITY
//*EB **  ATA-3 SECURITY
//EC  **  IDENTIFY DEVICE
//ED  RM  MEDIA EJECT
//*EE **  IDENTIFY DEVICE DMA
//EF  **  SET FEATURES
//*F0 **  [ENHANCED ATA]
//F1  SE  SECURITY SET PASSWORD
//F2  SE  SECURITY UNLOCK
//F3  SE  SECURITY ERASE PREPARE
//F4  SE  SECURITY ERASE UNIT
//F5  SE  SECURITY FREEZE LOCK
//F6  SE  SECURITY DISABLE PASSWORD
//F8  HP  READ NATIVE MAX ADDRESS
//F9  HP  SET MAX
//*FA **  [VENDOR SPECIFIC 4]

//CF: CompactFlash Devices
//ST: Streaming Devices
//PA: Packet Devices
//DC: Device Configuration
//MC: Media Card Devices
//RM: Removable Devices
//PM: Power Management
//LO: General Purpose Logging
//HP: Host Protected Area
//SE: Security
//SM: S.M.A.R.T.


#include <io.h>
#include "ata.h"

typedef unsigned short io_port_t;

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

void ata_inputPio(ata_controller_t controller, unsigned char* buffer, unsigned n)
{	_asm cld;
	_asm mov ecx, n;
	_asm mov edi, buffer;
	_asm mov  dx, controller.portData;
	_asm rep insw;
}

void ata_readSector(ata_disk_t disk, unsigned int block, unsigned char count)
{	ata_command_t	command;

	command.block		= block;
	command.count		= count;
	command.disk		= disk;
	command.features	= 0x00;
	command.command		= 0x20;

	ata_command(command);
}
