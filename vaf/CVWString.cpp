#include "CVWString.h"

CVWString::CVWString( void )
{
	v_pData = NULL;
	v_nSize = 0;
}

CVWString::CVWString( CVWString &str )
{
	v_pData = NULL;
	v_nSize = 0;

	set(str);
}

CVWString::CVWString( wchar *pStr )
{
	v_pData = NULL;
	v_nSize = 0;

	set(pStr);
}

CVWString::CVWString( int str_length )
{
	v_pData = NULL;
	v_nSize = 0;

	SetBufferSize(str_length);
}

CVWString::~CVWString( void )
{
	Reset();
}

wchar* CVWString::C_Str() const
{
	return v_pData;
}

int CVWString::Length() const
{
	return v_nSize - 1;
}

bool CVWString::IsEmpty() const
{
	if(v_pData == NULL || vaf_wcslen(v_pData) == 0 || v_nSize == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CVWString CVWString::SubStr( int nPosStart, int nCount )
{
	CVWString t;
	wchar* p = &v_pData[nPosStart];
	int len = nCount + 1;
	wchar* ss = (wchar*)alloc(len * SIZEOFWCHAR);
	memcpy(ss, p, nCount);
	t.set(ss);
	vaf_free(ss);
	return t;
}

uint CVWString::GetBufferSize() const
{
	return v_nSize * SIZEOFWCHAR;
}

void CVWString::SetBufferSize( int str_length )
{
	Reset();
	v_nSize = str_length + 1;
	v_pData = (wchar*)alloc(v_nSize * SIZEOFWCHAR);
	ZeroBuffer();	
}

void CVWString::ZeroBuffer()
{
	memset(v_pData, 0, v_nSize * SIZEOFWCHAR);
}

CVWString& CVWString::operator=( CVWString &str )
{
	set(str);
	return *this;
}

CVWString& CVWString::operator=( wchar *pStr )
{
	set(pStr);
	return *this;
}

CVWString CVWString::operator+( CVWString &str )
{
	CVWString xstring;
	xstring.set(v_pData);
	xstring.append(str);
	return xstring;
}

CVWString CVWString::operator+( wchar *pStr )
{
	CVWString xstring;
	xstring.set(v_pData);
	xstring.append(pStr);
	return xstring;
}

int CVWString::Compare( wchar* pStr ) const
{
	return vaf_wcscmp(C_Str(), pStr);
}

int CVWString::Compare( CVWString& str ) const
{
	return vaf_wcscmp(C_Str(), str.C_Str());
}

bool CVWString::operator==( wchar* pStr ) const
{
	if(Compare(pStr) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CVWString::operator==( CVWString& str ) const
{
	if(Compare(str) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CVWString::Find( wchar* pStr, int beginPos/*=0*/ ) const
{
	wchar* ret = vaf_wcsstr(&v_pData[beginPos], pStr);
	if(ret == NULL)
	{
		return -1;
	}

	int pos = ret - &v_pData[beginPos];
	return pos;
}

int CVWString::Find( CVWString& str, int beginPos/*=0*/ ) const
{
	wchar* ret = vaf_wcsstr(&v_pData[beginPos], str.C_Str());
	if(ret == NULL)
	{
		return -1;
	}
	
	int pos = ret - &v_pData[beginPos];
	return pos;
}

int CVWString::Find( wchar ch, int beginPos/*=0*/ ) const
{
	wchar cch[2];
	cch[0] = ch;
	cch[1] = 0;
	wchar* ret = vaf_wcsstr(&v_pData[beginPos], cch);
	if(ret == NULL)
	{
		return -1;
	}
	
	int pos = ret - &v_pData[beginPos];
	return pos;
}

wchar& CVWString::operator[]( const int index )
{
	return v_pData[index];
}

CVWString::operator wchar*() const
{
	return C_Str();
}

CVWString& CVWString::operator+=( CVWString &str )
{
	CVWString t;
	t.set(v_pData);
	t.append(str.C_Str());
	set(t);
	return *this;
}

CVWString& CVWString::operator+=( wchar *pStr )
{
	CVWString t;
	t.set(v_pData);
	t.append(pStr);
	set(t);
	return *this;
}

void* CVWString::alloc( int nSize )
{
	return vaf_calloc(nSize);
}

void CVWString::Reset( void )
{
	if(v_pData)
	{
		vaf_free(v_pData);
		v_pData = NULL;
		v_nSize = 0;
	}
}

void CVWString::append( wchar* pStr )
{
	if(pStr)
	{
		int new_len = vaf_wcslen(pStr) + v_nSize;
		wchar* pnew = (wchar*)alloc(new_len * SIZEOFWCHAR);
		if(v_pData)
		{
			vaf_wcscat(pnew, v_pData);
		}
		vaf_wcscat(pnew, pStr);
		Reset();
		v_nSize = new_len;
		v_pData = pnew;
	}

}

void CVWString::append( CVWString* pStr )
{
	if(pStr && pStr->Length() != 0)
	{
		int new_len = vaf_wcslen(pStr->C_Str()) + v_nSize;
		wchar* pnew = (wchar*)alloc(new_len * SIZEOFWCHAR);
		vaf_wcscat(pnew, v_pData);
		vaf_wcscat(pnew, pStr->C_Str());
		Reset();
		v_nSize = new_len;
		v_pData = pnew;
	}
}

void CVWString::set( wchar* pStr )
{
	if(pStr)
	{
		Reset();
		v_nSize = vaf_wcslen(pStr) + 1;
		v_pData = (wchar*)alloc(v_nSize * SIZEOFWCHAR);
		vaf_wcscpy(v_pData, pStr);
	}
}

void CVWString::set( CVWString* pStr )
{
	if(pStr && pStr->Length() != 0)
	{
		Reset();
		v_nSize = vaf_wcslen(pStr->C_Str()) + 1;
		v_pData = (wchar*)alloc(v_nSize * SIZEOFWCHAR);
		vaf_wcscpy(v_pData, pStr->C_Str());
	}
}