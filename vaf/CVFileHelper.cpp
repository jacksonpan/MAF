/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   23:43
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVCVFileHelper.cpp
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVCVFileHelper
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVFileHelper.h"

CVFileHelper::CVFileHelper()
{
	file_handle = -1;
	file_path = NULL;
	temp_path = NULL;
	file_size = 0;
	is_binary_open = false;
}

CVFileHelper::~CVFileHelper()
{
	if(file_handle >= 0)
	{
		FileClose();
	}
	if(file_path)
	{
		free_str(file_path);
		file_path = NULL;
	}
	if(temp_path)
	{
		delete temp_path;
		temp_path = NULL;
	}
}
bool CVFileHelper::SetTemppath(char * path)
{
	if(path == NULL) 
	{
		return false;
	}
	if(temp_path)
	{
		delete temp_path;
	}
	int str_size = strlen(path);
	temp_path = new short[str_size + 1];
	memset(temp_path, 0, str_size + 1);
	if(temp_path == NULL)
	{
		return false;
	}
	if(vaf_default_to_ucs2(temp_path, 255, path) != 0)
	{
		return false;
	}
	return true;
}

int CVFileHelper::FileOpen(uint mode, bool binary)
{
	if(file_path)
	{
		is_binary_open = binary;
		return file_handle = vaf_file_open(file_path, mode, binary);		
	}
	return -1;
}

void CVFileHelper::FileClose(void)
{
	vaf_file_close(file_handle);
	file_handle = -1;
}

int CVFileHelper::FileRead(void * data, uint length)
{
	uint read_size = 0;
	if(data)
	{
		uint tmp;
		while(vaf_file_read(file_handle, (void*)&((char*)data)[read_size], length, &tmp) != 0)
		{
			length -= tmp;
			read_size += tmp;
		}
		
		if(!is_binary_open)
			((char*)data)[read_size] = '\0';
		return read_size;
	}
	return 0;
}

int CVFileHelper::FileWrite(void * data, uint length)
{
	uint written_size = 0;
	if(data)
	{
		return written_size = vaf_file_write(file_handle, data, length, &written_size);
	}
	return 0;
}

int CVFileHelper::FileCommit(void)
{
	return vaf_file_commit(file_handle);
}

int CVFileHelper::FileSeek(int offset, int base)
{
	return vaf_file_seek(file_handle, offset, base);
}

int CVFileHelper::FileTell(void)
{
	return vaf_file_tell(file_handle);
}

int CVFileHelper::FileIsEof(void)
{
	return vaf_file_is_eof(file_handle);
}

int CVFileHelper::GetFileSize(void)
{
	if(vaf_file_getfilesize(file_handle, &file_size) == 0)
	{
		return file_size;
	}
	return -1;
}

int CVFileHelper::FileDelete(void)
{
	if(file_path)
	{
		return vaf_file_delete(file_path);
	}
	return -1;
}

int CVFileHelper::FileRename(char * new_path)
{
	if(!SetTemppath(new_path)) return -1;
	if(file_path && temp_path)
	{
		return vaf_file_rename(file_path, temp_path);
	}
	return -1;
}

int CVFileHelper::FileMKdir(char *  dir_path)
{
	if(!SetTemppath(dir_path)) return -1;
	if(temp_path)
	{
		return vaf_file_mkdir(temp_path);
	}
	return -1;
}

int CVFileHelper::FileRMdir(char *  dir_path)
{
	if(!SetTemppath(dir_path)) return -1;
	if(temp_path)
	{
		return vaf_file_rmdir(temp_path);
	}
	return -1;
}

int CVFileHelper::SetFileAttributes(uchar attributes)
{
	if(file_path)
	{
		return vaf_file_set_attributes(file_path, attributes);
	}
	return -1;
}

int CVFileHelper::GetFileAttributes(void)
{
	if(file_path)
	{
		return vaf_file_get_attributes(file_path);
	}
	return -1;
}

short * CVFileHelper::GetFilePath(void)
{
	return file_path;
}

int CVFileHelper::SetFilePath(char * path)
{
	file_path = default_to_ucs2(path);
	if(!file_path) return 0;
	return 1;
}
