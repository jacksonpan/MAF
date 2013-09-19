/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   23:37
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVImagingHelper.h
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVImagingHelper
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVImagingHelper_h__
#define __CVImagingHelper_h__
#include "../vaf/vaf_include.h"

#define ImageHelper		CVImagingHelper
class CVImagingHelper
{
public:
	CVImagingHelper(void);
	~CVImagingHelper(void);
	
	uchar* Load(char* name);
	//////////////////////////////////////////////////////////////////////////
	//Add by Shubo Yang
	void LoadFromMemory(uchar* ptr,int size);
	int GetCanvas();
	//////////////////////////////////////////////////////////////////////////
	static uchar* LoadImage(char* name);
	uchar* GetAddr(void);
	img_property* GetProperty(void);
	void GetProperty(int *width, int *height);
	
	BOOL LoadResizeImage(uchar *img_data, int img_len, int new_width, int new_height);
	
	void Free(void);
	
	void Draw(uchar* buf, int x, int y, int width, int height, int index = 1);
	void Draw(uchar* buf, int x, int y, int x_src, int y_src, int width, int height, int index = 1);
	int GetWidth(void);
	int GetHeight(void);
private:
	int img_width, img_height;
	int hcanvas;
	uchar* data;
	img_property *property;
};

#endif // __CVImagingHelper_h__