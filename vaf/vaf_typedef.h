#ifndef __vaf_typedef_h__
#define __vaf_typedef_h__ 

typedef short wchar;
typedef unsigned short uwchar;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;

//////////////////////////////////////////////////////////////////////////
// Win32 Style Type
//////////////////////////////////////////////////////////////////////////
typedef uchar* PUCHAR;
typedef char* PCHAR;
typedef void* PVOID;
typedef wchar* PWCHAR;

typedef unsigned short WCHAR;
typedef unsigned short WORD;
typedef unsigned short USHORT;
typedef unsigned char UCHAR;
typedef unsigned long ULONG;
typedef unsigned int UINT;
typedef ULONG DWORD;
typedef int INT;
typedef long LONG;
typedef short SHORT; 

typedef char BOOL;

#define TRUE 1
#define FALSE 0

//////////////////////////////////////////////////////////////////////////
// CSharp Style Type
//////////////////////////////////////////////////////////////////////////
#ifndef INT32
#define INT32 int
#endif

#ifndef INT16
#define INT16 short
#endif

#ifndef INT8
#define INT8 CHAR
#endif

#ifndef UINT32
#define UINT32 UINT
#endif

#ifndef UINT16
#define UINT16 USHORT
#endif

#ifndef UINT8
#define UINT8 UCHAR
#endif

#endif
