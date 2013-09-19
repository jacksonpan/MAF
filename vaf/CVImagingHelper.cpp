/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   23:38
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVImagingHelper.cpp
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVImagingHelper
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVImagingHelper.h"

CVImagingHelper::CVImagingHelper(void)
{
	img_width = 0;
	img_height = 0;
	
	hcanvas = 0;
	data = NULL;

	property = NULL;
}

CVImagingHelper::~CVImagingHelper(void)
{
	Free();
}
void CVImagingHelper::LoadFromMemory(uchar* ptr,int size)
{
	vaf_debug("Load Picture from memory[%02X]:[%d]",ptr,size);
	if ((hcanvas = vaf_load_image(ptr, size)) < 0)
	{
		vaf_debug("load image failed!");
		return;
	}

	//ptr = NULL;
	
	/* 获取画布地址 */ 
	vaf_debug("vaf_get_canvas_buffer Start");
	data = vaf_get_canvas_buffer(hcanvas);
	vaf_debug("LoadFromMemory End");
	vaf_debug("GetProperty Start");
	GetProperty(&img_width, &img_height); 
	vaf_debug("GetProperty End");
	vaf_debug("LoadFromMemory End");
}
int CVImagingHelper::GetCanvas()
{
	return hcanvas;
}
uchar* CVImagingHelper::Load(char* name)
{
	uchar *ptr;
	int size;

	/* 加载图片资源 */
	if ((ptr = vaf_load_resource(name, &size)) == NULL)
	{
		vaf_debug("load resource failed!");
		return 0;
	}
	/* 通过加载图片创建画布 */
	if ((hcanvas = vaf_load_image(ptr, size)) < 0)
	{
		vaf_debug("load image failed!");
		return 0;
	}

	vaf_free(ptr);
	ptr = NULL;
	
	/* 获取画布地址 */
	data = vaf_get_canvas_buffer(hcanvas);
	GetProperty(&img_width, &img_height);

	return data;
}

uchar* CVImagingHelper::LoadImage(char* name)
{
	int canvas;
	uchar* pImg;
	uchar *ptr;
	int size;

	/* 加载图片资源 */
	if ((ptr = vaf_load_resource(name, &size)) == NULL)
	{
		vaf_debug("load resource failed!");
		return 0;
	}
	/* 通过加载图片创建画布 */
	if ((canvas = vaf_load_image(ptr, size)) < 0)
	{
		vaf_debug("load image failed!");
		return 0;
	}

	vaf_free(ptr);
	ptr = NULL;
	
	/* 获取画布地址 */
	pImg = vaf_get_canvas_buffer(canvas);
	
	return pImg;
}


uchar* CVImagingHelper::GetAddr(void)
{
	return data;
}

img_property* CVImagingHelper::GetProperty(void)
{
	/* 获取画布属性*/
	property = vaf_get_img_property(hcanvas, 1);
	return property;
}

void CVImagingHelper::GetProperty(int *width, int *height)
{
	if(property == NULL)
	{
		property = vaf_get_img_property(hcanvas, 1);
	}

	*width = property->width;
	*height = property->height;
}

void CVImagingHelper::Free(void)
{
	if(data)
	{
		vaf_free(data);
		data = NULL;
	}
	img_width = 0;
	img_height = 0;
	hcanvas = 0;
	property = NULL;
}

void CVImagingHelper::Draw(uchar* buf, int x, int y, int width, int height, int index)
{
	if(data)
	{
		//vm_graphic_set_clip(x, y, x + width, y + height);
		vaf_blt(buf, x, y, data, 0, 0, width, height, index);
	}
}

void CVImagingHelper::Draw(uchar* buf, int x, int y, int x_src, int y_src, int width, int height, int index)
{
	if(data)
	{
		//vm_graphic_set_clip(x, y, x + width, y + height);
		vaf_blt(buf, x, y, data, x_src, y_src, width, height, index);
	}
}

int CVImagingHelper::GetWidth(void)
{
	return img_width;
}

int CVImagingHelper::GetHeight(void)
{
	return img_height;
}

BOOL CVImagingHelper::LoadResizeImage( uchar *img_data, int img_len, int new_width, int new_height )
{
	int ret = vaf_load_image_resized(img_data, img_len, new_width, new_height);
	if(ret > VM_GDI_SUCCEED)
	{
		hcanvas = ret;
		GetProperty();
		GetProperty(&img_width, &img_height);
		data = vaf_get_canvas_buffer(hcanvas);
		return TRUE;
	}
	return FALSE;
}