/********************************************************************
	created:	2011/03/22
	created:	22:3:2011   11:43
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVDrawText.h
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVDrawText
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVDrawText_h__
#define __CVDrawText_h__

#include "../vaf/vaf_include.h"


#define	RET_DRAWTEXT_SUCCESS				 0
#define	RET_DRAWTEXT_FAILER					-1

class CVDrawText
{
public:
	CVDrawText();
	~CVDrawText();

	//if there is ALIGN_TEXT_CALC, then it will return the height, or return RET_DRAWTEXT_SUCCESS or return RET_DRAWTEXT_FAILER
	//maxRow:1 is singline;>1 is multiline with maxrow limit;=0 is multiline without maxrow limit
	static int draw(uchar* buf, POSITION* pos, wchar* text, int len, ushort textColor, int vspace = 1, int maxRow = 0, int AlignMode = ALIGN_TEXT_LEFT);
protected:
private:
};

//for hewei
typedef struct  
{
	int xPos;  
	int yPos;
	int tolerable_width;  //����ʾ����
	int max_row;          //�������   0ΪĬ��
	BOOL calc_height;	  //�Ƿ�ֻ���㻻�к�ĸ߶Ȳ��������
	ushort txtcolor;	  //��ɫ
	int font_between;     //�м��
}WRAPSET;

int wrap(uchar * buf, wchar *s, WRAPSET* wrapset);

#endif // __CVDrawText_h__