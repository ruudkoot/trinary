#include <bootlog.h>
#include <debug.h>
#include <heap.h>
#include <mm.h>
#include <cpu.h>

//This is the entry point of the Trinary Operating System Kernel. Be assume to
//be located at physical and logical memory location 0x00000000. We should be
//in 32-bit Protected Mode. In the current version paging is disabled. Our
//segments (CS, SS, DS, ES, FS and GS) should have a base address of 0 and a
//limit of 4GB. The code has to be read-only, while the other segments have to
//be read-write.
void main(void)
{
	unsigned char* a;
	a = (unsigned char*)0xB8E6A;
	*a = 0xFB;
	a++;
	*a = 0x0A;

	heapInit(2*1024*1024, 0);

	cpuInit();

	//Shutdown the CPU
	_asm
	{
		cli;
		hlt;
	}
}