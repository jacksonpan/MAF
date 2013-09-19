#include "vaf_window.h" 
#include "vaf_windowsMgr.h"

class WindowsMgr;
UiWindow::UiWindow(void)
{
	hBase = (long)this;
	is_top_window = false;
	is_created = false;
	parent_hwnd = NULL;
	bg_color = V_COLOR_WHITE;
	enable_bg_color = false;

	CtrManager = new UiCtrManager();
	CtrManager->SetParenthWnd(hBase);

	can_release = TRUE;

	isDestroy=FALSE;

	//WindowsMgr::AddWindow(hBase);
}

UiWindow::~UiWindow(void)
{
	delete CtrManager;
}
void UiWindow::OnDispose(void)
{

}
bool UiWindow::GetWinIsCreated(void)
{
	return is_created;
}

long UiWindow::GetParenthWnd(void)
{
	return parent_hwnd;
}

int UiWindow::OnInitWnd(void)
{
	return 0;
}

void UiWindow::Create(int xPos, int yPos, int nwidth, int nheight, long nhwndParent, int nID)
{
	if(hBase == NULL)
	{
		vaf_exit_app();
		return;
	}

	if(GetWinIsCreated() == TRUE)
	{
		return;
	}
	
	x = xPos;
	y = yPos;
	width = nwidth;
	height = nheight;
	rc.left = x;
	rc.top = y;
	rc.right = x + width;
	rc.bottom = y + height;
	parent_hwnd = nhwndParent;
	id = nID;

	PostMessage(MSG_WIN_CREATE, 0, 0, 0);
	is_created = true;
}

void UiWindow::Show(bool flag)
{
	if(flag == true)
	{
		WindowsMgr::MessageProcss(hBase,MSG_WIN_SHOW, 0, 0, 0);
	}
}

void UiWindow::Update(void)
{
	PostMessage(MSG_WIN_PAINT, 0, 0 , 0);
}

void UiWindow::UpdateEx(int flag)
{
	if(flag == UPDATE_FLUSH)
	{
		PostMessage(MSG_WIN_PAINT, 0, 0 , 0);
	}
	else
	{
		PostMessage(MSG_WIN_PAINT, MSG_WIN_NO_UPDATE, 0 , 0);
	}
}

void UiWindow::Hide(void)
{
	PostMessage(MSG_WIN_HIDE, 0, 0, 0);
}

void UiWindow::Destroy(int flag)
{
	is_top_window = FALSE;
	isDestroy = TRUE;
	PostMessage(MSG_WIN_DESTROY, 0, 0, flag);
}

void UiWindow::SetBackgroundColor(ushort color)
{
	bg_color = color;
}

ushort UiWindow::GetBackgroundColor(void)
{
	return bg_color;
}

void UiWindow::IsEnableBackgroundColor(bool flag)
{
	enable_bg_color = flag;
}

bool UiWindow::GetIsEnableBackgroundColor(void)
{
	return enable_bg_color;
}

void UiWindow::IsEnableAutoChangeFocus(bool flag)
{
	CtrManager->IsEnableAutoChangeFocus(flag);
}

bool UiWindow::GetIsEnableAutoChangeFocus(void)
{
	return CtrManager->GetIsEnableAutoChangeFocus();
}

void UiWindow::DelayDestroy()
{
	this->is_top_window = FALSE;
	this->isDestroy = TRUE;
	PostMessage(MSG_WIN_DELAYDESTROY,0,0,0);
}
int UiWindow::MessageProc(int message, int sub_message, long wParam, long lParam)
{
	can_release = FALSE;
	switch(message)
	{
	case MSG_WIN_CREATE: 
		OnInitWnd();
		WindowsMgr::MessageProcss(hBase,MSG_WIN_CREATE, 0, hBase, 0);  
		break;
	case MSG_WIN_PAINT:
		WindowsMgr::MessageProcss(hBase,MSG_WIN_PAINT, 0, hBase, 0); 
		break;
	case MSG_WIN_HIDE:
		WindowsMgr::MessageProcss(hBase,MSG_WIN_HIDE, 0, hBase, 0);
		break;
	case MSG_WIN_DESTROY:
		WindowsMgr::MessageProcss(hBase,MSG_WIN_DESTROY,0,0,lParam);   
		break;
	case MSG_WIN_DELAYDESTROY:
		{
			WindowsMgr::MessageProcss(hBase,MSG_WIN_DELAYDESTROY,0,0,0);   
		}
		break;
	case MSG_KEY_EINT:
	case MSG_TOUCH_EINT:
		{  
			if(isDestroy == FALSE)
			{	
				CtrManager->PostMessage(message, sub_message, wParam, lParam);
				UsrMessageProcInner(message, sub_message, wParam, lParam); 
			}
			else
			{
				vaf_debug("Windows has been deleted Ctrl Message Will not be passed");
			}
		}
		break;
	case MSG_CTR_ID:
		{
			if(!isDestroy)
				UsrMessageProcInner(message, sub_message, wParam, lParam);
		}
		break;
	default:
		{
			if(message > MSG_USR_START)
			{
				if(!isDestroy)
					UsrMessageProcInner(message, sub_message, wParam, lParam);
			}

		}
		break;
	}
	can_release = TRUE;
	return 0;
}
bool UiWindow::GetIsDestroy()
{	
	return isDestroy;
}

