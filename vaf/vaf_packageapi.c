#include "vaf_packageapi.h"

static int font_size=0;

void vaf_exit_app(void)
{
//#ifndef WIN32
	vm_exit_app();
//#endif
}

int vaf_create_timer(ulong millisec, void (*callback)(int tid))
{
	return vm_create_timer(millisec, callback);
}

int vaf_delete_timer(int timerid)
{
	return vm_delete_timer(timerid);
}

int vaf_get_tick_count(void)
{
	return vm_get_tick_count();
}

//***********graphic***********

int vaf_load_image_resized(uchar* data, int length, int width, int height)
{
	return vm_graphic_load_image_resized(data, length, width, height);
}

int vaf_get_image_framecount(int addr)
{
	return vm_graphic_get_frame_number(addr);
}


int vaf_get_lcd_width(void)
{
	return vm_graphic_get_screen_width();
}

int vaf_get_lcd_height(void)
{
	return vm_graphic_get_screen_height();
}

int vaf_create_layer(int x, int y, int width, int height, int trans_color)
{
	return vm_graphic_create_layer(x, y, width, height, trans_color);
}

int vaf_clear_layer_bg(int handle)
{
	return vm_graphic_clear_layer_bg(handle);
}

int vaf_delete_layer(int handle)
{
	return vm_graphic_delete_layer(handle);
}

uchar* vaf_get_layer_buf(int handle)
{
	return vm_graphic_get_layer_buffer(handle);
}


int vaf_flush_layer(int* layer_handles, int count)  
{
	return vm_graphic_flush_layer(layer_handles, count);
}

int vaf_flush_layer_rect(int* layer_handles, int count, int x1, int y1, int x2, int y2)
{
#ifdef __FOR_MRE__
	return vaf_flush_layer(layer_handles, count);
#else
	return vm_graphic_flush_layer_by_xy(layer_handles, count, x1, y1, x2, y2);
#endif
}

int vaf_active_layer(int handle)
{
	return vm_graphic_active_layer(handle);
}

void vaf_set_clip(int x1, int y1, int x2, int y2)
{
	vm_graphic_set_clip(x1, y1, x2, y2);
}

void vaf_reset_clip(void)
{
	vm_graphic_reset_clip();
}

void vaf_line(uchar *buf, int x0, int y0, int x1, int y1, ushort color)
{
    vm_graphic_line(buf,  x0,  y0,  x1,  y1,  color);
}
void vaf_fill_rect(uchar *buf, int x, int y, int width, int height, ushort line_color, ushort back_color)
{
	vm_graphic_fill_rect(buf, x, y, width, height, line_color, back_color);
}


void vaf_rect(uchar *buf, int x, int y, int width, int height, ushort color)
{
	vm_graphic_rect(buf, x, y, width, height, color);
}

void vaf_fill_roundrect(uchar* frame_buf, int x, int y, int width, int height, int corner_width, int border_width, ushort border_color, ushort bg_color)
{
	int i;
	vm_graphic_fill_roundrect(frame_buf, x + border_width, y + border_width, width - border_width*2, height - border_width*2, corner_width, bg_color);
	for(i = border_width - 1;i >= 0;i--)
	{
		vm_graphic_roundrect(frame_buf, x + i, y + i, width - i*2, height - i*2, corner_width, border_color);
	}
}

void vaf_roundrect(uchar* frame_buf, int x, int y, int width, int height, int corner_width, int border_width, ushort border_color)
{
	int i;
	for(i = border_width - 1;i >= 0;i--)
	{
		vm_graphic_roundrect(frame_buf, x + i, y + i, width - i*2, height - i*2, corner_width, border_color);
	}
}

void vaf_ellipse (uchar * buf, int x, int y, int width, int height, ushort color)
{
	vm_graphic_ellipse(buf, x, y, width, height, color);
}

void vaf_fill_ellipse (uchar * buf, int x, int y, int width, int height, ushort color)
{
	vm_graphic_fill_ellipse(buf, x, y, width, height, color);
}

