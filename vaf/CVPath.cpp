/********************************************************************
	created:	2011/03/15
	created:	15:3:2011   21:17
	filename: 	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common\CVPath.cpp
	file path:	D:\Developer\SVN\trunk\mtk\vre\Tuangou\vaf\common
	file base:	CVPath
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVPath.h"
#include "CVStringConvert.h"

CVPath::CVPath()
{
	
}

CVPath::~CVPath()
{

}

CVString CVPath::getCurrentPath( void )
{
	CVString cvPath;
	int drv = -1;
	drv = vaf_get_removable_driver();	//优先获取移动盘符
	if(drv < 0) 						//不存在移动盘
	{
		drv = vaf_get_system_driver();	//获取系统盘
	}
	cvPath.SetBufferSize(128);
	sprintf(cvPath.C_Str(), "%c:\\", drv);
	return cvPath;
}

CVString CVPath::getCurrentVREPath( void )
{
	CVString cvPath = getCurrentPath();
	cvPath += "vre\\";
	return cvPath;
}

CVString CVPath::getCurrentVRESavePath( void )
{
	CVString cvPath = getCurrentVREPath();
	cvPath += "Save\\";
	return cvPath;
}

int CVPath::createPath( char* wholePath )
{
	CVString tPath = wholePath;
	return vaf_file_mkdir(CStringConvert::DefaultToUCS2(tPath).C_Str());
}

int CVPath::removePath( char* wholePath )
{
	CVString tPath = wholePath;
	return vaf_file_rmdir(CStringConvert::DefaultToUCS2(tPath).C_Str());
}


