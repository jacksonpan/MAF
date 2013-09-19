#include "CVString.h"

CVString::CVString( void )
{
	v_pData = NULL;
	v_nSize = 0;
}

CVString::CVString( const CVString &str )
{
	v_pData = NULL;
	v_nSize = 0;

	set(str);
}

CVString::CVString( const char *pStr )
{
	v_pData = NULL;
	v_nSize = 0;

	set(pStr);
}

CVString::CVString( int str_length )
{
	v_pData = NULL;
	v_nSize = 0;

	SetBufferSize(str_length);
}

CVString::~CVString( void )
{
	Reset();
}

char* CVString::C_Str() const
{
	return v_pData;
}

int CVString::Length() const
{
	return v_nSize - 1;
}

bool CVString::IsEmpty() const
{
	if(v_pData == NULL || strlen(v_pData) == 0 || v_nSize == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CVString CVString::SubStr( int nPosStart, int nCount )
{
	CVString t;
	char* p = &v_pData[nPosStart];
	int len = nCount + 1;
	char* ss = (char*)alloc(len * SIZEOFCHAR);
	memcpy(ss, p, nCount);
	t.set(ss);
	vaf_free(ss);
	return t;
}

uint CVString::GetBufferSize() const
{
	return v_nSize * SIZEOFCHAR;
}

void CVString::SetBufferSize( int str_length )
{
	Reset();
	v_nSize = str_length + 1;
	v_pData = (char*)alloc(v_nSize * SIZEOFCHAR);
	ZeroBuffer();	
}

void CVString::ZeroBuffer()
{
	memset(v_pData, 0, v_nSize * SIZEOFCHAR);
}

CVString& CVString::operator=( const CVString &str )
{
	set(str);
	return *this;
}

CVString& CVString::operator=( const char *pStr )
{
	set(pStr);
	return *this;
}

CVString CVString::operator+( const CVString &str )
{
	CVString xstring;
	xstring.set(v_pData);
	xstring.append(str);
	return xstring;
}

CVString CVString::operator+( const char *pStr )
{
	CVString xstring;
	xstring.set(v_pData);
	xstring.append(pStr);
	return xstring;
}

int CVString::Compare( const char* pStr ) const
{
	return strcmp(C_Str(), pStr);
}

int CVString::Compare( const CVString& str ) const
{
	return strcmp(C_Str(), str.C_Str());
}

bool CVString::operator==( const char* pStr ) const
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

bool CVString::operator==( const CVString& str ) const
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

int CVString::Find( const char* pStr, int beginPos/*=0*/ ) const
{
	char* ret = strstr(&v_pData[beginPos], pStr);
	if(ret == NULL)
	{
		return -1;
	}

	int pos = ret - &v_pData[beginPos];
	return pos;
}

int CVString::Find( const CVString& str, int beginPos/*=0*/ ) const
{
	char* ret = strstr(&v_pData[beginPos], str.C_Str());
	if(ret == NULL)
	{
		return -1;
	}
	
	int pos = ret - &v_pData[beginPos];
	return pos;
}

int CVString::Find( char ch, int beginPos/*=0*/ ) const
{
	char cch[2];
	cch[0] = ch;
	cch[1] = 0;
	char* ret = strstr(&v_pData[beginPos], cch);
	if(ret == NULL)
	{
		return -1;
	}
	
	int pos = ret - &v_pData[beginPos];
	return pos;
}

// void CVString::MakeUpper()
// {
// 
// }
// 
// void CVString::MakeLower()
// {
// 	
// }

char& CVString::operator[]( const int index )
{
	return v_pData[index];
}

CVString::operator char*() const
{
	return C_Str();
}

CVString& CVString::operator+=( const CVString &str )
{
	CVString t;
	t.set(v_pData);
	t.append(str.C_Str());
	set(t);
	return *this;
}

CVString& CVString::operator+=( const char *pStr )
{
	CVString t;
	t.set(v_pData);
	t.append(pStr);
	set(t);
	return *this;
}

void* CVString::alloc( int nSize )
{
	return vaf_calloc(nSize);
}

void CVString::Reset( void )
{
	if(v_pData)
	{
		vaf_free(v_pData);
		v_pData = NULL;
		v_nSize = 0;
	}
}

void CVString::append( const char* pStr )
{
	if(pStr)
	{
		int new_len = strlen(pStr) + v_nSize;
		char* pnew = (char*)alloc(new_len * SIZEOFCHAR);
		strcat(pnew, v_pData);
		strcat(pnew, pStr);
		Reset();
		v_nSize = new_len;
		v_pData = pnew;
	}

}

void CVString::append( const CVString* pStr )
{
	if(pStr && pStr->Length() != 0)
	{
		int new_len = strlen(pStr->C_Str()) + v_nSize;
		char* pnew = (char*)alloc(new_len * SIZEOFCHAR);
		strcat(pnew, v_pData);
		strcat(pnew, pStr->C_Str());
		Reset();
		v_nSize = new_len;
		v_pData = pnew;
	}
}

void CVString::set( const char* pStr )
{
	if(pStr)
	{
		Reset();
		v_nSize = strlen(pStr) + 1;
		v_pData = (char*)alloc(v_nSize * SIZEOFCHAR);
		strcpy(v_pData, pStr);
	}
}

void CVString::set( const CVString* pStr )
{
	if(pStr && pStr->Length() != 0)
	{
		Reset();
		v_nSize = strlen(pStr->C_Str()) + 1;
		v_pData = (char*)alloc(v_nSize * SIZEOFCHAR);
		strcpy(v_pData, pStr->C_Str());
	}
}