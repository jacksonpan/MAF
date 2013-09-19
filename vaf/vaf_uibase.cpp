#include "vaf_uibase.h"

#if 1
CVArray* UiTimer::array;
int UiTimer::timerID;
#define TIMER_SPANTIME 50
void UiTimer::Init()
{
	array = new CVArray();
	timerID=vaf_create_timer(TIMER_SPANTIME,Sys_Callback);
}
void UiTimer::Destroy()
{
	if(timerID>=0)
	{
		vaf_delete_timer(timerID);
	}
	for(int i=0;i<array->GetCount();i++)
	{
		_UiTimerList* timerStruct = (_UiTimerList*)array->objectAtIndex(i);
		if(timerStruct)
		{
			delete timerStruct;
			timerStruct = NULL;
		}
	}
	if(array)
	{
		delete array;
		array = NULL;
	}
}

bool UiTimer::RegisterTimer(CTimer* timer,int mil,int id)
{
	for(int i=0;i<array->GetCount();i++)
	{
		_UiTimerList* timerStruct = (_UiTimerList*)array->objectAtIndex(i);
		if(timerStruct->timer == timer && timerStruct->id == id)
		{
			return false;
		}
	}

	_UiTimerList* timerStruct = new _UiTimerList();
	timerStruct->timer = timer;
	timerStruct->id = id;
	timerStruct->mil = mil;
	timerStruct->curMil = 0;
	timerStruct->next = NULL;
	array->addObject(timerStruct);

	return true;
}

bool UiTimer::UnRegisterTimer(CTimer* timer,int id)
{
	for(int i=0;i<array->GetCount();i++)
	{
		_UiTimerList* timerStruct = (_UiTimerList*)array->objectAtIndex(i);
		if(timerStruct->timer == timer && timerStruct->id == id)
		{
			array->removeObjectAtIndex(i);
			delete timerStruct;
			timerStruct = NULL;
			return true;
		}
	}
	return false;
}

void UiTimer::Sys_Callback(int tid)
{
	for(int i=0;i<array->GetCount();i++)
	{
		_UiTimerList* timerStruct = (_UiTimerList*)array->objectAtIndex(i);
		timerStruct->curMil += TIMER_SPANTIME;
		if(timerStruct->timer && timerStruct->curMil >= timerStruct->mil)
		{
			timerStruct->timer->TimerCallback(timerStruct->id);
			timerStruct->curMil = 0;
		}
	}
}

#else
UiTimerList* UiTimer::pCur;
UiTimerList* UiTimer::pHead;
int UiTimer::timerID;
#define TIMER_SPANTIME 50
void UiTimer::Init()
{
	pCur = pHead = NULL;
	timerID=vaf_create_timer(TIMER_SPANTIME,Sys_Callback);
}
void UiTimer::Destroy()
{
	if(timerID>=-1)
	{
		vaf_delete_timer(timerID);
	} 
	UiTimerList* pTemp = pHead;
	if(!pHead)
		return;
	while(pTemp->next)
	{
		UiTimerList* pNext = pTemp->next;
		delete pTemp;
		pTemp = pNext;
	}

	delete pTemp;
}
bool UiTimer::RegisterTimer(CTimer* timer,int mil,int id)
{
	UiTimerList* pTemp = pHead;
	while(pTemp)
	{
		if(pTemp->timer == timer && pTemp->id == id)
			return false;
		pTemp = pTemp->next;
	}
	if(pHead==NULL)
	{
		UiTimerList* item = new UiTimerList();
		item->curMil = 0;
		item->id = id;
		item->mil = mil;
		item->timer = timer;
		item->next = NULL;
		pCur = pHead = item;
	}
	else
	{
		UiTimerList* item = new UiTimerList();
		item->id = id;
		item->curMil = 0;
		item->timer = timer;
		item->mil = mil;
		item->next = NULL;
		pCur->next = item;
		pCur = item;
	}
	return true;
}

bool UiTimer::UnRegisterTimer(CTimer* timer,int id)
{
	UiTimerList* list=NULL;
	UiTimerList* pParent=NULL;
	UiTimerList* item=NULL;
	int isFind=FALSE;
	list=pHead;
	while(list)
	{
		if(list->timer==timer && list->id==id)
		{
			item = list;
			isFind=TRUE;
			break;
		}
		pParent=list;
		list = list->next;
	}
	if(!isFind)
		return false;
	
	if(pParent)
	{ 
		pParent->next=item->next;
		if(!item->next)
// 		{
// 			pCur=pParent->next;
// 		}
// 		else
		{
			pCur=pParent;
		}
//		(*item).timer=NULL;
		delete item;
		item=NULL;
	}
	else
	{	
		pHead=pHead->next;
//		(*item).timer=NULL;
		delete item;
		item=NULL;
	}
	return true;
}

