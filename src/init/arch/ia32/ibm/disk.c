/******************************************************************************/
/* System Initialization : Disk Support                                       */
/* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       */
/*                                                                            */
/* This program is free software; you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation; either version 2 of the License, or          */
/* (at your option) any later version.                                        */
/******************************************************************************/

typedef struct
{
    unsigned biosid;
    unsigned sectors;
    unsigned heads;
    unsigned int13x;
} disk_t;

typedef struct
{
    unsigned char size;
    unsigned char reserved;
    unsigned short blocks;
    unsigned buffer;
    unsigned block;
    unsigned blockhigh;
    unsigned bufferlow;
    unsigned bufferhigh;
} int32xpacket_t;

char* disk_errorcodes[256];

void disk_init(void)
{
    disk_errorcodes[0x00] = "Successful Completion";
    disk_errorcodes[0x01] = "Invalid Function or Parameter";
    disk_errorcodes[0x02] = "Address Mark Not Found";
    disk_errorcodes[0x03] = "Disk Write-Protected";
    disk_errorcodes[0x04] = "Sector Not Found / Read Error";
    disk_errorcodes[0x05] = "Reset Failed";
    disk_errorcodes[0x06] = "Disk Changed";
    disk_errorcodes[0x07] = "Drive Parameter Activity Failed";
    disk_errorcodes[0x08] = "DMA Overrun";
    disk_errorcodes[0x09] = "Data Boundary Error";
    disk_errorcodes[0x0A] = "Bad Sector Detected";
    disk_errorcodes[0x0B] = "Bad Track Detected";
    disk_errorcodes[0x0C] = "Unsupported Track or Invalid Media";
    disk_errorcodes[0x0D] = "Invalid Number of Sectors on Format";
    disk_errorcodes[0x0E] = "Control Data Address Mark Detected";
    disk_errorcodes[0x0F] = "DMA Arbitration Level Out of Range";
    disk_errorcodes[0x10] = "Uncorrectable CRC or ECC Error Detected";
    disk_errorcodes[0x11] = "Data ECC Corrected";
    disk_errorcodes[0x20] = "Controller Failure";
    disk_errorcodes[0x31] = "No Media In Drive";
    disk_errorcodes[0x32] = "Invalid Drive Type Stored in CMOS";
    disk_errorcodes[0x40] = "Seek Failed";
    disk_errorcodes[0x80] = "Timeout";
    disk_errorcodes[0xAA] = "Drive Not Ready";
    disk_errorcodes[0xB0] = "Volume Not Locked in Drive";
    disk_errorcodes[0xB1] = "Volume Locked in Drive";
    disk_errorcodes[0xB2] = "Volume Not Removable";
    disk_errorcodes[0xB3] = "Volume In Use";
    disk_errorcodes[0xB4] = "Lock Count Exceded";
    disk_errorcodes[0xB5] = "Valid Eject Request Failed";
    disk_errorcodes[0xB6] = "Volume Present but Read Protected";
    disk_errorcodes[0xBB] = "Undefined Error";
    disk_errorcodes[0xCC] = "Write Fault";
    disk_errorcodes[0xE0] = "Status Register Error";
    disk_errorcodes[0xFF] = "Sense Operation Failed";
}

/******************************************************************************/
/* disk_readblock - Read Block from Disk                                      */
/*                                                                            */
/* This function read one block (sector) from the disk using the BIOS. If     */
/* availabe, it will use the Interrupt 13h Extensions. Additionally it        */
/* contains workarounds for all know BIOS bugs.                               */
/******************************************************************************/
int disk_readblock(disk_t* disk, unsigned block, void* buffer)
{

    unsigned cylinder, head, sector, temp;

    /* convert the sector number to a CHS address. We use the formula         *
     *     C = B / (Nh * Ns)                                                  *
     *     t = B % (Nh * Ns)                                                  *
     *     H = t / Ns                                                         *
     *     S = (t % Ns) + 1                                                   */

    cylinder    = block / (disk->sectors * disk->heads);
    temp        = block % (disk->sectors * disk->heads);
    head        = temp / disk->sectors;
    sector      = (temp % disk->sectors) + 1;

    asm
    (
        "stc;"
        "int $0x13;"
        "sti;"
        :
        :
        "a" (0x0201),
        "b" (buffer),
        "c" (0),
        "d" (0)
    );
}
