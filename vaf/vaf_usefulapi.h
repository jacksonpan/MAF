#ifndef __vaf_usefulapi_h__
#define __vaf_usefulapi_h__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "vaf_typedef.h"
//#include "vaf_packageapi.h"

#ifdef  __cplusplus
extern "C" {
#endif

//	extern void *memset(void *dest, int c, size_t count);
//	extern void *memcpy(void *dest, void* src, size_t count);
//	extern size_t strlen(const char *str);
//	extern char *strcat(char *, const char *);
//	extern char *strstr(const char *str, const char *strSearch);
//	extern int sprintf(char *buffer, const char *format,  ... );
//	extern char* strcpy(char *, const char *);
//	extern char* strncpy(char*, const char*, size_t);
//	extern int strcmp(const char *, const char *);
//	extern int atoi(const char *);
//	extern uint strftime(char *strDest, uint maxsize, const char *format, const struct tm *timeptr);
 

	extern wchar* default_to_ucs2(char* text);
	extern void free_str(void * ptr);

	extern void strcut(char* front, char* behind, char* src, char* des);

#ifdef  __cplusplus
}
#endif 



#endif
