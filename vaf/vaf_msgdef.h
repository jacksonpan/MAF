//////////////////////////////////////////////////////////////////////////
//All message will defined here
//All custom message MUST start from MSG_USR_START
//////////////////////////////////////////////////////////////////////////
#ifndef __vaf_msgdef_h__
#define __vaf_msgdef_h__

#define MSG_SYS_ACTIVE					VM_MSG_ACTIVE
#define MSG_SYS_PAINT					VM_MSG_PAINT
#define MSG_SYS_HIDE					VM_MSG_HIDE
#define MSG_SYS_INACTIVE				VM_MSG_INACTIVE
#define MSG_SYS_CREATE					VM_MSG_CREATE
#define MSG_SYS_QUIT					VM_MSG_QUIT

#define MSG_KEY_EINT					0x00000010
#define MSG_KEY_DOWN					0x00000011
#define MSG_KEY_UP						0x00000012

#define MSG_TOUCH_EINT					0x00000020
#define MSG_TOUCH_DOWN					0x00000021
#define MSG_TOUCH_MOVE					0x00000022
#define MSG_TOUCH_UP					0x00000023

//////////////////////////////////////////////////////////////////////////
// Core Message
//////////////////////////////////////////////////////////////////////////
#define MSG_CORE						0x01000000
#define MSG_CORE_INTERRUPT				MSG_SYS_QUIT
#define MSG_CORE_REFRESH				MSG_CORE+0x00000100
//////////////////////////////////////////////////////////////////////////
// WINDOWS MESSAGE
//////////////////////////////////////////////////////////////////////////
#define MSG_WIN							0x2000030
#define MSG_WIN_CREATE					MSG_WIN+0x00000030 //创建窗体的消息，在NEW UIWINDOW
#define MSG_WIN_PAINT					MSG_WIN+0x00000031 //绘制消息
#define MSG_WIN_HIDE					MSG_WIN+0x00000032 //隐藏消息
#define MSG_WIN_DESTROY					MSG_WIN+0x00000033 //销毁窗体消息
#define MSG_WIN_NO_UPDATE				MSG_WIN+0x00000034 //不立即更新层，重绘窗体
#define MSG_WIN_SHOW					MSG_WIN+0x00000035 //UIWINDOW.SHOW()函数出发的消息
#define MSG_WIN_DELAYDESTROY			MSG_WIN+0x00000036 //延迟释放窗体
#define MSG_WIN_NOTIFY_DESTROY			MSG_WIN+0x00000037 //窗体销毁的通知
#define MSG_WIN_NOTIFY_BACK				MSG_WIN+0x00000038 //回到窗体时的通知
#define MSG_WIN_NOTIFY_REFRESH			MSG_WIN+0x00000039 //中断时回到窗体时的通知 

//////////////////////////////////////////////////////////////////////////
// APPLICATION MESSAGE
////////////////////////////////////////////////////////////////////////// 
#define MSG_APP							0x3000000
#define MSG_CTR_PAINT					MSG_APP+0x00000040
#define MSG_CTR_FOCUS_CHANGE			MSG_APP+0x00000041
#define MSG_CTR_FOCUS_CHANGE_DOWN		MSG_APP+0x00000141
#define MSG_CTR_FOCUS_CHANGE_UP			MSG_APP+0x00000142
#define MSG_CTR_FOCUS_CHANGE_TOUCH		MSG_APP+0x00000143
#define MSG_CTR_FOCUS_CHANGE_ME			MSG_APP+0x00000144
#define MSG_CTR_ID						MSG_APP+0x00000042
#define MSG_CTR_NO_UPDATE				MSG_APP+0x00000043 
#define MSG_CTR_UPDATE_RECT				MSG_APP+0x00000044

#define MSG_CONTROL						0x4000000
//////////////////////////////////////////////////////////////////////////
// LISTBOX MESSAGE
//////////////////////////////////////////////////////////////////////////
#define MSG_LISTBOX						MSG_CONTROL+0x00002000//标记 无用
#define MSG_LISTBOX_SCROLL				MSG_CONTROL+0x00002001//拖动事件
#define MSG_LISTBOX_TOUCHDOWN			MSG_CONTROL+0x00002002//MOVE DOWN
#define MSG_LISTBOX_TOUCHUP				MSG_CONTROL+0x00002003//MOVE UP
#define MSG_LISTBOX_TOUCHMOVE			MSG_CONTROL+0x00002004//MOVE
#define MSG_LISTBOX_KEYDOWN				MSG_CONTROL+0x00002005//KEY DOWN
#define MSG_LISTBOX_KEYUP				MSG_CONTROL+0x00002006//KEY UP
#define MSG_LISTBOX_CLICK				MSG_CONTROL+0x00002007//单击事件
#define MSG_LISTBOX_CLICK				MSG_CONTROL+0x00002007

//////////////////////////////////////////////////////////////////////////
// TABBAR MESSAGE
//////////////////////////////////////////////////////////////////////////
#define MSG_TABBAR						MSG_CONTROL+0x00004001
#define MSG_TABBAR_ONSELECT             MSG_CONTROL+0x00004002 //wParam =[Control ID]|lParam = [Item ID]

//////////////////////////////////////////////////////////////////////////
// RICHLABEL MESSAGE
//////////////////////////////////////////////////////////////////////////
#define MSG_RICHLABEL					MSG_CONTROL+0x00005000
#define MSG_RICHLABEL_SCROLL			MSG_CONTROL+0x00005001 //wParam =[Control ID]   lParam = [Value]
#define MSG_RICHLABEL_COMPUTERECT		MSG_CONTROL+0x00005002 //wParam =[Control ID]   lParam = [Context Height]
#define MSG_RICHLABEL_SCROLLMAX			MSG_CONTROL+0x00005003 //wParam =[Control ID]   lParam = [Scrollbar Max Value] 

//////////////////////////////////////////////////////////////////////////
// Matrix MESSAGE
//////////////////////////////////////////////////////////////////////////
#define MSG_MATRIX						MSG_CONTROL+0x00003001

//////////////////////////////////////////////////////////////////////////
// Scroolbar MESSAGE
//////////////////////////////////////////////////////////////////////////
#define MSG_SCROOLTEXT					MSG_CONTROL+0x00006001
#define MSG_SCROOLUPDATE				MSG_CONTROL+0x00006002 


//////////////////////////////////////////////////////////////////////////
// StaticText MESSAGE
//////////////////////////////////////////////////////////////////////////
#define MSG_STATICTEXT_SCROLL			MSG_CONTROL+0x00007001 					
#define MSG_STATICTEXT				    MSG_CONTROL+0x00007002
//////////////////////////////////////////////////////////////////////////
// Other Message
//////////////////////////////////////////////////////////////////////////
#define MSG_USR_START					0x5001000

#define MSG_MESSAGEBOX					MSG_USR_START + 1

#endif 
 