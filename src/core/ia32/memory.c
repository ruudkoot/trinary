void discardable mm_arch_init(void);
void discardable mmPhysicalInit(void);
void discardable mmVirtualInit(void);

unsigned* buffer;
unsigned* bufferIterator;
const unsigned PAGESIZE = 4096;

char ts[4096*3];
char td[4096*3];

void discardable mm_arch_init(void)
{

   logItem("Initializing Memory Management");

    
    mmPhysicalInit();
    mmVirtualInit();

    logStatus(logSuccess);

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
//the processor's cache. And it makes implementing 36-bit physical addressing
//much easier. We use a persistant circular searching algorithm to find pages
//very fast and some other optimizations (such as checking 32 pages at once).
//
//We could also use MMX or SSE2 to check 64 or 128 pages (bits) at a time.
//
//The current algorithm can allocate 4GB on a 1GHz PC in less than 100 us.
//The algorithm takes about 75 clocks on a P6.
void discardable mmPhysicalInit(void)
{
	unsigned i;
    unsigned size = 16 * 1024 * 1024;

	size /= PAGESIZE;
	size++;
	size /= 32;

	buffer = (unsigned*)(0x40000);
    bufferIterator = (unsigned*)(0x40000);

	for (i = 0; i < 40; i++) buffer[i]      = 0xFFFFFFFF;
	for (i = 40; i < size; i++) buffer[i]   = 0x00000000;
}

unsigned mmPhysicalAlloc(void)
{
	unsigned mask = 0x00000001;
	unsigned bit = 0;

  	//Search for an entry that contains a free page
	while (*bufferIterator == 0xFFFFFFFF) bufferIterator++;
	
	//Search for a bit that indicates a free page
	while (*bufferIterator & mask)
	{
		mask <<= 1;
		bit++;
	}

	*bufferIterator |= mask;

    return 32 * (bufferIterator - buffer) + bit;
}

void mmPhysicalFree(unsigned page)
{
	buffer[page >> 5] &= ~(1 << (page & 0x1F));		//Confused?!?
}

/*******************************************************************/

void discardable mmVirtualInit(void)
{

}

/*******************************************************************/

void mmPageCopyByte(unt32 destination, unt32 source)
{
	asm volatile
    (   "cld;"
		"rep; movsb;"
		: 
		: "c" (1024*1024), "D" (destination), "S" (source)
		: "memory"
    );
}

void mmPageCopyWord(unt32 destination, unt32 source)
{
	asm volatile
    (   "cld;"
		"rep; movsw;"
		: 
		: "c" (512*1024), "D" (destination), "S" (source)
		: "memory"
    );
}

void mmPageCopyDword(unt32 destination, unt32 source)
{
	asm volatile
    (   "cld;"
		"rep; movsl;"
		: 
		: "c" (256*1024), "D" (destination), "S" (source)
		: "memory"
    );
}