void UiTimer::Sys_Callback(int tid)
{
	UiTimerList* item=pHead;
	while(item)
	{
		item->curMil+=TIMER_SPANTIME;
		if(item->timer && item->curMil>=item->mil)
		{
			item->timer->TimerCallback(item->id);
			item->curMil = 0;
		}
		item = item->next;
	}
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
UiBase::UiBase(void)
{
	hBase = (long)this;
	x = y = width = height = 0;
	memset(&rc, 0, sizeof(RECT));
	memset(&name, 0, sizeof(name));
	id = -1;
	is_key_down = false;
	is_touch_down = false;
	is_moving = false;

	enum_layers = ENUM_LAYERS_BOTH;
}

UiBase::~UiBase(void)
{

}
 

void UiBase::SetPos(int nx, int ny, int nwidth, int nheight)
{
	x = nx;
	y = ny;
	width = nwidth;
	height = nheight;
	
	rc.left = x;
	rc.top = y;
	rc.right = x + width;
	rc.bottom = y + height;
}

void UiBase::SetAlignPos(int toLeft, int toTop, int toRight, int toBottom)
{
	rc.left = toLeft;
	rc.top = toTop;
	rc.right = vaf_get_lcd_width()- toRight;
	rc.bottom = vaf_get_lcd_height() - toBottom;
	
	x = rc.left;
	y = rc.top;
	width = rc.right - rc.left;
	height = rc.bottom - rc.top;
}

void UiBase::SetName(CVString* str)
{
	if(str)
	{
		name = str->C_Str();
	}
}

void UiBase::SetName(char* str)
{
	if(str)
	{
		name = str;
	}
}

char* UiBase::GetName(void)
{
	return name.C_Str();
}

void UiBase::SetID(int nID)
{
	id = nID;
}

int UiBase::GetID(void)
{
	return id;
}

int UiBase::GetX(void)
{
	return x;
}

int UiBase::GetY(void)
{
	return y;
}

int UiBase::GetWidth(void)
{
	return width;
}

int UiBase::GetHeight(void)
{
	return height;
}

RECT* UiBase::GetRect(void)
{
	return &rc;
}

void UiBase::GetRect(RECT* rcRect)
{
	*rcRect = rc;
}

int UiBase::MessageProc(int message, int sub_message, long wParam, long lParam)
{
	return 0;
}

int UiBase::PostMessage(int message, int sub_message, long wParam, long lParam)
{
	return MessageProc(message, sub_message, wParam, lParam);
}

void UiBase::KeyDownHandle(int key_code)
{
	
}

void UiBase::KeyUpHandle(int key_code)
{
	
}
void UiBase::TouchDownHandle(int nx, int ny)
{
	
}

void UiBase::TouchUpHandle(int nx, int ny)
{
	
}

void UiBase::TouchMoveHandle(int nx, int ny)
{
	
}

void UiBase::Flush(void)
{
	switch(GetLayerUse())
	{
	case ENUM_LAYERS_LAYER0:
		{
			int layers = vaf_get_layer0_handle();
			vaf_flush_layer(&layers, 0);
		}
		break;
	case ENUM_LAYERS_LAYER1:
		{
			int layers = vaf_get_layer1_handle();
			vaf_flush_layer(&layers, 1);
		}
		break;
	case ENUM_LAYERS_BOTH:
		vaf_flush_layer(vaf_get_layers_handle(), 2);
		//vaf_flush_layer_rect(vaf_get_layers_handle(), 2, 0, 0, 100, 100);
		break;
	}
}

void UiBase::Flush(int x1, int y1, int x2, int y2)
{
	switch(GetLayerUse())
	{
	case ENUM_LAYERS_LAYER0:
		{
			int layers = vaf_get_layer0_handle();
			vaf_flush_layer_rect(&layers, 1, x1, y1, x2, y2);
		}
		break;
	case ENUM_LAYERS_LAYER1:
		{
			int layers = vaf_get_layer1_handle();
			vaf_flush_layer_rect(&layers, 1, x1, y1, x2, y2);
		}
		break;
	case ENUM_LAYERS_BOTH:
		vaf_flush_layer_rect(vaf_get_layers_handle(), 2, x1, y1, x2, y2);
		break;
	}
}

void UiBase::Update(void)
{

}

void UiBase::Paint(int* handle, RECT* rcRect, int nx, int ny, int nwidth, int nheight)
{

}

void UiBase::SetLayerUse(int flag)
{
	enum_layers = flag;
}

int UiBase::GetLayerUse(void)
{
	return enum_layers;
}


 
CTimer::CTimer()
{

}
CTimer::~CTimer()
{
}
void CTimer::TimerCallback(int timer_id)
{
	return;
}
void CTimer::CreateTimer(int spanTime,int id)
{ 
	UiTimer::RegisterTimer(this,spanTime,id);
}
void CTimer::DeleteTimer(int id)
{ 
	UiTimer::UnRegisterTimer(this,id);
}
