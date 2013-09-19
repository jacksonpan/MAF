#ifndef __vaf_window_h__
#define __vaf_window_h__ 

#include "vaf_uibase.h"
#include "vaf_controlsmanager.h"
#include "vaf_control.h" 
#include "vaf_windowscore.h" 

enum
{
	ID_NULL = 0,
	ID_BACK
};
  
/**
* @brief The Basic Window Class, we call it "UiWindow"
*/
class UiWindow : public UiBase
{
	friend class UiControl;
public:
	UiWindow(void);
	virtual ~UiWindow(void);
	
	/**
	* @brief Get the window is created
	* @return true or false
	*/
	bool GetWinIsCreated(void);

	/**
	* @brief Get the window's parent window handle
	* @return the parent window handle. If no parent window, then return NULL;
	*/
	long GetParenthWnd(void);

	/**
	* @brief Create the window's property
	* @param xPos the x position
	* @param yPos the y position
	* @param nwidth the window width
	* @param nheight the window height
	* @param nhwndParent the parent window handle
	* @param nID the window id
	*/
	void Create(int xPos, int yPos, int nwidth, int nheight, long nhwndParent, int nID);

	/**
	* @brief Show the window
	* @param flag true is show, false is doing nothing
	*/
	void Show(bool flag);

	/**
	* @brief Hide the window
	*/
	void Hide(void);

	/**
	* @brief Destroy the window
	* @param flag when the flag is ID_NULL, then the vaf will destroy the window and do nothing. 
	* When the flag is ID_BACK, then the vaf will destroy the window and show the previous window.
	*/
	void Destroy(int flag);

	/**
	* @brief Set the window's background color
	* @param color the color
	*/
	void SetBackgroundColor(ushort color);

	/**
	* @brief Get the window's background color
	* @return color the backgournd color
	*/
	ushort GetBackgroundColor(void);

	/**
	* @brief Is enable the backgournd color
	* @param flag true or false
	*/
	void IsEnableBackgroundColor(bool flag);

	/**
	* @brief Get is enable the backgournd color
	* @return is enable the background color
	*/
	bool GetIsEnableBackgroundColor(void);

	/**
	* @brief Paint the controls
	* @param handle the layers's handle
	*/
	void PaintControls(int* handle);

	/**
	* @brief Add controls to the window, and save the control's handle to the controls's list
	* @param control the control's pointer
	*/
	void AddUiControl(UiControl* control);

	/**
	* @brief Get the window is the top window
	* @return true or false
	*/
	bool GetIsTopWindow(void);

	/**
	* @brief Get the focused control in the window
	* @return -1 or id
	*/
	int GetWinFocusedID(void);

	/**
	* @brief Update the window
	*/
	void Update(void);
	
	/**
	* @brief Update the window
	* @param flag UPDATE_FLUSH or UPDATE_NONE
	*/
	void UpdateEx(int flag = UPDATE_FLUSH);

	/**
	* @brief Is enable the auto change focus
	* @param flag true or false
	*/
	void IsEnableAutoChangeFocus(bool flag);

	/**
	* @brief Get is enable the auto change focus
	* @return flag true or false
	*/
	bool GetIsEnableAutoChangeFocus(void);

	/**
	* @brief The window's message process
	* @param message the message id
	* @param sub_message the sub message id
	* @param wParam the first param
	* @param lParam the second param
	* @return no useless
	*/
	int MessageProc(int message, int sub_message, long wParam, long lParam);

	long PostUserMessage(int message,int sub_message,long wP,long lP);
public:

	/**
	* @brief The window initialization, it must be overload by developers, then you can initialize some resources
	* @return no useless
	*/
	virtual int OnInitWnd(void);

	/**
	* @brief The user window's message process, it must be overload by developers, then you can process some messages which include system's or user's
	* @param message the message id
	* @param sub_message the sub message id
	* @param wParam the first param
	* @param lParam the second param
	* @return no useless
	*/
	virtual int UsrMessageProc(int message, int sub_message, long wParam, long lParam);

	/**
	* @brief Paint the window, it must be overload by developers, then you can paint the window what you want
	* @param handle the layers's handle
	* @param rcRect the window's rect
	*/
	virtual void Paint(int* handle, RECT* rcRect);

	//virtual void FinishPaint(void);

	bool GetIsDestroy();

	void DelayDestroy();

	virtual void OnDispose(void);

	bool isDestroy;
protected:
	int UsrMessageProcInner(int message, int sub_message, long wParam, long lParam);
	
public:
	bool can_release;
	/**
	* @brief save the window which is the top window
	*/
	bool is_top_window;
private:

	/**
	* @brief save the window which is the created
	*/
	bool is_created;
	
	/**
	* @brief save the background color
	*/
	unsigned short bg_color;

	/**
	* @brief save the window which is enable the background color
	*/
	bool enable_bg_color;

public:
	/**
	* @brief the controls's manager
	*/
	UiCtrManager* CtrManager;

	/**
	* @brief save the parent window handle
	*/
	long parent_hwnd;

}; 
#endif
