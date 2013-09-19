#include "vaf_windowsmgr.h" 
#include "vaf_window.h"
#include "vaf_windowscore.h"
#include "CVString.h"
#include "CVWString.h"
#include "CVStringConvert.h"

VafArrayStack::VafArrayStack()
{
	//zero memory
	memset(windowArray,0,sizeof(long)*MAXWINDOWSNUM);
	index = 0;
}
VafArrayStack::~VafArrayStack()
{
	
}
void * VafArrayStack::Pop()
{ 
	long ret = NULL;
	if(index>0)
	{
		ret = windowArray[--index];
		windowArray[index] = NULL;
	}
	else
		return NULL;	
	return (void*)ret;
}
bool VafArrayStack::Push(void * data)
{
	if(index<MAXWINDOWSNUM)
	{
		windowArray[index++] = (long)data;
	}
	else
		return false;
	
	return true;
}
void* VafArrayStack::GetTop()
{
	return GetItem(index-1);
}
void* VafArrayStack::GetItem(int p)
{
	if(p>=index || p<0)
		return NULL;
	else
		return (void*)windowArray[p];
	return 0;
}
 
int VafArrayStack::GetCount()
{
	return (index);
}
bool VafArrayStack::Remove(int p)
{
	if(p>=index || p<0) 
		return FALSE;
	
	
	if(p == (index-1))//if its last then direct make it NULL and do not change the order
	{
		windowArray[p] = NULL;
	}
	else // if its not last change the order and make it NULL
	{	
		for(int i=p+1;i<index;i++)
		{
			windowArray[i-1] = windowArray[i];
		} 
		windowArray[index-1] = NULL;//make last to be NULL
	
	}
	index--;//desc the index because one of them has been removed
	return TRUE;
}

bool VafArrayStack::RemoveByHandle(void * data)
{
	int pos = -1;
	for(int i=0; i<index;i++)
	{
		if(windowArray[i]==(long)data)
		{
			pos = i;
			break;
		}
	}
	return Remove(pos);
}
//===========================================°³ÊÇ·Ö¸îÏß=======================================================

VafArrayStack * WindowsMgr::pStack = NULL;
VafArrayStack * WindowsMgr::pDesStack = NULL; 
int WindowsMgr::timerID=NULL;
// int WindowsMgr::finishpaintID=NULL;
int WindowsMgr::coreDebugTimerID=NULL;
// UiWindow* WindowsMgr::finishpainthWnd = NULL;

