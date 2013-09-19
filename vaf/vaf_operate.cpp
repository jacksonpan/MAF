#include "vaf_include.h"

#ifdef WIN32

void *operator new(size_t size)
{
	return vm_malloc(size);
};

void operator delete(void *p)
{
	vm_free(p);
};

#endif
