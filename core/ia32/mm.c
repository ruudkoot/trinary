#include <mm.h>
#include <bootlog.h>

void mmPhysicalInit(unsigned size);

/******************************************************************************/
/*                                SPINLOCKS!                                  */
/******************************************************************************/

static unsigned* buffer;

//  00000000h - 3FFFFFFFh: Application
//  40000000h - 7FFFFFFFh:
//  80000000h - BFFFFFFFh:
//  C0000000h - FFFFFFFFh: Kernel
//    C0000000h - CFFFFFFFh: Kernel Code
//    D0000000h - DFFFFFFFh: Kernel Data
//    E0000000h - EFFFFFFFh: Memory Manager
//    F0000000h - FFFFFFFFh: Kernel Stack

//mmInit() is called (very early) by the kernel, before any of the other
//memory manager functions are called.
bool mmInit(void)
{
	logStatus(success);
	logNote("The following parameters were set at compile time!");
	logSubItem("Total Physical Memory", "16384 kB");
	logSubItem("Kernel Size", "1024 kB");
	mmPhysicalInit(16*1024*1024);
	return true;
}

//mmPhysicalInit() initializes the buffer used to keep track of free physical
//pages. This is the first memory management function that should be called,
//and it should only be called once. It sets all pages to allocated/reserved
//(reserved in this case). Free physical memory should then be registered by
//mmPhysicalRegister(). It's very important to note that 1 bit means that the
//page is allocated or reserved and that 0 bit means free. This makes the
//search algorithm look nicer and possibly faster. Also remeber that bit 0 of
//an entry is page 0 (or 32, or 64, ...) and that bit 31 is page 31 (or 63,
//or 95, ...) and not the other way around.
//
//The keep track of physical memory, we could have used a stack or a bit array.
//At first sight a stack might seem much faster. We just have to increment or
//decrement a pointer to allocate or deallocate a page. A stack makes it
//impossible to allocate a specific page in memory. This is necessary for
//a page coloring algorithm that will be implemented in the future. It also
//memory allocation for DMA buffers more easy. Another advantage is the fact
//that a bit array is 32 times smaller (64 times if we start using 64-bit
//addresses) than a stack making them faster accessable and fit more easy in
//the processor's cache. We use a persistant circular searching algorithm to
//find pages very fast and some other optimizations (such as checking 32 pages
//at once).
//
//We could also use MMX or SSE2 to check 64 or 128 bits/pages at a time.
void mmPhysicalInit(unsigned size)
{
	unsigned i;
	
	size /= PAGESIZE;
	size++;
	size /= 32;

	buffer = (unsigned*)(0x40000);

	for (i = 0; i < 32; i++) buffer[i]		= 0xFFFFFFFF;
	for (i = 32; i < size; i++) buffer[i]	= 0x00000000;
}

unsigned mmPhysicalAllocatePage(void)
{
	unsigned* bufferIterator = buffer;

	unsigned mask = 0x00000001;
	unsigned bit = 0;

	//Search for an entry that contains a free page
	while (*bufferIterator != 0xFFFFFFFF) bufferIterator++;
	
	//Search for a bit that indicates a free page
	while (*bufferIterator & mask)
	{
		mask <<= 1;
		bit++;
	}

	*bufferIterator |= mask;

	return 32 * (bufferIterator - buffer) + bit;
}

void mmPhysicalDeallocatePage(unsigned page)
{
	buffer[page >> 5] &= ~(1 << (page & 0x1F));		//Confused?!?
}

void mmVirtualCreatePageDirectory(void)
{
//	unsigned address = page << 12;
//	_asm mov cr3, address;
}

void mmVirutalCreatePageTable(void)
{
}

//Before we enable paging we must do some things
//
//  Create a Page Directory
//  Create a Page Table
//  Select the Page Table in the Page Directory
//  Map the Page Directory and the Page Table into the Page Table itself
//
//The last two steps are very important, because else we wouldn't be able to
//modify the Page Directory and that Page Table, because they would only exist
//in physical memory which we can't access yet (we need to modify the
//Page Directory and Page Table for that).
//
//After enabling paging we must also ensure that
//
//  Kernel Memory is mapped correctly
void mmVirtualInit(void)
{
	unsigned pageDirectory, pageTable;
	
	//Create a Page Directory
	pageDirectory = mmPhysicalAllocatePage() << 12;
//	memzero(pageDirectory, PAGESIZE);
	
	//Create a Page Table
	pageTable = mmPhysicalAllocatePage() << 12;
//	memzero(pageTable, PAGESIZE);

	//Select the Page Table in the Page Directory
	((unsigned*)pageDirectory)[0xE0] = (pageTable & 0xFFFFF000) + 0x25;

	//Map the Page Directory and the Page Table into the Page Table itself
	((unsigned*)pageTable)[0x00] = (pageDirectory & 0xFFFFF000) + 0x67;
	((unsigned*)pageTable)[0x01] = (pageTable & 0xFFFFF000) + 0x67;

	//Enable Paging
	__asm mov eax, pageDirectory;
	__asm mov cr3, eax;
	__asm mov eax, cr0;
	__asm or eax, 0x80000000;
	__asm mov cr0, eax;


}