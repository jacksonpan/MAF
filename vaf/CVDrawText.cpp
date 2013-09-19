/********************************************************************
	created:	2011/03/22
	created:	22:3:2011   11:43
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVDrawText.cpp
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVDrawText
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVDrawText.h"

CVDrawText::CVDrawText()
{
	
}

CVDrawText::~CVDrawText()
{
	
}

int CVDrawText::draw( uchar* buf, POSITION* pos, wchar* text, int len, ushort textColor, int vspace, int maxRow /*= 0*/, int AlignMode )
{
	int totalHeight = 0;
	int fontHeight = vaf_get_character_height() + vspace;
	int stringWidth = vaf_get_string_width(text);
	BOOL isCalc = FALSE;
	BOOL isWordbreak = FALSE;

	if((AlignMode & ALIGN_TEXT_CALC) == ALIGN_TEXT_CALC)
	{
		isCalc = TRUE;
		AlignMode ^= ALIGN_TEXT_CALC;
	}
	if((AlignMode & ALIGN_TEXT_WORDBREAK) == ALIGN_TEXT_WORDBREAK)
	{
		isWordbreak = TRUE;
		AlignMode ^= ALIGN_TEXT_WORDBREAK;
	}

	if(stringWidth <= pos->width/* && maxRow == 1*/)
	{
		switch(AlignMode)
		{
		case ALIGN_TEXT_TOP:
		case ALIGN_TEXT_LEFT:
		case ALIGN_TEXT_TOP | ALIGN_TEXT_LEFT:
			{
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, pos->x, pos->y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_RIGHT:
		case ALIGN_TEXT_TOP | ALIGN_TEXT_RIGHT:
			{
				int x = pos->x + (pos->width - stringWidth);
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, x, pos->y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_BOTTOM:
		case ALIGN_TEXT_BOTTOM | ALIGN_TEXT_LEFT:
			{
				int y = pos->y + (pos->height - fontHeight);
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, pos->x, y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_BOTTOM | ALIGN_TEXT_RIGHT:
			{
				int x = pos->x + (pos->width - stringWidth);
				int y = pos->y + (pos->height - fontHeight);
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, x, y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_V_CENTER:
		case ALIGN_TEXT_V_CENTER | ALIGN_TEXT_LEFT:
			{
				int y = pos->y + (pos->height - fontHeight)/2;
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, pos->x, y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_V_CENTER | ALIGN_TEXT_RIGHT:
			{
				int x = pos->x + (pos->width - stringWidth);
				int y = pos->y + (pos->height - fontHeight)/2;
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, x, y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_H_CENTER:
		case ALIGN_TEXT_H_CENTER | ALIGN_TEXT_TOP:
			{
				int x = pos->x + (pos->width - stringWidth)/2;
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, x, pos->y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_H_CENTER | ALIGN_TEXT_BOTTOM:
			{
				int x = pos->x + (pos->width - stringWidth)/2;
				int y = pos->y + (pos->height - fontHeight);
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, x, y , text, len, textColor);
				}
			}
			break;
		case ALIGN_TEXT_V_CENTER | ALIGN_TEXT_H_CENTER:
			{
				int x = pos->x + (pos->width - stringWidth)/2;
				int y = pos->y + (pos->height - fontHeight)/2;
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, x, y , text, len, textColor);
				}
			}
			break;
		default:
			return RET_DRAWTEXT_FAILER;
			break;
		}
		if(isCalc)
		{
			return totalHeight;
		}
		return RET_DRAWTEXT_SUCCESS;
	}
	else if(stringWidth > pos->width && maxRow == 1)
	{
_TEXT_OUT_1:
		wchar *temp = new wchar[len+1];
		memset(temp, 0, (len+1)*SIZEOFWCHAR);
		int i;
		for(i=0;i<len;i++)
		{
			temp[i] = text[i];
			int strWidth = vaf_get_string_width(temp);
			if(strWidth > pos->width)
			{
				text[i+1] = 0;
				text[i] = '.';
				text[i-1] = '.';
				text[i-2] = '.';
				break;
			}
		}

		switch(AlignMode)
		{
		case ALIGN_TEXT_TOP:
		case ALIGN_TEXT_LEFT:
		case ALIGN_TEXT_TOP | ALIGN_TEXT_LEFT:
			{
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, pos->x, pos->y , text, i+1, textColor);
				}
			}
			break;
		case ALIGN_TEXT_V_CENTER:
		case ALIGN_TEXT_LEFT | ALIGN_TEXT_V_CENTER:
			{
				int y = pos->y + (pos->height - fontHeight)/2;
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, pos->x, y , text, i+1, textColor);
				}
			}
			break;
		case ALIGN_TEXT_BOTTOM:
		case ALIGN_TEXT_BOTTOM | ALIGN_TEXT_LEFT:
			{
				int y = pos->y + (pos->height - fontHeight);
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, pos->x, y , text, i+1, textColor);
				}
			}
			break;
		default:
			return RET_DRAWTEXT_FAILER;
			break;
		}
		delete temp;
		temp = NULL;
		if(isCalc)
		{
			return totalHeight;
		}
		return RET_DRAWTEXT_SUCCESS;
	}
	else if(stringWidth > pos->width)
	{
		if(maxRow == 1 || isWordbreak == FALSE)
		{
			goto _TEXT_OUT_1;
		}

		BOOL is_limit_row = FALSE;
		int save_row = 0;
		if(maxRow > 1)
		{	
			is_limit_row = TRUE;
		}

		wchar *temp = new wchar[len+1];
		memset(temp, 0, (len+1)*SIZEOFWCHAR);
		int k = 0;
		int x = pos->x;
		int y = pos->y;
		int strWidth = 0;
		for(int i=0;i<len;i++)
		{
			temp[k] = text[i];
			strWidth = vaf_get_string_width(temp);
			if(temp[k] == '\n')
			{
				goto _TEXT_OUT_2;
			}
			if(strWidth >= pos->width)
			{
_TEXT_OUT_2:
				temp[k] = 0;
				save_row++;
				if(pos->height != 0)
				{
					if((y + fontHeight) > (pos->y + pos->height - fontHeight))
					{
						goto _TEXT_OUT_4;
					}
				}
				if(save_row == maxRow)
				{
_TEXT_OUT_4:
					if(strWidth > pos->width)
					{
						temp[k+1] = 0;
						temp[k] = '.';
						temp[k - 1] = '.';
						temp[k - 2] = '.';
					}
					goto _TEXT_OUT_3;
				}
				if(isCalc)
				{
					totalHeight += fontHeight;
				}
				else
				{
					vaf_textout(buf, x, y , temp, k+1, textColor);
				}
				k = 1;
				memset(temp, 0, (len+1)*SIZEOFWCHAR);
				temp[0] = text[i];
				y += fontHeight;
			}
			else
			{
				k++;
			}
		}

_TEXT_OUT_3:
		if(isCalc)
		{
			totalHeight += fontHeight;
		}
		else
		{
			vaf_textout(buf, x, y , temp, k+1, textColor);
		}

		delete temp;
		temp = NULL;
		if(isCalc)
		{
			return totalHeight;
		}
		return RET_DRAWTEXT_SUCCESS;
	}
	return RET_DRAWTEXT_FAILER;
}

