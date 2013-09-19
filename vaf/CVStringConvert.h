#ifndef __CStringConvert_h__
#define __CStringConvert_h__

#include "CVString.h"
#include "CVWString.h"

#define CStringConvert	CVStringConvert

class CVStringConvert
{
public:
	static CVWString DefaultToUCS2(CVString& pStr);	
	static CVString UCS2ToDefault(CVWString& pStr);
	static CVWString GB2312ToUCS2(CVString& pStr);
	static CVString UCS2ToGB2312(CVWString& pStr);
	static CVWString ASCIIToUCS2(CVString& pStr);
	static CVString UCS2ToASCII(CVWString& pStr);
	static CVWString UTF8toUCS2(CVString& pStr);
	static CVString UCS2TOUTF8(CVWString& pStr);
};

//only for run with old application which use this api, please don't use it
extern wchar* UTF8toUCS2(char* str);
#endif