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
//   *CHS/LBA Translation : This is a complex topic, so I've written a dedicated
//                          section for it.
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
//    CHS28: 128 GB
//    LBA28: 128 GB
//    LBA48: 128 PB
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
//    #  I/O RANGE 1  I/O RANGE 2  IRQ    DMA
//    1  01F0h-01F7h  03F6h-03F7h  14     
//    2  0170h-0177h  0376h-0377h  15/10  (5)
//    3  01E8h-01EFh  03EEh-03EFh  12/11
//    4  0168h-016Fh  036Eh-036Fh  10/9
//
//
//The following IDE chipsets contain bugs and will corrupt your data!
//
//    CMD640x
//    PC-Tech RZ-1000 (http://www.intel.com/procs/support/rz1000/index.htm)

//00h  **********  NOP
//01h  


#include <io.h>

enum ata_command
{
	identify	= 0xEC
};

struct ata_command_t
{
	unsigned char opcode;
};

struct ata_controller_t
{
	unsigned ioCommand;
};

struct ata_device_t
{
};

struct ata_identification_t
{
};

void ata_command(ata_command_t command)
{
//	ioWriteByte(command.opcode);
}

void ata_killInterrupt(ata_controller_t controller)
{
	ioReadByte(controller.ioCommand);
}

void ata_identify(ata_device_t device, ata_identification_t buffer)
{
	ata_command_t command;

	command.opcode = 0xEC;

	ata_command(command);
}