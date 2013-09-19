#ifndef __vaf_uibase_h__
#define __vaf_uibase_h__

#include "vaf_include.h"
#include "CVString.h"

enum
{
	UPDATE_FLUSH = 0,
	UPDATE_RECT,
	UPDATE_NONE
};

enum
{
	ENUM_LAYERS_NONE = 0,
	ENUM_LAYERS_LAYER0,
	ENUM_LAYERS_LAYER1,
	ENUM_LAYERS_BOTH
};
/**
* @brief The Basic UI Class, we call it "UiBase"
*/
class UiBase
{
public:
	UiBase(void);
	virtual ~UiBase(void);
	
public:
	
	
	/**
	* @brief Set the UI's Position
	* @param nx the x coordinate
	* @param ny the y coordinate
	* @param nwidth the ui's width
	* @param nheight the ui's height
	*/
	void SetPos(int nx, int ny, int nwidth, int nheight);

	/**
	* @brief Set the UI's align Position
	* @param toLeft the distance between the screen's left border and the ui's left border
	* @param toTop the distance between the screen's top border and the ui's top border
	* @param toRight the distance between the screen's right border and the ui's right border
	* @param toBottom the distance between the screen's bottom border and the ui's bottom border
	*/
	void SetAlignPos(int toLeft, int toTop, int toRight, int toBottom);

	/**
	* @brief Set the UI's Name
	* @param str the name
	*/
	void SetName(CVString* str);
	void SetName(char* str);

	/**
	* @brief Get the UI's Name
	* @return the ui's name
	*/
	char* GetName(void);

	/**
	* @brief Set the UI's ID
	* @param nID the id
	*/
	void SetID(int nID);

	/**
	* @brief Get the UI's ID
	* @return the ui's id
	*/
	int GetID(void);

	/**
	* @brief Get the UI's x position
	* @return the ui's x position
	*/
	int GetX(void);

	/**
	* @brief Get the UI's y position
	* @return the ui's y position
	*/
	int GetY(void);

	/**
	* @brief Get the UI's width
	* @return the ui's width
	*/
	int GetWidth(void);

	/**
	* @brief Get the UI's height
	* @return the ui's height
	*/
	int GetHeight(void);

	/**
	* @brief Get the UI's rect
	* @return the ui's rect
	*/
	RECT* GetRect(void);

	/**
	* @brief Get the UI's rect
	* @param rcRect the ui's rect point
	*/
	void GetRect(RECT* rcRect);

	/**
	* @brief Flush UI
	*/
	void Flush(void);
	void Flush(int x1, int y1, int x2, int y2);

	/**
	* @brief Set developers Use which layer
	* @param flag the enum
	*/
	void SetLayerUse(int flag);

	/**
	* @brief Get the layer which developers use
	* @return the enum like ENUM_LAYERS_LAYER0
	*/
	int GetLayerUse(void);

public:

	/**
	* @brief Only for Overload, nothing to do, 
	* UI's Message Process
	* @param message the message id
	* @param sub_message the sub message id
	* @param wParam the first param
	* @param lParam the second param
	* @return no useless
	*/
	virtual int MessageProc(int message, int sub_message, long wParam, long lParam);

	/**
	* @brief Only for Overload, nothing to do, 
	* UI's Post Message Method
	* @param message the message id
	* @param sub_message the sub message id
	* @param wParam the first param
	* @param lParam the second param
	* @return no useless
	*/
	virtual int PostMessage(int message, int sub_message, long wParam, long lParam);

	/**
	* @brief Only for Overload, nothing to do, 
	* When key down, it will call this method
	* @param key_code the key code, look for vaf_keydef.h
	*/
	virtual void KeyDownHandle(int key_code);

	/**
	* @brief Only for Overload, nothing to do, 
	* When key up, it will call this method
	* @param key_code the key code, look for vaf_keydef.h
	*/
	virtual void KeyUpHandle(int key_code);

	/**
	* @brief Only for Overload, nothing to do, 
	* When touch down, it will call this method
	* @param nx the x position
	* @param ny the y position
	*/
	virtual void TouchDownHandle(int nx, int ny);

	/**
	* @brief Only for Overload, nothing to do, 
	* When touch up, it will call this method
	* @param nx the x position
	* @param ny the y position
	*/
	virtual void TouchUpHandle(int nx, int ny);

	/**
	* @brief Only for Overload, nothing to do, 
	* When touch move, it will call this method
	* @param nx the x position
	* @param ny the y position
	*/
	virtual void TouchMoveHandle(int nx, int ny);

	/**
	* @brief Only for Overload, nothing to do, 
	* Update the UI
	*/
	virtual void Update(void);

	/**
	* @brief Only for Overload, nothing to do, 
	* Paint the UI
	* @param handle the layers's handle
	* @param rcRect the ui's rect
	* @param nx the x position
	* @param ny the y position
	* @param nwidth the ui's width
	* @param nheight the ui's height
	*/
	virtual void Paint(int* handle, RECT* rcRect, int nx, int ny, int nwidth, int nheight);
public:
	
	/**
	* @brief the ui's handle
	*/
	long hBase;
	
	/**
	* @brief the ui's x
	*/
	int x;
	
	/**
	* @brief the ui's y
	*/
	int y;
	
	/**
	* @brief the ui's width
	*/
	int width;
	
	/**
	* @brief the ui's height
	*/
	int height;
	
	/**
	* @brief the ui's rect
	*/
	RECT rc;

	/**
	* @brief the ui's id
	*/
	int id;

	/**
	* @brief the ui's status, is key down
	*/
	bool is_key_down;

	/**
	* @brief the ui's status, is touch down
	*/
	bool is_touch_down;

	/**
	* @brief the ui's status, is moving
	*/
	bool is_moving;
	
private:
	/**
	* @brief the ui's name
	*/
	CVString name;

	/**
	* @brief save the layer enum which use
	*/
	int enum_layers;
};
class CTimer;
typedef struct UiTimerList
{
	CTimer * timer;
	int mil;
	int curMil;
	int id;
	UiTimerList* next;
}_UiTimerList;


class CTimer
{
public:
	CTimer();
	~CTimer();
	virtual void TimerCallback(int timer_id);
	void CreateTimer(int spanTime,int id);
	void DeleteTimer(int id);
};

#if 1
#include "CVArray.h"

class UiTimer
{
public:
	static void Destroy();
	static void Init();
	static bool RegisterTimer(CTimer* timer,int mil,int id);
	static bool UnRegisterTimer(CTimer* timer,int id);
protected:  
	static void Sys_Callback(int tid);
private:
	static CVArray* array;
	static int timerID;
};
#else
class UiTimer
{
public:
	static void Destroy();
	static void Init();
	static bool RegisterTimer(CTimer* timer,int mil,int id);
	static bool UnRegisterTimer(CTimer* timer,int id);
protected:  
	static void Sys_Callback(int tid);
private:
	static UiTimerList* pHead;
	static UiTimerList* pCur;
	
	static int timerID;
};
#endif

#endif
