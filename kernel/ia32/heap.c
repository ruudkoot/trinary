#include <heap.h>

static unsigned a;

/* public ********************************************************************/


void* operator new(unsigned cb)
{
    return heapAlloc(cb);
}

void operator delete(void* p)
{
    heapFree(p);
}

bool heapInit(unsigned address, unsigned size)
{
	size = size;
	a = address;
	return true;
}

//bool heapSize(unsigned size)
//{
//}

void* heapAlloc(unsigned size)
{
	a += size;
	return (void*)(a - size);
}

void heapFree(void*)
{
	return;
}

/* private *******************************************************************/