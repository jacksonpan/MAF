#ifndef __vaf_font_h__
#define __vaf_font_h__

#define ALIGN_TEXT_LEFT			0x0001
#define ALIGN_TEXT_TOP			0x0002
#define ALIGN_TEXT_V_CENTER		0x0004			//垂直方向y
#define ALIGN_TEXT_H_CENTER		0x0008			//水平方向x
#define ALIGN_TEXT_RIGHT		0x0010			
#define ALIGN_TEXT_BOTTOM		0x0020
#define ALIGN_TEXT_CALC			0x0040
#define ALIGN_TEXT_WORDBREAK	0x0080


extern void vaf_font_init(void);

#endif
