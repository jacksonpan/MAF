/********************************************************************
	created:	2011/03/15
	created:	15:3:2011   21:16
	filename: 	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common\CVFile.cpp
	file path:	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common
	file base:	CVFile
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVFile.h"
#include "../vaf/vaf_include.h"
#include "CVStringConvert.h"

CVFile::CVFile(void)
{
	file = NULL;
	file_path = new CVString();
	open_type = FILE_READ;
}

CVFile::CVFile( char* path, uint type)
{
	file = NULL;
	file_path = new CVString();
	*file_path = path;
	open_type = type;
}

CVFile::~CVFile(void)
{
	if(file_path)
	{
		delete file_path;
		file_path = NULL;
	}
	if(file)
	{
		Close();
	}
}

void CVFile::SetPath( char* str )
{
	*file_path = str;
}

void CVFile::SetType( uint type )
{
	open_type = type;
}

bool CVFile::Open( void )
{
	CVWString path = CStringConvert::DefaultToUCS2(*file_path);
	file = vaf_file_open((short*)(path.C_Str()), open_type, FALSE);
	
	if(!file)
	{
		return false;
	}
	return true;	
}

bool CVFile::Close( void )
{
	vaf_file_close(file);
	file = NULL;
	return true;
}

int CVFile::GetFileSize( void )
{	
	if(Open() == false)
	{
		return -1;
	}
	uint length;
	if(vaf_file_getfilesize(file, &length) < 0)
	{
		return -1;
	}
	Close();
	int ret = length;
	return ret;
}

char* CVFile::Read( void )
{
	Close();
	int length = GetFileSize();
	
	if(length <= 0)
	{
		return NULL;
	}
	if(Open() == false)
	{
		return NULL;
	}
	
	uint length1;
	char* buffer = new char[length + 1];
	memset(buffer, 0, length + 1);
	vaf_file_read(file, buffer, length, &length1);
	return buffer;
}

bool CVFile::Write(char* data)
{
	if(data == NULL)
	{
		return false;
	}
	
	int len = strlen(data);
	
	if(len == 0)
	{
		return false;
	}
	
	uint length;
	vaf_file_write(file, data, len, &length);
	return true;
}

bool CVFile::CheckFileExist(void)//true:说明文件存在, false:说明文件不存在, 这个函数以r类型读取
{
	CVWString path = CStringConvert::DefaultToUCS2(*file_path);
	file = vaf_file_open((short*)(path.C_Str()), FILE_READ, FALSE);
	if(file < 0)
	{
		return false;
	}
	
	vaf_file_close(file);
	file = NULL;
	return true;
};

char* CVFile::ReadFast( void )
{
	if(Open() == false)
	{
		return NULL;
	}

	char* ret = Read();
	Close();
	return ret;
}

bool CVFile::WriteFast( char* data )
{
	if(Open() == false)
	{
		return false;
	}

	bool ret = Write(data);
	Close();
	return ret;
}

bool CVFile::Create( void )
{
	CVWString path = CStringConvert::DefaultToUCS2(*file_path);
	file = vaf_file_open((short*)(path.C_Str()), MODE_CREATE_ALWAYS_WRITE, FALSE);
	
	if(!file)
	{
		return false;
	}
	Close();
	return true;
}