int UiWindow::UsrMessageProcInner(int message, int sub_message, long wParam, long lParam)
{
	can_release = FALSE;
	int ret = UsrMessageProc(message,sub_message,wParam,lParam);
	can_release = TRUE;
	return ret;
}
int UiWindow::UsrMessageProc(int message, int sub_message, long wParam, long lParam)
{
	return 0;
}
long UiWindow::PostUserMessage(int message,int sub_message,long wP,long lP)
{
	return UsrMessageProcInner(message,sub_message,wP,lP);
}

void UiWindow::Paint(int* handle, RECT* rcRect)
{
	unsigned char* buf = NULL;
#if 0//def WIN32
	vaf_active_layer(handle[0]);
	buf = vaf_get_layer_buf(handle[0]);
	vaf_reset_clip();
	vaf_fill_rect(buf, x, y, width, height, V_COLOR_WHITE, V_COLOR_WHITE);
	
	vaf_active_layer(handle[1]);
	buf = vaf_get_layer_buf(handle[1]);
	vaf_reset_clip();
	vaf_fill_rect(buf, x, y, width, height, V_COLOR_WHITE, V_COLOR_WHITE);

	if(GetIsEnableBackgroundColor() == true)
	{
		buf = vaf_get_layer_buf(handle[0]);
		vaf_fill_rect(buf, x, y, width, height, bg_color, bg_color);
		buf = vaf_get_layer_buf(handle[1]);
		vaf_fill_rect(buf, x, y, width, height, bg_color, bg_color);
	}
#else
	vaf_active_layer(handle[0]);
	vaf_reset_clip();
	vaf_clear_layer_bg(handle[0]);
	vaf_active_layer(handle[1]);
	vaf_reset_clip();
	vaf_clear_layer_bg(handle[1]);

	if(GetIsEnableBackgroundColor() == true)
	{
//		vaf_debug("%s paint window background color", GetName());
//		vaf_debug("color: %d", bg_color);
		buf = vaf_get_layer_buf(handle[0]);
		vaf_fill_rect(buf, x, y, width, height, bg_color, bg_color);
 		buf = vaf_get_layer_buf(handle[1]);
		vaf_fill_rect(buf, x, y, width, height, bg_color, bg_color);
//		vaf_debug("%d %d %d %d", x, y, width, height);
	}
#endif
}

void UiWindow::PaintControls(int* handle)
{
	CVArray* hCtrl_vector = CtrManager->GetControlList();
	
	if(hCtrl_vector == NULL)
	{
		return;
	}
	
	if(hCtrl_vector)
	{
		for(int i=0;i<hCtrl_vector->GetCount();i++)
		{
			UiControl* pCtrl = (UiControl*)hCtrl_vector->objectAtIndex(i);
			
			if(GetIsTopWindow() == false)
			{
				return;
			}
			
			if(pCtrl)
			{
				if(pCtrl->GetIsVisible() == true)
				{
					pCtrl->PostMessage(MSG_CTR_PAINT, MSG_CTR_NO_UPDATE, 0 , 0);
				}
			}
		}
	}
}

void UiWindow::AddUiControl(UiControl* control)
{
	if(control)
	{
		if(control->hBase)
		{
			control->where_hwnd = hBase;
			CtrManager->AddUIControl(control);
		}
	}
}

bool UiWindow::GetIsTopWindow(void)
{
	return is_top_window;
}

int UiWindow::GetWinFocusedID(void)
{
	return this->CtrManager->GetFocusedID();
}

// void UiWindow::FinishPaint( void )
// {
// 	
// }
