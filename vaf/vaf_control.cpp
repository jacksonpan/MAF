#include "vaf_control.h"
#include "vaf_window.h"

UiControl::UiControl(void)
{
	hBase = (long)this;
	enable_control = true;
	enable_keyhandle = true;
	enable_overall_keyhandle  = false;
	enable_touchhandle  = true;
	enable_overall_touchhandle  = false;
	enable_focus = false;
	is_focused = false;
	is_visible = true;
	enable_postid = false;
	where_hwnd = NULL;
	is_lost_focus = FALSE;

	bg_color = V_COLOR_WHITE;
}

UiControl::~UiControl(void)
{

}

void UiControl::IsEnableKeyHandle(bool flag)
{
	enable_keyhandle = flag;
}

bool UiControl::GetIsEnableKeyHandle(void)
{
	return enable_keyhandle;
}

void UiControl::IsEnableOverallKeyHandle(bool flag)
{
	enable_overall_keyhandle = flag;
}

bool UiControl::GetIsEnableOverallKeyHandle(void)
{
	return enable_overall_keyhandle;
}

void UiControl::IsEnableTouchHandle(bool flag)
{
	enable_touchhandle = flag;
}

bool UiControl::GetIsEnableTouchHandle(void)
{
	return enable_touchhandle;
}

void UiControl::IsEnableOverallTouchHandle(bool flag)
{
	enable_overall_touchhandle = flag;
}

bool UiControl::GetIsEnableOverallTouchHandle(void)
{
	return enable_overall_touchhandle;
}

void UiControl::IsEnableFocus(bool flag)
{
	enable_focus = flag;
}

bool UiControl::GetIsEnableFocus(void)
{
	return enable_focus;
}

void UiControl::IsFocused(bool flag)
{
	is_focused = flag;
}

bool UiControl::GetIsFocused(void)
{
	return is_focused;
}

void UiControl::IsVisible(bool flag)
{
	is_visible = flag;
}

bool UiControl::GetIsVisible(void)
{
	return is_visible;
}

void UiControl::IsEnableControl(bool flag)
{
	enable_control = flag;
}

bool UiControl::GetIsEnableControl(void)
{
	return enable_control;
}

void UiControl::IsEnablePostID(bool flag)
{
	enable_postid = flag;
}

bool UiControl::GetIsEnablePostID(void)
{
	return enable_postid;
}

void UiControl::SetCurhWnd(long lhWnd)
{
	where_hwnd = lhWnd;
}
void UiControl::SetIsLostFocus(bool flag)
{
	is_lost_focus = flag;
}

long UiControl::GetCurhWnd(void)
{
	return where_hwnd;
}

void UiControl::SetBackgroundColor(ushort color)
{
	bg_color = color;
}

ushort UiControl::GetBackgroundColor(void)
{
	return bg_color;
}

int UiControl::PostWinMessage(int message, int sub_message, long wParam, long lParam)
{
	if(where_hwnd)
	{
		UiWindow* pWnd = (UiWindow*)where_hwnd;
		if(pWnd)
		{
			return pWnd->PostUserMessage(message, sub_message, wParam, lParam);
		}
	}
	return NULL;
}

