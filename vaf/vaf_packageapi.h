#ifndef __vaf_packageapi_h__
#define  __vaf_packageapi_h__

#include "vaf_include.h"


#define VAF_DEBUG_LEVEL	VM_DEBUG_LEVEL

#if defined(APP_RELEASE)
#define vaf_debug
#else
#define vaf_debug	vm_log_debug
#endif

#define vaf_char_info vm_graphic_char_info



/**
 * 输入文字，默认输入法为拼音。
 */
#define V_INPUT_METHOD_TEXT			VM_INPUT_METHOD_TEXT

/** 
 * 输入密码，默认输入法为英文字母，输入内容用星号覆盖。
 */
#define V_INPUT_METHOD_PASSWORD		VM_INPUT_METHOD_PASSWORD

/** 
 * 输入数字，默认输入法为数字。
 */
#define V_INPUT_METHOD_NUMERIC		VM_INPUT_METHOD_NUMERIC

/**
 * 输入小写英文字母，默认输入法为小写英文字母。
 */
#define V_INPUT_METHOD_ALPHABETIC	VM_INPUT_METHOD_ALPHABETIC

typedef struct frame_prop img_property;

typedef vm_fileinfo_ext vaf_fileinfo_ext;
#ifdef  __cplusplus
extern "C" {
#endif


	enum enum_lcd_support
	{
		ENUM_SUPPORT_START = 0,
			ENUM_SUPPORT_QCIF = ENUM_SUPPORT_START,
			ENUM_SUPPORT_QCIF_LS,
			ENUM_SUPPORT_QVGA,
			ENUM_SUPPORT_QVGA_LS,
			ENUM_SUPPORT_WQVGA,
			ENUM_SUPPORT_WQVGA_LS,
			ENUM_SUPPORT_HVGA,
			ENUM_SUPPORT_HVGA_LS,
			
			ENUM_SUPPORT_NONE,
			ENUM_SUPPORT_END
	};

extern void vaf_exit_app(void);
extern int vaf_create_timer(ulong millisec, void (*callback)(int tid));
extern int vaf_delete_timer(int timerid);
extern int vaf_get_tick_count(void);
//***********************************graphic**********************************************
typedef enum
{
    VAF_GDI_GP_HOR = 0,  //水平
		VAF_GDI_GP_VER,      //垂直
		VAF_GDI_GP_DIA,      //斜45度
		VAF_GDI_GP_DIA_INV,  //反向斜45度
		VAF_GDI_GP_FLIP      //中间往2边 
}vaf_graphic_gp_style;
typedef struct _vaf_graphic_color{
	uint vaf_color_565;//565格式的颜色
	uint vaf_color_888;//888格式的颜色
}vaf_graphic_color;
extern int vaf_get_lcd_type(void);
extern int vaf_get_lcd_width(void);
extern int vaf_get_lcd_height(void);
extern int vaf_create_layer(int x, int y, int width, int height, int trans_color);
extern int vaf_clear_layer_bg(int handle);
extern int vaf_delete_layer(int handle);
extern uchar* vaf_get_layer_buf(int handle);
extern int vaf_flush_layer(int* layer_handles, int count);
extern int vaf_flush_layer_rect(int* layer_handles, int count, int x1, int y1, int x2, int y2);
extern int vaf_active_layer(int handle);
extern void vaf_set_clip(int x1, int y1, int x2, int y2);
extern void vaf_reset_clip(void);
extern void vaf_line(uchar *buf, int x0, int y0, int x1, int y1, ushort color);
extern void vaf_fill_rect(uchar *buf, int x, int y, int width, int height, ushort line_color, ushort back_color);
extern void vaf_rect(uchar *buf, int x, int y, int width, int height, ushort color);
extern void vaf_fill_roundrect(uchar* frame_buf, int x, int y, int width, int height, int corner_width, int border_width, ushort border_color, ushort bg_color);
extern void vaf_roundrect(uchar* frame_buf, int x, int y, int width, int height, int corner_width, int border_width, ushort border_color);
extern void vaf_ellipse (uchar * buf, int x, int y, int width, int height, ushort color);
extern void vaf_fill_ellipse (uchar * buf, int x, int y, int width, int height, ushort color);
extern void vaf_gradient_fill_rect(uchar *buf, int x, int y, int width, int height, ushort line_color, ushort begincolor,ushort endcolor);
extern void vaf_graphic_gradient_paint_rect(int handle, int x1, int y1, int x2, int y2, vaf_graphic_color color_start, vaf_graphic_color color_end,vaf_graphic_gp_style style);
extern void vaf_gradient_fill_rect_noborder(uchar *buf, int x, int y, int width, int height, ushort begincolor,ushort endcolor);
extern int vaf_get_string_width(short * str);
extern int vaf_textout_to_layer(int handle, int x, int y, wchar* s, int length);
extern void vaf_textout(uchar* disp_buf, int x, int y, wchar* s, int length, ushort color);
extern void vaf_set_font(int size);
extern int vaf_get_character_height(void);
extern int vaf_input_text(short* default_string, int input_max_size, int default_input_method, void (*input_text_cb)(int state, VMWSTR text));
extern int vaf_wcslen(short * p);
extern int vaf_has_sim_card(void);
extern int vaf_sim_card_count(void);
extern int vaf_ucs2_to_default(char* dst, int size, wchar* src);
extern int  vaf_default_to_ucs2(wchar* dst, int size, char* src);
extern int vaf_ucs2_to_gb2312(char* dst, int size, wchar* src);
extern int vaf_gb2312_to_ucs2(wchar* dst, int size, char* src);
extern int vaf_ucs2_to_ascii(char* dst, int size, wchar* src);
extern int vaf_ascii_to_ucs2(wchar* dst, int size, char* src);
extern int vaf_utf8_to_ucs2(uchar * dst, ushort * src);
extern uchar vaf_ucs2_to_utf8(ushort *ucs2_code, uchar* utf8_code);
extern void *vaf_malloc(int size);
extern void *vaf_calloc(int size);
extern void vaf_free(void* ptr);
extern void vaf_free_str(void * ptr);
extern int vaf_wcslen(wchar* p);
extern int vaf_wcscpy(wchar* dst, wchar* src);
extern int vaf_wcscat(wchar* dst, wchar* src);
extern int vaf_wcscmp(wchar* str_1, wchar* str_2);
extern wchar* vaf_wcsstr(wchar * wcs1, wchar * wcs2) ;
extern int vaf_get_character_height(void);
extern int vaf_get_string_width(wchar* s);
extern void vaf_graphic_fill_roundrect (uchar * buf, int x,int y, int width, int height, int  corner_width, ushort color);
extern void vaf_graphic_roundrect(uchar * buf, int x,int y, int width, int height, int  corner_width, ushort color);

extern int vaf_load_image_resized(uchar* data, int length, int width, int height);
extern img_property * vaf_get_img_property(int hcanvas, uchar frame_index);
extern uchar* vaf_load_resource(char* res_name, int* res_size);
extern int vaf_load_image(uchar *img, int img_len);
extern int vaf_create_canvas(int width,int height);
extern void vaf_delete_canvas(int hCanvas);
extern uchar* vaf_get_canvas_buffer(int hcanvas);
extern void vaf_blt(uchar * dst_disp_buf, int x_dest, int y_dest, uchar * src_disp_buf, 
			 int x_src, int y_src, int width, int height, int frame_index);
extern int vaf_get_image_framecount(int addr);
extern int  vaf_graphic_is_use_vector_font(void);

extern operator_t vaf_get_operator(void);

extern void vaf_log_init(char* filename, int log_level);
extern int vaf_get_removable_driver(void);
extern int vaf_get_cache_driver(void);


extern int vaf_get_system_driver(void);
extern void vaf_find_close_ext(VMINT handle);
extern int vaf_find_next_ext(int handle, vm_fileinfo_ext * direntry);


extern int vaf_switch_power_saving_mode(power_saving_mode_enum mode);
extern void vaf_set_volume(int volume);

extern int vaf_file_open(short * filename, uint mode, uint binary);
extern void vaf_file_close(int handle);
extern int vaf_file_read(int handle, void * data, uint length, uint * nread);
extern int vaf_file_write(int handle, void * data, uint length, uint * written);
extern int vaf_file_commit(int handle);
extern int vaf_file_seek(int handle, int offset, int base);
extern int vaf_file_tell(int handle);
extern int vaf_file_is_eof(int handle);
extern int vaf_file_getfilesize(int handle, uint * file_size);
extern int vaf_file_delete(short * filename);
extern int vaf_file_rename(short * filename, short * newname);
extern int vaf_file_mkdir(short * dirname);
extern int vaf_file_rmdir(short * dirname);
extern int vaf_file_set_attributes(short * filename, uchar attributes);
extern int vaf_file_get_attributes(short * filename);

typedef struct vaf_time_t {
	int year;		/* 年份。			*/
	int mon;		/* 月份，从1开始。	*/
	int day;		/* 天，从1开始。	*/
	int hour;		/* 小时，24小时制。	*/
	int min;		/* 分钟。			*/
	int sec;		/* 秒。				*/
} vaf_time_t;
int vaf_get_time(vaf_time_t* time);
extern int vaf_find_first_ext(short* pathname,vm_fileinfo_ext* direntry);

int vaf_io_mdir(wchar* dir);

extern int vaf_http_cancel(int handle);
extern void vaf_http_free(int handle);


/**
 * 打开WAP浏览器并转到相应的地址，本函数只能在进程处在前台状态下才能调用。
 *
 * @param url					WAP地址。
 * @return					打开流程器是否成功。
 * @retval					VM_OPEN_WAP_URL_SUCCESS 打开WAP流程器成功。
 * @retval					VM_OPEN_WAP_URL_ERROR_PARAM 参数错误，打开浏览器失败。
 * @retval					VM_OPEN_WAP_URL_NO_SERVICE 当前浏览器不可用。
 * @retval					VM_OPEN_WAP_URL_ERROR_STATUS 如果进程不在前台调用本函数，则返回失败。
 */
int vaf_open_wap_url(wchar* url);

/**
 *	设置当前sim卡
 *
 *	@param card_id sim卡的序号,有效数据VM_SIM_SIM1=卡1，VM_SIM_SIM2=卡2
 *
 *	@return		TRUE=设置成功, FALSE=设置失败
 */
int vaf_set_active_sim_card(int card_id);

/**
 * 获得手机卡的IMEI。
 *
 * 如果支持双IMEI号的情况，只返回当前对应卡的IMEI。
 * 
 * @return 				手机卡的imei 号。如果返回的VMSTR
 *								指向一个NULL那么表示系统还正在得到IMEI，
 *								请稍候调用本函数。
 */
extern char* vaf_get_imei(void);

/**
 * 获得手机卡的IMSI，只返回当前对应卡的IMEI。。
 * 
 * @return 				手机卡的imsi 号。
 */
extern char* vaf_get_imsi(void);

#ifdef  __cplusplus
}
#endif




#endif