void vaf_gradient_fill_rect(uchar *buf, int x, int y, int width, int height, ushort line_color, ushort begincolor,ushort endcolor)
{
	int beginred  = VM_COLOR_GET_RED(begincolor);
	int begingreen = VM_COLOR_GET_GREEN(begincolor);
	int beginblue = VM_COLOR_GET_BLUE(begincolor);
	int endred  = VM_COLOR_GET_RED(endcolor);
	int endgreen = VM_COLOR_GET_GREEN(endcolor);
	int endblue = VM_COLOR_GET_BLUE(endcolor);
	float f =(float)2.0/(float)height;
	int ox = x;
	int oy = y;
	int i = 0;
	float p = 0;
	int r = 0, g = 0 , b = 0;
	for ( i = 0; i < height/2-1 ; ++i )
	{
		float n = f *  i ;
		
		int rr1,rr2,gg1,gg2,bb1,bb2;
		if ( n < 1)
		{
			p = n;
			rr1 = beginred;
			rr2 = endred;
			gg1 = begingreen;
			gg2 = endgreen;
			bb1 = beginblue;
			bb2 = endblue;
		}
		else p = 0;
		
		r = (int)(rr1 * ( 1 - p ) + rr2 * p);
		g = (int)(gg1 * ( 1 - p ) + gg2 * p);
		b = (int)(bb1 * ( 1 - p ) + bb2 * p);
		if ( height % 2 != 0 && i == height/2-2)
		{
			vm_graphic_fill_rect(buf,ox+1,oy+1,width-2,3, (ushort)V_RGB(r,g,b), (ushort)V_RGB(r,g,b));
		}
		else
		{
			vm_graphic_fill_rect(buf,ox+1,oy+1,width-2,2,(ushort)V_RGB(r,g,b),(ushort)V_RGB(r,g,b));
		}
		vm_graphic_rect(buf,x,y,width,height,line_color);
		oy += 2;
	}
}

void vaf_graphic_gradient_paint_rect(int handle, int x1, int y1, int x2, int y2, vaf_graphic_color color_start, vaf_graphic_color color_end,vaf_graphic_gp_style style)
{
	vm_graphic_color colorbegin,colorend;
	colorbegin.vm_color_565 = color_start.vaf_color_565;
	colorbegin.vm_color_888 = color_start.vaf_color_888;
	colorend.vm_color_565 = color_end.vaf_color_565;
	colorend.vm_color_888 = color_end.vaf_color_888;
	vm_graphic_gradient_paint_rect(handle,x1,  y1,  x2,  y2,  colorbegin,  colorend, style);
}


void vaf_gradient_fill_rect_noborder(uchar *buf, int x, int y, int width, int height, ushort begincolor,ushort endcolor)
{
	int beginred  = VM_COLOR_GET_RED(begincolor);
	int begingreen = VM_COLOR_GET_GREEN(begincolor);
	int beginblue = VM_COLOR_GET_BLUE(begincolor);
	int endred  = VM_COLOR_GET_RED(endcolor);
	int endgreen = VM_COLOR_GET_GREEN(endcolor);
	int endblue = VM_COLOR_GET_BLUE(endcolor);
	float f =(float)2.0/(float)height;
	int ox = x;
	int oy = y;
	int i = 0;
	float p = 0;
	int r = 0, g = 0 , b = 0;
	for ( i = 0; i < height/2 ; ++i )
	{
		float n = f *  i ;
		
		int rr1,rr2,gg1,gg2,bb1,bb2;
		if ( n < 1)
		{
			p = n;
			rr1 = beginred;
			rr2 = endred;
			gg1 = begingreen;
			gg2 = endgreen;
			bb1 = beginblue;
			bb2 = endblue;
		}
		else p = 0;
		
		r = (int)(rr1 * ( 1 - p ) + rr2 * p);
		g = (int)(gg1 * ( 1 - p ) + gg2 * p);
		b = (int)(bb1 * ( 1 - p ) + bb2 * p);
		if ( height % 2 != 0 && i == height/2-2)
		{
			vm_graphic_fill_rect(buf,ox,oy,width,3, (ushort)V_RGB(r,g,b), (ushort)V_RGB(r,g,b));
		}
		else
		{
			vm_graphic_fill_rect(buf,ox,oy,width,2,(ushort)V_RGB(r,g,b),(ushort)V_RGB(r,g,b));
		}
	 
		oy += 2;
	}
}
//******************************************************************

