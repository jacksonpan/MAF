#include "vaf_usefulapi.h" 
#include "vaf_include.h"

wchar* default_to_ucs2(char* text)
{
	char* pSrc;
	int sizeSrc;
	int malloc_len;
	wchar* pDst;
	
	if(text == NULL)
	{
		return 0;
	}

	if(strlen(text) == 0)
	{
		return 0;
	}
	
	pSrc = text;
	sizeSrc = strlen(pSrc);
	malloc_len = (sizeSrc+1)*sizeof(wchar);
	pDst = (wchar*)vaf_calloc(malloc_len);
	
	if(pDst == NULL)
	{
		vaf_debug("default_to_ucs2: vm_calloc fail!");
		return NULL;
	}
		
	if(vaf_default_to_ucs2(pDst, malloc_len, pSrc) != 0)
	{
		vaf_debug("default_to_ucs2: vaf_default_to_ucs2 fail!");
		return NULL;
	}

	return pDst;
}

void free_str(void * ptr)
{
	if(ptr)
	{
		vaf_free(ptr);
		ptr = NULL;
	}
}

void strcut(char* front, char* behind, char* src, char* des)
{
	char* pStr1 = NULL;
	char* pStr2 = NULL;
	int Size;
	pStr1 = strstr(src, front) + strlen(front);
	if(pStr1)
	{
		pStr2 = strstr(pStr1, behind);
		Size  = pStr2 - pStr1;
		if(Size > 0)
		{
			memcpy(des, pStr1, Size);
		}
	}
}

