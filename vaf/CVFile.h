/********************************************************************
	created:	2011/03/15
	created:	15:3:2011   21:08
	filename: 	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common\CVFile.h
	file path:	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common
	file base:	CVFile
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVFile_h__
#define __CVFile_h__

#include "CVString.h"

#define FILE_READ		MODE_READ
#define FILE_WRITE		MODE_WRITE
#define FILE_APPEND		MODE_APPEND

class CVFile
{
public:
	CVFile(void);
	CVFile(char* path, uint type);
	~CVFile(void);

	void SetPath(char* str);
	void SetType(uint type);
	bool CheckFileExist(void);//true:说明文件存在, false:说明文件不存在, 这个函数以r类型读取

	bool Create(void);
	bool Open(void);
	bool Close(void);
	int GetFileSize(void);
	char* Read(void);//delete to release
	bool Write(char* data);

	//no need to open and close
	char* ReadFast(void);//delete to release
	bool WriteFast(char* data);
protected:
	int file;
	CVString* file_path;
	uint open_type;
};


#endif