void WindowsMgr::Init(int enable_mem)
{
	pStack = new VafArrayStack();
	pDesStack = new VafArrayStack();
	timerID = vaf_create_timer(100,TimerCallBack);
	if(enable_mem == ENABLE_MEM)
	{
		coreDebugTimerID = vaf_create_timer(100,CoreDebugTimer);
	}
}
#define DBGSTRCOLOR V_RGB(255,0,255)
void WindowsMgr::CoreDebugTimer(int t)
{
	vaf_debug("CoreDebugTimer");
	malloc_stat_t * st = vm_get_malloc_stat();

	vaf_set_font(VM_SMALL_FONT);

	int* handle = vaf_get_layers_handle();
	vaf_active_layer(handle[1]);
	uchar* buf = vaf_get_layer_buf(handle[1]);
 	vaf_reset_clip();
	//vaf_clear_layer_bg(handle[1]);
 	vaf_fill_rect(buf, 0, 0, vaf_get_lcd_width()/3, vaf_get_character_height()*9, V_COLOR_WHITE, V_COLOR_WHITE);

	char tb[512];
	CVWString temp;
	CVString tString;
	sprintf(tb,"CL:%d",st->avail_heap_size);

	tString = tb;
	temp = CVStringConvert::DefaultToUCS2(tString);
	vaf_textout(buf,0,vaf_get_character_height()*0,temp.C_Str(),temp.Length(),DBGSTRCOLOR);

	sprintf(tb,"CU:%d",st->current);
	tString = tb;
	temp = CVStringConvert::DefaultToUCS2(tString);
	vaf_textout(buf,0,vaf_get_character_height()*1,temp.C_Str(),temp.Length(),DBGSTRCOLOR);
	
	sprintf(tb,"FT:%d",st->fail_times);
	tString = tb;
	temp = CVStringConvert::DefaultToUCS2(tString);
	vaf_textout(buf,0,vaf_get_character_height()*2,temp.C_Str(),temp.Length(),DBGSTRCOLOR);

	sprintf(tb,"MC:%d",st->malloc_count);
	tString = tb;
	temp = CVStringConvert::DefaultToUCS2(tString);
	vaf_textout(buf,0,vaf_get_character_height()*3,temp.C_Str(),temp.Length(),DBGSTRCOLOR);

	sprintf(tb,"FC:%d",st->free_count);
	tString = tb;
	temp = CVStringConvert::DefaultToUCS2(tString);
	vaf_textout(buf,0,vaf_get_character_height()*4,temp.C_Str(),temp.Length(),DBGSTRCOLOR);

	sprintf(tb,"MM:%d",st->peak);
	tString = tb;
	temp = CVStringConvert::DefaultToUCS2(tString);
	vaf_textout(buf,0,vaf_get_character_height()*5,temp.C_Str(),temp.Length(),DBGSTRCOLOR);

	sprintf(tb,"%s",vm_get_imsi());
	tString = tb;
	temp = CVStringConvert::DefaultToUCS2(tString);
	vaf_textout(buf,0,vaf_get_character_height()*6,temp.C_Str(),temp.Length(),DBGSTRCOLOR);

	if(pStack)
	{
		sprintf(tb,"CAW:%d",pStack->GetCount());
		tString = tb;
		temp = CVStringConvert::DefaultToUCS2(tString);
		vaf_textout(buf,0,vaf_get_character_height()*7,temp.C_Str(),temp.Length(),DBGSTRCOLOR);
	}

	if(pDesStack)
	{
		sprintf(tb,"CDW:%d",pDesStack->GetCount());
		tString = tb;
		temp = CVStringConvert::DefaultToUCS2(tString);
		vaf_textout(buf,0,vaf_get_character_height()*8,temp.C_Str(),temp.Length(),DBGSTRCOLOR);
	}

	vaf_flush_layer(handle,2);
	
}

void WindowsMgr::TimerCallBack(int k)
{
/*
	if(k == finishpaintID)
	{
		vaf_delete_timer(finishpaintID);
		finishpaintID = NULL;
		if(finishpainthWnd)
		{
			finishpainthWnd->FinishPaint();
			finishpainthWnd = NULL;
		}
		return;
	}
*/
	DestroyWindows();
}

