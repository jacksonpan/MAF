/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   23:42
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVFileHelper.h
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVFileHelper
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVFileHelper_h__
#define __CVFileHelper_h__
#include "../vaf/vaf_include.h"

#define FileHelper	CVFileHelper

class CVFileHelper
{
public:
	CVFileHelper();
	~CVFileHelper();
	/**
	* Open the file.
	*
	* @mode		read(MODE_READ),write(MODE_WRITE),add to the end of the file(MODE_APPEND),
	*			whatever this file is being there,just create it(MODE_CREATE_ALWAYS_WRITE).
	* @binary	open the file by binary when it's true,open the file by ASCII when it's false.
	*
	* @return	return a nonnegative number when open the file success,
	*			return a negative number when open the file failed.
	*/
	int FileOpen(uint mode, bool binary);
	/**
	* Close the file.
	*/
	void FileClose(void);
	/**
	* Read from the file.
	*
	* @data		memory address pointer where read to.
	* @length	length you need to read.
	*
	* @return	return how much word you have read,
	*			return 0 when there is some error occurred or you have reach the end of the file.
	*/
	int FileRead(void * data, uint length);
	/**
	* Write to file
	*
	* @data		memory address pointer where you want write to the file	
	* @length	length you need to write.
	*
	* @return	return how much word you have write,
	*			return 0 when there is some error occurred.
	*/
	int FileWrite(void * data, uint length);
	/**
	* Refresh content in I/O buffer to the file immediately,data which wrote submit to file compulsory.
	*
	* @return	return 0 when success,
	*			else failed.
	*/
	int FileCommit(void);
	/**
	* Move the file literacy pointer to specified position.
	*
	* @offset	mobile offset, bytes for the unit.
	* @base		start from head of the file(BASE_BEGIN),
	*			start from the current position(BASE_CURR),
	*			start from the end of the file(BASE_END).
	*
	* @return	return 0 when success,
	*			return negative number when failed.
	*/
	int FileSeek(int offset, int base);
	/**
	* Get current position of file literacy pointer.
	*
	* @return	return current position of the pointer,
	*			return negative number when failed.
	*/
	int FileTell(void);
	/**
	* Determine that current position of file literacy pointer have reach the end of the file.
	*
	* @return	TRUE=Yes,FALSE=No.
	*/
	int FileIsEof(void);
	/**
	* Get file size,bytes for the unit.
	*
	* @return	return 0 when success,
	*			else failed.
	*/
	int GetFileSize(void);
	/**
	* Delete the file.
	*
	* @return	return 0 when success,
	*			else failed.
	*/
	int FileDelete(void);
	/**
	* Rename the file.
	*
	* @new_path	new file path.
	*
	* @return	return 0 when success,
	*			else failed.
	*/
	int FileRename(char * new_path);
	/**
	* Create directory.
	*
	* @dir_path	path of directory.
	*
	* @return	return 0 when success,
	*			else failed.
	*/
	int FileMKdir(char * dir_path);
	/**
	* Delete directory.
	*
	* @dir_path	path of directory.
	*
	* @return	return 0 when success,
	*			else failed.
	*/
	int FileRMdir(char * dir_path);
	/**
	* Set file attributes(Which not include VM_FS_ATTR_VOLUME£¬VM_FS_ATTR_DIR£¬VM_FS_LONGNAME_ATTR).
	*
	* @attributes file attributes.
	*
	* @return	return 0 when success,
	*			return negative number when failed.
	*/
	int SetFileAttributes(uchar attributes);
	/**
	* Get file attributes.
	*
	* @return	return file attributes when success,
	*			return negative number when failed.
	*/
	int GetFileAttributes(void);
	/**
	* Get file path.
	*
	* return file path.
	*/
	short * GetFilePath(void);
	/**
	* Set file path.
	*
	* @path file path you want to set.
	*
	* @return	1 when success,
	*			0 when failed.
	*/
	int SetFilePath(char * path);
	/**
	* Converted to UCS2 encoding.
	*
	* @path file path you want to converted.
	*
	* @return	true when success,
	*			false when failed.
	*/
	bool SetTemppath(char * path);
private:
	int file_handle;
	short * file_path;
	short * temp_path;
	uint file_size;
	bool is_binary_open;
};

#endif // __CVFileHelper_h__