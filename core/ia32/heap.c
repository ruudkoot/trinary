#include <heap.h>

static unsigned a;

/* public ********************************************************************/


void* _cdecl operator new(unsigned cb)
{
    return heapAlloc(cb);
}

void _cdecl operator delete(void* p)
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