void WindowsMgr::Free()
{
	int sCount = pStack->GetCount(); 
	if(sCount == 0)
	{
		vaf_debug("Begin Delete pDes");
		delete pDesStack;
		vaf_debug("Begin Delete pStack");
		delete pStack;
		vaf_debug("Begin Show Memory State"); 
		malloc_stat_t* st = vm_get_malloc_stat();
		vaf_debug("CURUSE:%d, MAX FAIL:%d",st->current,st->fail_times);
		vaf_delete_timer(timerID);

		if(coreDebugTimerID != NULL)
		{
			vaf_delete_timer(coreDebugTimerID);
		}

		vaf_winmgr_free();
		{
			extern void (*vaf_app_unload)(void);
			if(vaf_app_unload)vaf_app_unload();
		}
		vaf_exit_app();
	} 
} 
bool WindowsMgr::SetTopWindow(long wnd)
{ 
	pStack->RemoveByHandle((void*)wnd);
	pStack->Push((UiWindow*)wnd);
	return TRUE;
}
int WindowsMgr::MessageProcss(long hWnd,int message, int sub_message, long wParam, long lParam)
{  
	UiWindow * wnd = (UiWindow*)hWnd;
	UiWindow * hTop = (UiWindow*)pStack->GetTop();
	switch(message)
	{
	case MSG_SYS_INACTIVE:
		{ 
			if(hTop)
				hTop->PostMessage(MSG_CORE_INTERRUPT, sub_message, wParam, lParam);
		}		
		break;
	case MSG_WIN_CREATE:
		{
			if(hWnd)
			{
				AddWindow(hWnd); 
			}
		}
		break;
	case MSG_WIN_SHOW:
		{ 
			if(hWnd)
			{
				SetNoneTopWindow();
				((UiWindow*)hWnd)->is_top_window=TRUE;
				((UiWindow*)hWnd)->PostUserMessage(MSG_WIN_SHOW,NULL,NULL,NULL);
				((UiWindow*)hWnd)->Update(); 
				SetTopWindow(hWnd);
			}
		}
		break;
	case MSG_WIN_DELAYDESTROY:
		{
			if(hWnd)
			{
				UiWindow* ddesWin = (UiWindow*)hWnd;
				if(ddesWin)pStack->RemoveByHandle(ddesWin);
				UiWindow* dtopWin = (UiWindow*)pStack->GetTop();
				if(dtopWin)dtopWin->is_top_window = TRUE;
				if(ddesWin)pDesStack->Push(ddesWin); 
			}
		}
		break;
	case MSG_WIN_DESTROY:
		{  
			if(hWnd)
			{			 
				UiWindow* desWin = wnd;
				if(desWin)
				{
					desWin->PostUserMessage(MSG_WIN_NOTIFY_DESTROY,NULL,NULL,NULL);
					pStack->RemoveByHandle(desWin); 
				} 
				if(lParam == ID_BACK)
				{
					UiWindow* dWin = (UiWindow*)pStack->GetTop();
					if(dWin)
					{
						dWin->PostUserMessage(MSG_WIN_NOTIFY_BACK,NULL,NULL,NULL);
						dWin->is_top_window=TRUE;
						dWin->Update();
					} 
					//UiWindow* win = (UiWindow*)desWin;
					//if(win)
					//{
					//	win->OnDispose();
					//}
					pDesStack->Push(desWin);
				}
				else if(lParam == ID_NULL) 
				{ 
					//UiWindow* win = (UiWindow*)hWnd;
					//if(win)
					//{
					//	win->OnDispose();
					//}
					if(hWnd)
						pDesStack->Push((UiWindow*)hWnd);
				}
			} 
		}
		break;
	case MSG_CORE_REFRESH:
		{
			int wCount = pStack ->GetCount();
			int pos = 0;
			for(int i=wCount;i>=0;i--)
			{
				UiWindow* pw = (UiWindow*)pStack->GetItem(i);
				if(pw)
				{
					if(pw->GetWidth()>=vaf_get_lcd_width() && pw->GetHeight()>=vaf_get_lcd_height()
						&& pw->GetX()==0 && pw->GetY()==0)
					{
						vaf_debug("[%s] is full screen window!!!!!!!Flush Next",pw->GetName());
						pos = i;
						break;
					}
					else
					{
						vaf_debug("[%s] Not full screen window",pw->GetName());
					}
				}
			}
			UiWindow* tw = NULL;
			for(int k=pos;k<wCount;k++)
			{
				UiWindow* tw = (UiWindow*)pStack->GetItem(k);
				if(tw)
				{
					bool topwndState = tw->is_top_window;
					tw->is_top_window = TRUE;
					vaf_debug("[%s] tw->Paint(vaf_get_layers_handle(), tw->GetRect());",tw->GetName());
					tw->Update();
					vaf_debug("[%s] tw->PaintControls(vaf_get_layers_handle());",tw->GetName());
					tw->is_top_window = topwndState;
				}
			}  
			UiWindow* pTopWindow =(UiWindow*) pStack->GetTop(); 
			vaf_debug("vaf_flush_layer(vaf_get_layers_handle(), 2);");
			if(pTopWindow)
				pTopWindow->PostUserMessage(MSG_WIN_NOTIFY_REFRESH,NULL,NULL,NULL);
		}
		break;
	case MSG_WIN_PAINT:
		{
			if(wnd)
			{
				wnd->Paint(vaf_get_layers_handle(), wnd->GetRect());
				wnd->PaintControls(vaf_get_layers_handle());
				if(sub_message != MSG_WIN_NO_UPDATE)
				{
					wnd->Flush();
				}
				//finishpainthWnd = wnd;
				//finishpaintID= vaf_create_timer(100,TimerCallBack);
			} 
		}
		break;
	case MSG_KEY_EINT: 
	case MSG_TOUCH_EINT:
		{
			UiWindow * pIO = (UiWindow*)pStack->GetTop();
			if(pIO)
				pIO->PostMessage(message, sub_message, wParam, lParam);
		} 
		break;
	default:
		{
			if(wnd && !wnd->isDestroy)
				wnd->PostUserMessage(message,sub_message,wParam,lParam);
		}
		break;
	}
	
	return 0;
}

