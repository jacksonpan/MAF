#include "vaf_windowscore.h"
#include "vaf_window.h"
#include "vaf_windowsmgr.h"
#include "vaf_uibase.h"

class WindowsMgr;

typedef struct _vaf_winlist
{
	long hWnd;
	struct _vaf_winlist* next;
}vaf_winlist;

vaf_winlist* cur_hwnd;
vaf_winlist* destroy_hwnd;
int destroy_timer = -1;
static bool destroy_is_processing = false;
void vaf_winmgr_free()
{
	UiTimer::Destroy();
}
void vaf_winmgr_init(void)
{
	cur_hwnd = NULL;
}
void vaf_exit_program_by_mgr()
{
	WindowsMgr::ExitProgram();
}
int PostWinMessage(long hWnd,int message, int sub_message, long wParam, long lParam)
{
	return WindowsMgr::MessageProcss(hWnd,message,sub_message,wParam,lParam);
}
int PostTopWinMessage(int message, int sub_message, long wParam, long lParam)
{
	return WindowsMgr::MessageProcss(WindowsMgr::GetTopWindow(),message,sub_message,wParam,lParam);
} 
long vaf_get_top_window_hwnd(void)
{
	return WindowsMgr::GetTopWindow();
} 
void vaf_eint_to_refresh_window(void)
{
	PostTopWinMessage(MSG_CORE_REFRESH,NULL,NULL,NULL);  
}
 
void KeyHandleProc(int key_event, int key_code)
{
	PostTopWinMessage(MSG_KEY_EINT, key_event, key_code, 0);
}

void TouchHandleProc(VMINT touch_event, VMINT x, VMINT y)
{ 
	PostTopWinMessage(MSG_TOUCH_EINT, touch_event, x, y);
}
long vaf_get_hwnd_by_id(int id)
{
	return WindowsMgr::FindWindowByID(id);
}	
int vaf_winmgr_msg_proc(int message, int sub_message, long wParam, long lParam)
{  
	return PostTopWinMessage(message,sub_message,wParam,lParam);
} 
