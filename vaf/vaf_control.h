#ifndef __vaf_control_h__
#define __vaf_control_h__
#include "vaf_controlsmanager.h"
#include "vaf_uibase.h"
#include "vaf_window.h"

/**
* @brief The Basic Control Class, we call it "UiControl"
*/
class UiControl : public UiBase
{
	friend class UiWindow;
	friend class UiCtrManager;
public:
	UiControl(void);
	virtual ~UiControl(void);
	
	/**
	* @brief Is enable the key handle, if set the false, then the control won't receive the key handle
	* @param flag true or false
	*/
	void IsEnableKeyHandle(bool flag);

	/**
	* @brief Get is enable the key handle
	* @return flag true or false
	*/
	bool GetIsEnableKeyHandle(void);

	/**
	* @brief Is enable the touch handle, if set the false, then the control won't receive the touch handle
	* @param flag true or false
	*/
	void IsEnableTouchHandle(bool flag);
	
	/**
	* @brief Get is enable the touch handle
	* @return flag true or false
	*/
	bool GetIsEnableTouchHandle(void);

	/**
	* @brief Is enable the focus, if set the false, then the control won't have the focus
	* @param flag true or false
	*/
	void IsEnableFocus(bool flag);

	/**
	* @brief Get is enable the focus
	* @return flag true or false
	*/
	bool GetIsEnableFocus(void);

	/**
	* @brief Is the control focused, if set the true, then the control is focused. Only allowed one focused in all controls of one window
	* @param flag true or false
	*/
	void IsFocused(bool flag);

	/**
	* @brief Get is enable the control focused
	* @return flag true or false
	*/
	bool GetIsFocused(void);

	/**
	* @brief Is the control visible, if set the true, then the control is visible
	* @param flag true or false
	*/
	void IsVisible(bool flag);

	/**
	* @brief Get is enable the control visble
	* @return flag true or false
	*/
	bool GetIsVisible(void);

	/**
	* @brief Is enable the control, if set the false, then the control won't show and receive no handle
	* @param flag true or false
	*/
	void IsEnableControl(bool flag);

	/**
	* @brief Get is enable the control
	* @return flag true or false
	*/
	bool GetIsEnableControl(void);

	/**
	* @brief Is enable the over all key handle, if set the true, then the control will receive the key handle without focus
	* @param flag true or false
	*/
	void IsEnableOverallKeyHandle(bool flag);

	/**
	* @brief Get is enable the over all key handle
	* @return flag true or false
	*/
	bool GetIsEnableOverallKeyHandle(void);

	/**
	* @brief Is enable the over all touch handle, if set the true, then the control will receive the touch handle without focus
	* @param flag true or false
	*/
	void IsEnableOverallTouchHandle(bool flag);

	/**
	* @brief Get is enable the over all touch handle
	* @return flag true or false
	*/
	bool GetIsEnableOverallTouchHandle(void);

	/**
	* @brief Is enable post id to the window, if set the true, then the control will receive the id in the UsrMessageProc method
	* @param flag true or false
	*/
	void IsEnablePostID(bool flag);

	/**
	* @brief Get is enable post id to the window
	* @return flag true or false
	*/
	bool GetIsEnablePostID(void);

	/**
	* @brief Set the window handle which the control is in the window
	* @param lhWnd the window handle
	*/
	void SetCurhWnd(long lhWnd);

	/**
	* @brief Get the window handle which the control is in the window
	* @return the window handle
	*/
	long GetCurhWnd(void);

	/**
	* @brief Set the control's background color
	* @param color the color
	*/
	void SetBackgroundColor(ushort color);

	/**
	* @brief Get the window's background color
	* @return color the backgournd color
	*/
	ushort GetBackgroundColor(void);

	/**
	* @brief Set the flag that determines the control will or not lost focus,sys will not call it.
	* @param lost or not
	*/
	void SetIsLostFocus(bool flag); 

	int PostWinMessage(int message, int sub_message, long wParam, long lParam);

public:
	
	/**
	* @brief The control's message process, if you really need to overload, then you can make the method yourself
	* @param message the message id
	* @param sub_message the sub message id
	* @param wParam the first param
	* @param lParam the second param
	* @return no useless
	*/
	virtual int MessageProc(int message, int sub_message, long wParam, long lParam);

	/**
	* @brief Update the control, if you really need to overload, then you can make the method yourself
	*/
	virtual void Update(void);
	
	/**
	* @brief Update the control, if you really need to overload, then you can make the method yourself
	* @param flag UPDATE_FLUSH or UPDATE_NONE
	*/
	virtual void UpdateEx(int flag = UPDATE_FLUSH);

	/**
	* @brief Paint the control, you can overload it, then paint it yourself
	* @param handle the layers's handle
	* @param rcRect the ui's rect
	* @param nx the x position
	* @param ny the y position
	* @param nwidth the control's width
	* @param nheight the control's height
	*/
	virtual void Paint(int* handle, RECT* rcRect, int nx, int ny, int nwidth, int nheight);

	/**
	* @brief Paint the control's focused status, you can overload it, then paint it yourself, we provide a default style
	* @param handle the layers's handle
	* @param rcRect the ui's rect
	* @param nx the x position
	* @param ny the y position
	* @param nwidth the control's width
	* @param nheight the control's height
	*/
	virtual void PaintFocus(int* handle, RECT* rcRect, int nx, int ny, int nwidth, int nheight);
	
private:
	
	/**
	* @brief save the control which is the enable
	*/
	bool enable_control;

	/**
	* @brief save the control which is the enable the key handle
	*/
	bool enable_keyhandle;

	/**
	* @brief save the control which is the enable the over all key handle
	*/
	bool enable_overall_keyhandle;

	/**
	* @brief save the control which is the enable the touch handle
	*/
	bool enable_touchhandle;

	/**
	* @brief save the control which is the enable the over all touch handle
	*/
	bool enable_overall_touchhandle;

	/**
	* @brief save the control which is the enable the focus
	*/
	bool enable_focus;

	/**
	* @brief save the control which is focused
	*/
	bool is_focused;

	/**
	* @brief save the control which is visible
	*/
	bool is_visible;

	/**
	* @brief save the control which need to  post id to the window
	*/
	bool enable_postid;
protected:
	/**
	* @brief save the control which can lost the focus
	*/
	bool is_lost_focus;
public:

	/**
	* @brief save the window which the control is in the window
	*/
	long where_hwnd;
	
	/**
	* @brief save the control's background color
	*/
	ushort bg_color;
};



#endif
