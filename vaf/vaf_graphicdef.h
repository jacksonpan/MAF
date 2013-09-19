#ifndef __vaf_graphicdef_h__
#define __vaf_graphicdef_h__

#define V_RGB(r, g, b) ((((r & 0xf8) + ((g & 0xe0) >> 5)) << 8) + ((g & 0x1c) << 3) + (b >> 3))
#define RGB(r,g,b) V_RGB(r,g,b)

#define V_COLOR_BLACK	V_RGB(0, 0, 0)
#define V_COLOR_WHITE	V_RGB(255, 255, 255)
#define V_COLOR_FOCUS	V_RGB(255, 204, 0)

#define V_COLOR_TRANS	(V_RGB(255, 255, 255) - 2)

#define IN_RECT_WAY1(xf,yf,x,y,width,height)	(xf > x && xf < x + width && yf >y && yf < y + height)
#define IN_RECT_WAY2(xf,yf,x1,y1,x2,y2)			(xf > x1 && xf < x2 && yf > y1 && yf < y2)

#define GET_IS_IN_THE_RECT(x,y,x1,y1,x2,y2)		(x > x1 && x < x2 && y > y1 && y < y2)
#define GET_IS_OUT_THE_RECT(x,y,x1,y1,x2,y2)	(x < x1 || x > x2 || y < y1 || y > y2)

typedef struct _RECT
{
	int left;
	int top;
	int right;
	int bottom;
}RECT;

typedef struct _POSITION
{
	int x;
	int y;
	int width;
	int height;
}POSITION;

#define QCIF_WIDTH		176
#define QCIF_HEIGHT		220

#define QCIF_LS_WIDTH	220
#define QCIF_LS_HEIGHT	176

#define QVGA_WIDTH		240
#define QVGA_HEIGHT		320

#define QVGA_LS_WIDTH	320
#define QVGA_LS_HEIGHT	240

#define WQVGA_WIDTH		240
#define WQVGA_HEIGHT	400

#define HVGA_WIDTH		320
#define HVGA_HEIGHT		480

#endif