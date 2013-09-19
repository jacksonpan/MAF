#include "CVStringConvert.h"

CVWString CVStringConvert::DefaultToUCS2( CVString& pStr )
{
	CVWString dst(pStr.Length());
	if(vaf_default_to_ucs2(dst.C_Str(), dst.GetBufferSize(), pStr.C_Str()) != 0)
	{
		vaf_debug("DefaultToUCS2: fail!");
		return dst;
	}
	return dst;
}

CVString CVStringConvert::UCS2ToDefault( CVWString& pStr )
{
	CVString dst(pStr.Length()*SIZEOFWCHAR);
	if(vaf_ucs2_to_default(dst.C_Str(), dst.GetBufferSize(), pStr.C_Str()) != 0)
	{
		vaf_debug("UCS2ToDefault: fail!");
		return dst;
	}
	return dst;
}

CVWString CVStringConvert::GB2312ToUCS2( CVString& pStr )
{
	CVWString dst(pStr.Length());
	if(vaf_gb2312_to_ucs2(dst.C_Str(), dst.GetBufferSize(), pStr.C_Str()) != 0)
	{
		vaf_debug("GB2312ToUCS2: fail!");
		return dst;
	}
	return dst;
}

CVString CVStringConvert::UCS2ToGB2312( CVWString& pStr )
{
	CVString dst(pStr.Length()*SIZEOFWCHAR);
	if(vaf_ucs2_to_gb2312(dst.C_Str(), dst.GetBufferSize(), pStr.C_Str()) != 0)
	{
		vaf_debug("UCS2ToGB2312: fail!");
		return dst;
	}
	return dst;
}

CVWString CVStringConvert::ASCIIToUCS2( CVString& pStr )
{
	CVWString dst(pStr.Length());
	if(vaf_ascii_to_ucs2(dst.C_Str(), dst.GetBufferSize(), pStr.C_Str()) != 0)
	{	
		vaf_debug("ASCIIToUCS2: fail!");
		return dst;
	}
	return dst;
}

CVString CVStringConvert::UCS2ToASCII( CVWString& pStr )
{
	CVString dst(pStr.Length()*SIZEOFWCHAR);
	if(vaf_ucs2_to_ascii(dst.C_Str(), dst.GetBufferSize(), pStr.C_Str()) != 0)
	{
		vaf_debug("UCS2ToASCII: fail!");
		return dst;
	}
	return dst;
}

CVWString CVStringConvert::UTF8toUCS2(CVString& pStr)
{
	CVWString dst(pStr.Length()*2);
	if(vaf_utf8_to_ucs2((uchar*)pStr.C_Str(), (ushort*)dst.C_Str()) == 0)
	{	
		vaf_debug("UTF8TOUCS2: fail!");
		return dst;
	}
	return dst;
}

CVString CVStringConvert::UCS2TOUTF8( CVWString& pStr )
{
	CVString dst(pStr.Length()*SIZEOFWCHAR*2);
	if(vaf_ucs2_to_utf8((ushort*)pStr.C_Str(), (uchar*)dst.C_Str()) == 0)
	{
		vaf_debug("UCS2ToUTF8: fail!");
		return dst;
	}
	return dst;
}

wchar* UTF8toUCS2(char* str)
{
	CVString t1 = str;
	CVWString t2 = CVStringConvert::UTF8toUCS2(t1);
	wchar* t3 = (wchar*)vaf_calloc(SIZEOFWCHAR*(t1.Length()+1));
	vaf_wcscpy(t3, t2.C_Str());
	return t3;
}
