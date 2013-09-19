#ifndef __vaf_core_h__
#define __vaf_core_h__

#define ENABLE_LOG		1
#define UNABLE_LOG		0

#define ENABLE_MEM		1
#define UNABLE_MEM		0

extern void vaf_reg_usr_sysevt_callback(void (*handle)(int message, int param));
extern void vaf_reg_usr_keyboard_callback(void (*handle)(int event, int keycode));
extern void vaf_reg_usr_pen_callback(void (*handle)(int event, int x, int y));

extern void vaf_handle_sysevt(int message, int param);
extern void vaf_handle_keyevt(int event, int keycode);
extern void vaf_handle_penevt(int event, int x, int y);
extern void vaf_register_app_entry(void (*entry)(void));
extern void vaf_register_app_unload(void (*unload)(void));
extern void vaf_core_init(int enable_log, int enable_mem);

#endif