void vaf_textout(uchar* disp_buf, int x, int y, wchar* s, int length, ushort color)
{
	vm_graphic_textout(disp_buf, x, y, s, length, color);
}

int vaf_textout_to_layer(int handle, int x, int y, short* s, int length)
{
	return vm_graphic_textout_to_layer(handle, x, y, s, length);
}

void vaf_set_font(int size)
{
	vm_graphic_set_font(size);
}

int vaf_ucs2_to_default(char* dst, int size, wchar* src)
{
#if defined(__FOR_FACEBOOK__)
	return vm_ucs2_to_ascii(dst, size, src);
#elif
	return vm_ucs2_to_default(dst, size, src);
#endif
}

int vaf_default_to_ucs2(wchar* dst, int size, char* src)
{
#if defined(__FOR_FACEBOOK__)
	return vm_ascii_to_ucs2(dst, size, src);
#elif
	return vm_default_to_ucs2(dst, size, src);
#endif
}

int vaf_ucs2_to_gb2312(char* dst, int size, wchar* src)
{
	return vm_ucs2_to_gb2312(dst,size,src);
}
int  vaf_gb2312_to_ucs2(wchar* dst, int size, char* src)
{
	return vm_gb2312_to_ucs2(dst, size, src);//for china only, so use it, if we want to support outside, we can use other api.
}

int vaf_ucs2_to_ascii(char* dst, int size, wchar* src)
{
	return vm_ucs2_to_ascii(dst, size, src);
}

int vaf_ascii_to_ucs2(wchar* dst, int size, char* src)
{
	return vm_ascii_to_ucs2(dst, size, src);
}

int vaf_utf8_to_ucs2(uchar* utf8_code, ushort* ucs2_code)
{        
    VMUINT16 temp1, temp2;
    VMINT is_unrecognized = FALSE ;
    VMUINT step = 1,counter = 0, end = 0;
    VMUINT8* utf8string= utf8_code;
	
    if(!utf8_code || !ucs2_code){
		return 0;
    }
	
    end = strlen((char *)utf8_code);
    
    while(counter < end + 1){
		if(0x00 == (*utf8string & 0x80)){
			/* 1 byte UTF-8 Charater.*/
			temp1 = *((VMUINT8 *)(utf8string));
			//by ljt
			ucs2_code[0] = temp1;
			ucs2_code ++;
			//wstrcpy((VMWCHAR *)ucs2_code++, (VMWCHAR *)&temp1);
			step = 1;
			counter += step;
			utf8string += step;
			is_unrecognized = TRUE;
		}
		else if(0xc0 == (*utf8string & 0xe0) &&
			0x80 == (*(utf8string + 1) & 0xc0)
			){
			/* 2 bytes UTF-8 Charater.*/ 
			temp1 = (VMUINT16)(*utf8string & 0x1f);
			temp1 <<= 6;
			temp1 |= (VMUINT16)(*(utf8string + 1) & 0x3f);
			step = 2;
			counter += step;
			utf8string += step;
			//by ljt
			ucs2_code[0] = temp1;
			ucs2_code ++;
			//wstrcpy((VMWCHAR *)ucs2_code++, (VMWCHAR *)(&temp1));
			is_unrecognized = TRUE;
		}
		else if( 0xe0 == (*utf8string & 0xf0) &&
			0x80 == (*(utf8string +1) & 0xc0) &&
			0x80 == (*(utf8string + 2) & 0xc0)
			){
			/* 3bytes UTF-8 Charater.*/
			temp1 = (VMUINT16)(*utf8string &0x0f);
			temp1 <<= 12;
			temp2 = (VMUINT16)(*(utf8string+1) & 0x3F);
			temp2 <<= 6;
			temp1 = temp1 | temp2 | (VMUINT16)(*(utf8string+2) & 0x3F);
			step = 3;
			counter += step;
			utf8string += step;
			//by ljt
			ucs2_code[0] = temp1;
			ucs2_code ++;
			//wstrcpy((VMWCHAR *)ucs2_code++, (VMWCHAR *)(&temp1));
			is_unrecognized = TRUE;
		}
		else{
			temp1 =  *((VMUINT8 *)(utf8string));
			wstrcpy((VMWCHAR *)ucs2_code++, (VMWCHAR *)&temp1);
			is_unrecognized = TRUE;
			utf8string ++;
			counter ++;
		}
    }
    return is_unrecognized;
}

