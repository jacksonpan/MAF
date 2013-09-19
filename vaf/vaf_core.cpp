#include "vaf_core.h"
#include "vaf_include.h"
#include "vaf_uibase.h"
#include "vaf_windowscore.h"
#include "vaf_windowsmgr.h"

void vaf_core_msg_proc(int message, int sub_message, long wParam, long lParam);
void vaf_debug_init(int enable_debug);

extern void (*vaf_app_unload)(void);

void (*vaf_app_entry)(void);
void (*vaf_app_unload)(void);
void (*vaf_usr_handle_sysevt)(int message, int param);
void (*vaf_usr_handle_keyevt)(int event, int keycode);
void (*vaf_usr_handle_penevt)(int event, int x, int y);

static int vaf_app_is_login = 0;

void vaf_core_init(int enable_log, int enable_mem)
{
	vm_reg_sysevt_callback(vaf_handle_sysevt);
	vm_reg_keyboard_callback(vaf_handle_keyevt);
	vm_reg_pen_callback(vaf_handle_penevt);

	vaf_app_entry = NULL;
	vaf_app_unload = NULL;
	vaf_usr_handle_sysevt = NULL;
	vaf_usr_handle_keyevt = NULL;
	vaf_usr_handle_penevt = NULL;
	
	WindowsMgr::Init(enable_mem);
	UiTimer::Init();
	vaf_winmgr_init();
	vaf_font_init();
	vaf_debug_init(enable_log);
}

void vaf_reg_usr_sysevt_callback(void (*handle)(int message, int param))
{
	if(handle)
	{
		vaf_usr_handle_sysevt = handle;
	}
}

void vaf_reg_usr_keyboard_callback(void (*handle)(int event, int keycode))
{
	if(handle)
	{
		vaf_usr_handle_keyevt = handle;
	}
}

void vaf_reg_usr_pen_callback(void (*handle)(int event, int x, int y))
{
	if(handle)
	{
		vaf_usr_handle_penevt = handle;
	}
}

void vaf_register_app_entry(void (*entry)(void))
{
	if(entry)
	{
		vaf_app_entry = entry;
	}
	else
	{
		vaf_app_entry = NULL;
	}
}

void vaf_register_app_unload(void (*unload)(void))
{
	if(unload)
	{
		vaf_app_unload = unload;
	}
	else
	{
		vaf_app_unload = NULL;
	}
}

void vaf_handle_sysevt(int message, int param)
{
	vaf_core_msg_proc(message, 0, param, 0);
	if(vaf_usr_handle_sysevt)
	{
		vaf_usr_handle_sysevt(message, param);
	}
}

void vaf_handle_keyevt(int event, int keycode)
{
	switch(event)
	{
	case VM_KEY_EVENT_DOWN:
		vaf_core_msg_proc(MSG_KEY_EINT, MSG_KEY_DOWN, keycode, 0);
		break;
	case VM_KEY_EVENT_UP:
		vaf_core_msg_proc(MSG_KEY_EINT, MSG_KEY_UP, keycode, 0);
		break;
	}

	if(vaf_usr_handle_keyevt)
	{
		vaf_usr_handle_keyevt(event, keycode);
	}
}

void vaf_handle_penevt(int event, int x, int y)
{
	switch(event)
	{
	case VM_PEN_EVENT_TAP:
		vaf_core_msg_proc(MSG_TOUCH_EINT, MSG_TOUCH_DOWN, x, y);
		break;
	case VM_PEN_EVENT_MOVE:
		vaf_core_msg_proc(MSG_TOUCH_EINT, MSG_TOUCH_MOVE, x, y);
		break;
	case VM_PEN_EVENT_RELEASE:
		vaf_core_msg_proc(MSG_TOUCH_EINT, MSG_TOUCH_UP, x, y);
		break;
	} 
	if(vaf_usr_handle_penevt)
	{
		vaf_usr_handle_penevt(event, x, y);
	}
}

void vaf_core_msg_proc(int message, int sub_message, long wParam, long lParam)
{
	switch(message)
	{  
	case MSG_SYS_ACTIVE: 
		{
			PostTopWinMessage(message, sub_message, wParam, lParam); 
		}
		break;
	case MSG_SYS_PAINT: 
		vaf_create_layers();
		if(vaf_app_is_login == 0) 
		{
			if(vaf_app_entry)
			{
				vaf_app_entry();
			}
			else
			{
// 				vaf_exit_app();
				WindowsMgr::ExitProgram();
			}
			vaf_app_is_login = 1;
		}
		else
		{
			vaf_eint_to_refresh_window();
		}
		PostTopWinMessage(message, sub_message, wParam, lParam); 
		break;
	case MSG_SYS_HIDE:
	case MSG_SYS_INACTIVE:
		PostTopWinMessage(message, sub_message, wParam, lParam); 
		vaf_delete_layers();
		break;
	case MSG_SYS_CREATE: 
	case MSG_KEY_EINT:
	case MSG_SYS_QUIT:
	case MSG_TOUCH_EINT:
		PostTopWinMessage(message, sub_message, wParam, lParam); 
 		break; 
	} 
}
 

void vaf_debug_init(int enable_debug)
{
	int drv = -1;
	char	path[255] = {0};

	if(enable_debug == UNABLE_LOG)
	{
		return;
	}
	
	drv = vaf_get_removable_driver();	//优先获取移动盘符
	if(drv < 0) 						//不存在移动盘
	{
		drv = vaf_get_system_driver();	//获取系统盘
	}
	
	sprintf(path, "%c:\\vaf.log", drv);
	vaf_log_init(path, VAF_DEBUG_LEVEL);
	vaf_debug("Application Start!");
}