//for hewei
int wrap( uchar * buf, wchar *s, WRAPSET* wrapset )
{
	wchar *pStr = s;
	int iStrLen = wstrlen(pStr);
	int i, j;
	int count = 1;
	wchar pbuf[255] = {0};
	int str_width = vaf_get_string_width(pStr);
	int font_height = vaf_get_character_height();
	
	
	
	for(i=0,j=0;i<iStrLen;i++,j++)
	{
		int nTempWidth = 0;
		
		pbuf[j] = pStr[i];
		nTempWidth = vaf_get_string_width(pbuf);
		
		if(pStr[i] == '\n')
		{
			count++;
			wchar temp = pbuf[j];
			pbuf[j] = 0;
			if(count >= wrapset->max_row)
			{
				pbuf[j-2] = '.';
				pbuf[j-1] = '.';
				pbuf[j] = '.';
				if(wrapset->calc_height == false)
				{
					vaf_textout(buf, wrapset->xPos,   wrapset->yPos+ wrapset->font_between ,pbuf, wstrlen(pbuf),  wrapset->txtcolor);
				}
				return (font_height*count)+(count* wrapset->font_between) +  wrapset->font_between;
			}
			else
			{
				if(wrapset->calc_height == false)
				{
					vaf_textout(buf, wrapset->xPos,  wrapset->yPos+wrapset->font_between ,pbuf, wstrlen(pbuf), wrapset->txtcolor);
				}
				wrapset->yPos = wrapset->yPos + font_height + wrapset->font_between;
				j = 0;
				memset(pbuf, 0, 255*sizeof(wchar));
				pbuf[0] = temp;
			}
		}
		
		if(nTempWidth >= wrapset->tolerable_width)
		{
			wchar temp = pbuf[j];
			if(count == wrapset->max_row)
			{
				pbuf[j-2] = '.';
				pbuf[j-1] = '.';
				pbuf[j] = '.';
				if(wrapset->calc_height == false)
				{
					vaf_textout(buf, wrapset->xPos,   wrapset->yPos+ wrapset->font_between ,pbuf, wstrlen(pbuf),  wrapset->txtcolor);
				}
				return (font_height*count)+(count* wrapset->font_between) +  wrapset->font_between;
			}
			else
			{
				pbuf[j] = 0;
				if( wrapset->calc_height == false)
				{
					vaf_textout(buf,  wrapset->xPos,   wrapset->yPos+ wrapset->font_between ,pbuf, wstrlen(pbuf),  wrapset->txtcolor);
				}
				wrapset->yPos =  wrapset->yPos + font_height +  wrapset->font_between;
				j = 0;
				memset(pbuf, 0, 255*sizeof(wchar));
				pbuf[0] = temp;
				count++;
			}
			
		}
		
	}
	
	// 	if( wrapset->tolerable_width >= str_width)
	// 	{
	// 		if( wrapset->calc_height == false)
	// 		{
	// 			vaf_textout(buf,  wrapset->xPos,   wrapset->yPos+ wrapset->font_between ,pStr, wstrlen(pStr),  wrapset->txtcolor);
	// 		}
	// 		return (font_height*count)+(count* wrapset->font_between) + 5;
	// 	}
	
	if(vaf_wcslen(pbuf))
	{
		if( wrapset->calc_height == false)
		{
			vaf_textout(buf,  wrapset->xPos,   wrapset->yPos+ wrapset->font_between ,pbuf, wstrlen(pbuf),  wrapset->txtcolor);
			wrapset->yPos =  wrapset->yPos + font_height +  wrapset->font_between;
		}
	}
	int sum_height = (font_height*count)+(count* wrapset->font_between) +  wrapset->font_between;
	return sum_height;
}