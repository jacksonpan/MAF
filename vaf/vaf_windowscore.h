#ifndef __vaf_windowscore_h__
#define __vaf_windowscore_h__

// #include "vaf_include.h"
	
extern void vaf_winmgr_init(void);
extern void vaf_winmgr_free(void);
extern long vaf_get_top_window_hwnd(void); 
extern void vaf_eint_to_refresh_window(void);
extern long vaf_get_hwnd_by_id(int id);
extern int PostTopWinMessage(int message, int sub_message, long wParam, long lParam);
extern int PostWinMessage(long hWnd,int message, int sub_message, long wParam, long lParam);
extern void vaf_exit_program_by_mgr();

#endif