int UiControl::MessageProc(int message, int sub_message, long wParam, long lParam)
{
	switch(message)
	{
	case MSG_KEY_EINT:
		switch(sub_message)
		{
		case MSG_KEY_DOWN:
			is_key_down = true;
			KeyDownHandle(wParam);
			if(GetIsEnablePostID() == true && GetIsFocused() == true)
			{
				PostWinMessage(MSG_CTR_ID, MSG_KEY_DOWN, wParam, id);
			}
			else
			if(GetIsEnablePostID() == true && GetIsEnableOverallKeyHandle() == true)
			{
				PostWinMessage(MSG_CTR_ID, MSG_KEY_DOWN, wParam, id);
			}
			break;
		case MSG_KEY_UP:
			if(is_key_down == true)
			{
				is_key_down = false;
				KeyUpHandle(wParam);
				if(GetIsEnablePostID() == true && GetIsFocused() == true)
				{
					PostWinMessage(MSG_CTR_ID, MSG_KEY_UP, wParam, id);
				}
				else
				if(GetIsEnablePostID() == true && GetIsEnableOverallKeyHandle() == true)
				{
					PostWinMessage(MSG_CTR_ID, MSG_KEY_UP, wParam, id);
				}
			}
			break;
		}
		break;
	case MSG_TOUCH_EINT:
		switch(sub_message)
		{
		case MSG_TOUCH_DOWN:
			is_touch_down = true;
			TouchDownHandle(wParam, lParam);
			if(GetIsEnablePostID() == true && GET_IS_IN_THE_RECT(wParam, lParam, rc.left, rc.top, rc.right, rc.bottom) == true)
			{
				PostWinMessage(MSG_CTR_ID, MSG_TOUCH_DOWN, 0, id);
			}
			break;
		case MSG_TOUCH_MOVE:
			if(is_touch_down == true)
			{
				is_moving = true;
				TouchMoveHandle(wParam, lParam);
				if(GetIsEnablePostID() == true && GET_IS_IN_THE_RECT(wParam, lParam, rc.left, rc.top, rc.right, rc.bottom) == true)
				{
					PostWinMessage(MSG_CTR_ID, MSG_TOUCH_MOVE, 0, id);
				}
			}
			break;
		case MSG_TOUCH_UP:
			if(is_touch_down == true)
			{
				is_moving = false;
				is_touch_down = false;
				TouchUpHandle(wParam, lParam);
				if(GetIsEnablePostID() == true && GET_IS_IN_THE_RECT(wParam, lParam, rc.left, rc.top, rc.right, rc.bottom) == true)
				{
					PostWinMessage(MSG_CTR_ID, MSG_TOUCH_UP, 0, id);
				}
			}
			break;
		}
		break;
	case MSG_CTR_PAINT:
		Paint(vaf_get_layers_handle(), &rc, x, y, width, height);
		if(GetIsFocused() == TRUE && GetIsEnableFocus() == TRUE)
		{
			PaintFocus(vaf_get_layers_handle(), &rc, x, y, width, height);
		}
#if 1
		if(sub_message == MSG_CTR_UPDATE_RECT)
		{
			Flush(rc.left, rc.top, rc.right, rc.bottom);
		}
		else if(sub_message != MSG_CTR_NO_UPDATE && sub_message != MSG_CTR_UPDATE_RECT)
		{
			Flush();
		}
#else
		if(sub_message != MSG_CTR_NO_UPDATE)
		{
			Flush();
		}
#endif
		break;
	case MSG_CTR_FOCUS_CHANGE:
		switch(sub_message)
		{
		case MSG_CTR_FOCUS_CHANGE_ME:
			IsFocused(TRUE);
			Update();
			break;
		case MSG_CTR_FOCUS_CHANGE_DOWN:
		case MSG_CTR_FOCUS_CHANGE_UP:
		case MSG_CTR_FOCUS_CHANGE_TOUCH:
			{
				long last_focus = wParam;
				if(last_focus != 0)
				{
					UiControl* pLastUiWin = (UiControl*)last_focus;
					pLastUiWin->IsFocused(FALSE);
					pLastUiWin->UpdateEx(UPDATE_NONE);
				}
				IsFocused(TRUE);
				Update();
			}
			break;
		}
		break;
	}
	return 0;
}

void UiControl::Update(void)
{
	if(GetIsVisible() == true)
	{
		PostMessage(MSG_CTR_PAINT, 0, 0 , 0);
	}
}

void UiControl::UpdateEx(int flag)
{
	if(GetIsVisible() == true)
	{
		if(flag == UPDATE_FLUSH)
		{
			PostMessage(MSG_CTR_PAINT, 0, 0 , 0);
		}
		else if(flag == UPDATE_RECT)
		{
			PostMessage(MSG_CTR_PAINT, MSG_CTR_UPDATE_RECT, 0, 0);
		}
		else
		{
			PostMessage(MSG_CTR_PAINT, MSG_CTR_NO_UPDATE, 0 , 0);
		}
	}
}

void UiControl::Paint(int* handle, RECT* rcRect, int nx, int ny, int nwidth, int nheight)
{
}

void UiControl::PaintFocus(int* handle, RECT* rcRect, int nx, int ny, int nwidth, int nheight)
{
	unsigned char* buf = NULL;
	vaf_active_layer(handle[1]);
	buf = vaf_get_layer_buf(handle[1]);
	vaf_set_clip(rcRect->left, rcRect->top, rcRect->right, rcRect->bottom);
	vaf_rect(buf, x, y, width, height, V_COLOR_FOCUS);
	vaf_rect(buf, x+1, y+1, width-2, height-2, V_COLOR_FOCUS);
}
