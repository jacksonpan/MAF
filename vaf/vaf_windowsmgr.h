#ifndef __vaf_windowMgr_h__
#define __vaf_windowMgr_h__
//#include "vaf_window.h"
//max windows number
//32 have been unlimited...
//memory is so small...wtf!!!
#define MAXWINDOWSNUM 32

class VafArrayStack
{
public:
	VafArrayStack();
	~VafArrayStack();
	void *  Pop();
	bool Push(void * data);
	void* GetItem(int index);
	int GetCount();
	void* GetTop();
	bool Remove(int index);
	bool RemoveByHandle(void* index);
	void Clear();
protected:
	char index;
	long windowArray[MAXWINDOWSNUM];
};

typedef struct tag_vaf_winlist
{
	long hWnd;
}WINLIST,*PWINLIST;

class WindowsMgr
{
public:
	static int MessageProcss(long hWnd,int message, int sub_message, long wParam, long lParam);
	
	static bool AddWindow(long wnd);
	
	static bool DeleteWindow(long wnd);
	
	static long GetTopWindow();
	
	static bool SetTopWindow(long wnd);
	
	static long FindTopWindow();
	
	static void Init(int enable_mem);
	
	static void Free(); 
	
	static long FindWindowByID(int id);
	
	static void ExitProgram();
protected:
	static void TimerCallBack(int k);
	static PWINLIST pWndList;
	static PWINLIST pCur_Wnd;

	static bool DestroyWindows();
	static void SetNoneTopWindow();	
private:
	WindowsMgr(){};
	~WindowsMgr(){};
	static VafArrayStack * pStack;
	static VafArrayStack * pDesStack;
	static int timerID;
//	static int finishpaintID;
//	static UiWindow* finishpainthWnd;
 
	static int coreDebugTimerID;
	static void CoreDebugTimer(int t);
};

#endif