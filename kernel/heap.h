void* operator new(unsigned cb);
void operator delete(void* p);

bool heapInit(unsigned address, unsigned size);
bool heapSize(unsigned size);
void* heapAlloc(unsigned size);
void heapFree(void*);