uchar vaf_ucs2_to_utf8(ushort *ucs2_code, uchar* utf8_code)
{
    VMINT length                = 0;
    VMINT counter                = 0;
    VMINT step                = 0;
    VMINT end                                = 0;
    VMUINT16 tmp                        = *ucs2_code;
    VMUINT8* out                        = utf8_code;
	
    if(!utf8_code){
		return length;
    }
	
	end = wstrlen((VMWCHAR *)ucs2_code);
	
    for(counter = 0; counter < end; counter++) {
		if(0x0080 > *ucs2_code){
			/* 1 byte UTF-8 Character.*/
			*out = (VMUINT8)(tmp);
			length++; 
			step = 1;
			ucs2_code ++;
			tmp = *(ucs2_code);
			out += step;
		}
		else if(0x0800 > *ucs2_code){
			if(*(out - 1) == 20) {
				*out = (VMUINT8)(tmp);
				length++; 
				step = 1;
				ucs2_code ++;
				tmp = *(ucs2_code);
				out += step;
				continue;
			}
			
			/*2 bytes UTF-8 Character.*/
			*out = ((VMUINT8)(tmp >> 6)) | 0xc0;
			*(out+1) = ((VMUINT8)(tmp & 0x003F)) | 0x80;
			length += 2;
			step = 2;
			ucs2_code ++;
			tmp = *(ucs2_code);
			out += step;
		}
		else {
			/* 3 bytes UTF-8 Character .*/
			*out = ((VMUINT8)(tmp >> 12)) | 0xE0;
			*(out+1) = ((VMUINT8)((tmp & 0x0FC0)>> 6)) | 0x80;
			*(out+2) = ((VMUINT8)(tmp & 0x003F)) | 0x80;
			length += 3;         
			step = 3;
			ucs2_code ++;
			tmp = *(ucs2_code);
			out += step;
		}
    }
    out++;
    *out = 0;
    
    return ++length;
}


void *vaf_malloc(int size)
{
	return vm_malloc(size);
}

void *vaf_calloc(int size)
{
	void* p = vm_malloc(size);
	memset(p, 0, size);
	return p;
}

void vaf_free(void* ptr)
{
	vm_free(ptr);
}

int vaf_wcslen(wchar* p)
{
	return vm_wstrlen(p);
}

int vaf_wcscpy(wchar* dst, wchar* src)
{
	return vm_wstrcpy(dst, src);
}

int vaf_wcscat(wchar* dst, wchar* src)
{
	return vm_wstrcat(dst, src);
}

int vaf_wcscmp(wchar* str_1, wchar* str_2)
{
	return vm_wstrcmp(str_1, str_2);
}

wchar* vaf_wcsstr(wchar * wcs1, wchar * wcs2) 
{ 
	wchar *cp = (wchar *) wcs1; 
	wchar *s1, *s2; 
	
	if ( !*wcs2) 
		return (wchar *)wcs1; 
	
	while (*cp) 
	{ 
		s1 = cp; 
		s2 = (wchar *) wcs2; 
		
		while ( *s1 && *s2 && !(*s1-*s2) ) 
			s1++, s2++; 
		
		if (!*s2) 
			return(cp); 
		
		cp++; 
	} 
	
	return(NULL); 
} 

