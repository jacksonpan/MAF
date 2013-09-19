#include "vaf_include.h"

#ifndef WIN32
void* malloc(size_t n)
{
	return vm_malloc(n);
}

void free(void *ptr)
{
	vm_free(ptr);
}
#endif