void WindowsMgr::SetNoneTopWindow()
{
	int count = pStack->GetCount();
	for(int i=0;i<count;i++)
	{		
		if(((UiWindow*)pStack->GetItem(i)))
			((UiWindow*)pStack->GetItem(i))->is_top_window = FALSE;
	}
}

void WindowsMgr::ExitProgram()
{
//	vaf_delete_timer(timerID);
	int count = pStack->GetCount();
	while(count)
	{ 
		UiWindow* ui = (UiWindow*)pStack->Pop();
		if(!ui)
			break;
//		while(ui->can_release == FALSE);
		if(ui)
		{
			ui->Destroy(ID_NULL);
		}
		count = pStack->GetCount();
	}
//	DestroyWindows(); 
	{
		extern void (*vaf_app_unload)(void);
		if(vaf_app_unload)vaf_app_unload();
	}
//	vaf_exit_app();
}

long WindowsMgr::FindTopWindow()
{ 
	return (long)pStack->GetTop();
}

long WindowsMgr::FindWindowByID(int id)
{
	if(pStack==NULL)
		return 0;
	int count = pStack->GetCount();
	for(int i=0;i<count;i++)
	{		
		UiWindow* tempWnd = (UiWindow*)pStack->GetItem(i);
		if(tempWnd)
		{
			if(tempWnd->GetID() == id)
				return tempWnd->hBase;
		}
	}

	return 0;
}

bool WindowsMgr::DestroyWindows()
{
	//vaf_debug("fun:DestroyWindows");
	while(pDesStack->GetCount()!=0)
	{
		//vaf_debug("Enter While");
		UiWindow * p = (UiWindow*)pDesStack->GetTop();
		if(p)
		{	
			vaf_debug("Get Wnd:%02X",p);
			vaf_debug("Get Wnd:%s",p->GetName());
			if(p && p->isDestroy && p->is_top_window==FALSE && p->can_release)
			{
				vaf_debug("RemoveByHandle");
				bool tmpBl = pDesStack->RemoveByHandle(p);
				vaf_debug("RemoveByHandle:%d",tmpBl);
				vaf_debug("start delete p"); 
				p->OnDispose();
				delete p;
				p = NULL;
				vaf_debug("delete p finish");
			} 
			else
			{
				vaf_debug("windows clear finish");
				break;
			}
		}
		else
		{
			break;
		}
	}
	//vaf_debug("fun:DestroyWindows Leave"); 
// 	if(timerID)
// 	{
// 		 vaf_delete_timer(timerID);
// 		 timerID = NULL;
// 	}
	Free();
	//vaf_debug("fun:DestroyWindows Free Finish Exit"); 
	return 0; 
}

bool WindowsMgr::DeleteWindow(long hWnd)
{ 
	pStack->RemoveByHandle((UiWindow*)hWnd);

	UiWindow * pWnd = (UiWindow*)pStack->GetTop();
	if(pWnd)
	{
		pWnd->is_top_window=TRUE;
		pWnd->Update();
	}
	return FALSE; 
}

bool WindowsMgr::AddWindow(long wnd)
{  
	UiWindow* window = (UiWindow*)wnd;
	UiWindow* topWin = (UiWindow*)pStack->GetTop();
	if(topWin)
		topWin->is_top_window = FALSE;
	if(window)
		window->is_top_window = TRUE;
	pStack->Push(window);
	return TRUE;
}

long WindowsMgr::GetTopWindow()
{
	return (long)pStack->GetTop();
}