int vaf_get_character_height(void)
{
	if(vaf_graphic_is_use_vector_font()==TRUE)
	{	
		if(font_size<=0)
		{
			short *strucs2=NULL;
			int width=0;
			int height=0;
			strucs2=(short *)vm_malloc(30);
			memset(strucs2,0,10);
			vm_gb2312_to_ucs2(strucs2, strlen("测试字体高度"), "测试字体高度");
			vm_graphic_measure_character(strucs2[0], &width, &height);
			vm_free(strucs2);
			font_size=height;
			return font_size;
		}
		else
		return font_size;
	}
	else
		return vm_graphic_get_character_height();

}

int vaf_get_string_width(wchar* s)
{
	return vm_graphic_get_string_width(s);
}
void vaf_graphic_fill_roundrect (uchar* buf, int x,int y, int width, int height, int  corner_width, ushort color)
{	
	vm_graphic_fill_roundrect(buf, x, y, width, height,  corner_width,  color);
}
void vaf_graphic_roundrect(uchar * buf, int x,int y, int width, int height, int  corner_width, ushort color)
{
	vm_graphic_roundrect(buf, x, y, width, height,  corner_width,  color);
}

img_property * vaf_get_img_property(int hcanvas, uchar frame_index)
{
	return vm_graphic_get_img_property(hcanvas, frame_index);
}

uchar* vaf_load_resource(char* res_name, int* res_size)
{
	return vm_load_resource(res_name, res_size);
}

int vaf_load_image(uchar *img, int img_len)
{
	return vm_graphic_load_image(img, img_len);
}

int vaf_create_canvas(int width,int height)
{
	return vm_graphic_create_canvas(width,height);
}

void vaf_delete_canvas(int hCanvas)
{
	vm_graphic_release_canvas(hCanvas);
}

uchar* vaf_get_canvas_buffer(int hcanvas)
{
	return vm_graphic_get_canvas_buffer(hcanvas);
}

void vaf_blt(uchar * dst_disp_buf, int x_dest, int y_dest, uchar * src_disp_buf, 
					int x_src, int y_src, int width, int height, int frame_index)
{
	vm_graphic_blt(dst_disp_buf, x_dest, y_dest, src_disp_buf, x_src, y_src, width, height, frame_index);	
}

int vaf_input_text(short* default_string, int input_max_size, int default_input_method, void (*input_text_cb)(VMINT state, VMWSTR text))
{
	return vm_input_text3(default_string, input_max_size, default_input_method, input_text_cb);
}



void vaf_log_init(char* filename, int log_level)
{
	vm_log_init(filename, log_level);
}

int vaf_get_removable_driver(void)
{
	return vm_get_removable_driver();
}

int vaf_get_cache_driver(void)
{
	int drv;
	drv = vm_get_removable_driver();
	if(drv < 0)
		drv = vaf_get_system_driver();
	return drv;
}

int vaf_get_system_driver(void)
{
	return vm_get_system_driver();
}

void vaf_find_close_ext(int handle)
{
   vm_find_close_ext(handle);
}
int vaf_find_next_ext(int handle,  vm_fileinfo_ext * direntry)
{
	return vm_find_next_ext(handle, direntry);
}


void vaf_set_volume(int volume)
{
	vm_set_volume(volume);
}

int vaf_has_sim_card(void)
{
	return vm_has_sim_card();
}
int vaf_sim_card_count(void)
{
	return vm_sim_card_count();
}

int vaf_file_open(short * filename, uint mode, uint binary)
{
	return vm_file_open(filename, mode, binary);
}

void vaf_file_close(int handle)
{
	vm_file_close(handle);
}

int vaf_file_read(int handle, void * data, uint length, uint * nread)
{
	return vm_file_read(handle, data, length, nread);
}

