void* _cdecl operator new(unsigned cb);
void _cdecl operator delete(void* p);

bool heapInit(unsigned address, unsigned size);
bool heapSize(unsigned size);
void* heapAlloc(unsigned size);
void heapFree(void*);
