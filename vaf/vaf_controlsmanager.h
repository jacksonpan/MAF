#ifndef __vaf_controlsmanager_h__
#define __vaf_controlsmanager_h__


#include "CVArray.h"
#include "vaf_control.h"

class UiControl;

class UiCtrManager
{
	friend class UiControl;
public:
	UiCtrManager(void);
	~UiCtrManager(void);
public:
	void AddUIControl(UiControl* control);
	void RemoveUIControl(UiControl* control);
	void RemoveAllUIControls(void);
	UiControl* GetUIControl(long handle = -1, int ID = -1);
	int GetFocusedID(void);
	int GetCount();
	CVArray* GetControlList(void);
public:
	int CtrManagerMessageProc(int message, int sub_message, long wParam, long lParam);
	int PostMessage(int message, int sub_message, long wParam, long lParam);
	void IsEnableAutoChangeFocus(bool flag);
	bool GetIsEnableAutoChangeFocus(void);
	void SetParenthWnd(long lhWnd);
private:
	CVArray* controls;
	long parent_hwnd;
	bool enable_auto_change_focus;
};


#endif