int vaf_file_write(int handle, void * data, uint length, uint * written)
{
	return vm_file_write(handle, data, length, written);
}

int vaf_file_commit(int handle)
{
	return vm_file_commit(handle);
}

int vaf_file_seek(int handle, int offset, int base)
{
	return vm_file_seek(handle, offset, base);
}

int vaf_file_tell(int handle)
{
	return vm_file_tell(handle);
}

int vaf_file_is_eof(int handle)
{
	return vm_file_is_eof(handle);
}

int vaf_file_getfilesize(int handle, uint * file_size)
{
	return vm_file_getfilesize(handle, file_size);
}

int vaf_file_delete(short * filename)
{
	return vm_file_delete(filename);
}

int vaf_file_rename(short * filename, short * newname)
{
	return vm_file_rename(filename, newname);
}

int vaf_file_mkdir(short * dirname)
{
	return vm_file_mkdir(dirname);
}

int vaf_file_rmdir(short * dirname)
{
	return vm_file_rmdir(dirname);
}

int vaf_file_set_attributes(short * filename, uchar attributes)
{
	return vm_file_set_attributes(filename, attributes);
}

int vaf_file_get_attributes(short * filename)
{
	return vm_file_get_attributes(filename);
}

operator_t vaf_get_operator(void)
{
	return vm_get_operator();
}





int vaf_get_lcd_type(void)
{
	int lcd_support;
	int lcd_width;
	int lcd_height;
	lcd_width = vaf_get_lcd_width();
	lcd_height = vaf_get_lcd_height();
	
	if(QCIF_WIDTH == lcd_width && QCIF_HEIGHT == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_QCIF;
	}
	else if(QCIF_LS_WIDTH == lcd_width && QCIF_LS_HEIGHT == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_QCIF_LS;
	}
	else if(QVGA_WIDTH == lcd_width && QVGA_HEIGHT == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_QVGA;
	}
	else if(QVGA_LS_WIDTH == lcd_width && QVGA_LS_HEIGHT == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_QVGA_LS;
	}
	else if(WQVGA_WIDTH == lcd_width && WQVGA_HEIGHT == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_WQVGA;
	}
	else if(WQVGA_HEIGHT == lcd_width && WQVGA_WIDTH == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_WQVGA_LS;
	}
	else if(HVGA_WIDTH == lcd_width && HVGA_HEIGHT == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_HVGA;
	}
	else if(HVGA_HEIGHT == lcd_width && HVGA_WIDTH == lcd_height)
	{
		lcd_support = ENUM_SUPPORT_HVGA_LS;
	}
	else
	{
		lcd_support = ENUM_SUPPORT_NONE;
	}
	return lcd_support;
}


int vaf_get_time(vaf_time_t* time)
{
	
	return vm_get_time((vm_time_t*)time);
}

int vaf_switch_power_saving_mode(power_saving_mode_enum mode)
{
	return vm_switch_power_saving_mode(mode);
}


int vaf_io_mdir(wchar* dir)
{
	return vm_file_mkdir((wchar*)dir);
}

int vaf_find_first_ext(short* pathname,vm_fileinfo_ext* direntry)
{
	return vm_find_first_ext(pathname, direntry);
}
int vaf_http_cancel(int handle)
{
	return vm_cancel_asyn_http_req(handle);
}

void vaf_http_free(int handle)
{
	vm_http_free_handle(handle);
}

int  vaf_graphic_is_use_vector_font(void)
{
#ifdef __FOR_MRE__
	return FALSE;
#else
	return vm_graphic_is_use_vector_font();
#endif
}

int vaf_open_wap_url( wchar* url )
{
	return vm_open_wap_url(url);
}

int vaf_set_active_sim_card(int card_id)
{
	return vm_set_active_sim_card(card_id);
}

char* vaf_get_imei( void )
{
	return vm_get_imei();
}

char* vaf_get_imsi( void )
{
	return vm_get_imsi();	
}
