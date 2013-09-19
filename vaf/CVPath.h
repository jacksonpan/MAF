/********************************************************************
	created:	2011/03/15
	created:	15:3:2011   21:17
	filename: 	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common\CVPath.h
	file path:	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common
	file base:	CVPath
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVPath_h__
#define __CVPath_h__
#include "CVString.h"

class CVPath
{
public:
	CVPath();
	~CVPath();

	CVString getCurrentPath(void);
	CVString getCurrentVREPath(void);
	CVString getCurrentVRESavePath(void);

	/*
	*	return 0 is successful, return other is failer, return -255 is getCurrentPath error
	*/
	int createPath(char* wholePath);
	int removePath(char* wholePath);
private:
protected:

};

#endif
