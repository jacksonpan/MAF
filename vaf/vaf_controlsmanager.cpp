#include "vaf_window.h"
#include "vaf_controlsmanager.h"


UiCtrManager::UiCtrManager(void)
{
	controls = new CVArray();
	parent_hwnd = NULL;
	enable_auto_change_focus = true;
}

UiCtrManager::~UiCtrManager(void)
{
	if(controls)
	{
		delete controls;
	}
}

void UiCtrManager::IsEnableAutoChangeFocus(bool flag)
{
	enable_auto_change_focus = flag;
}

bool UiCtrManager::GetIsEnableAutoChangeFocus(void)
{
	return enable_auto_change_focus;
}



int UiCtrManager::GetFocusedID(void)
{
	if(controls == NULL)
	{
		return -1;
	}

	for(int i=0;i<controls->GetCount();i++)
	{
		UiControl* pCtrl = (UiControl*)controls->objectAtIndex(i);
		if(pCtrl)
		{
			if(pCtrl->GetIsFocused() == true)
			{
				return pCtrl->GetID();
			}
		}
	}
	return -1;
}

int UiCtrManager::CtrManagerMessageProc(int message, int sub_message, long wParam, long lParam)
{
	UiWindow* ParentWnd = (UiWindow*)parent_hwnd;

	if(controls == NULL)
	{
		return 0;
	}
	
	for(int i=0;i<controls->GetCount();i++)
	{
		UiControl* ctrl = (UiControl*)controls->objectAtIndex(i);
		if(ctrl->GetIsEnableControl() == TRUE)
		{
			if(message == MSG_KEY_EINT)
			{
				if(GetIsEnableAutoChangeFocus() == TRUE)
				{
					int key_code = wParam;
					int key_event = sub_message;
					
					switch(key_code)
					{
					case KEY_UP:
						{			
							if(key_event == MSG_KEY_DOWN)
							{
								if(ctrl->GetIsFocused() == TRUE)
								{ 
									if(!ctrl->is_lost_focus)
									{
										return 0;
									}

//									VafVectorStruct* pPrevList = p->prev;

									for(int j=0;j<controls->GetCount();j++)
									{
										UiControl* pCurFocus = (UiControl*)controls->objectAtIndex(j);
										if(pCurFocus->GetIsEnableFocus() == FALSE)
										{
											continue;
										}
										if(pCurFocus == ctrl)
										{
											UiControl* pPrevFocus = NULL;
											int k=controls->GetCount()-1;
_FOCUS_CHANGE_UP_1:
											if(j-1<controls->GetCount()&&j>1)
											{
												pPrevFocus = (UiControl*)controls->objectAtIndex(j-1);
												if(pPrevFocus->GetIsEnableFocus() == TRUE)
												{
													if(ParentWnd->GetIsTopWindow() == true)
													{
														pPrevFocus->PostMessage(MSG_CTR_FOCUS_CHANGE, MSG_CTR_FOCUS_CHANGE_DOWN, (long)ctrl, 0);
													}
													return 0;
												}
												else
												{
													j--;
													goto _FOCUS_CHANGE_UP_1;
												}
											}
											else
											{
_FOCUS_CHANGE_UP:
												pPrevFocus = (UiControl*)controls->objectAtIndex(k);
												if(pPrevFocus->GetIsEnableFocus() == TRUE)
												{
													if(ParentWnd->GetIsTopWindow() == true)
													{
														pPrevFocus->PostMessage(MSG_CTR_FOCUS_CHANGE, MSG_CTR_FOCUS_CHANGE_DOWN, (long)ctrl, 0);
													}
													return 0;
												}
												k--;
												if(k<0)
												{
													k=0;
												}
												goto _FOCUS_CHANGE_UP;
											}
										}
									}
								}
							}
						}
						break;
					case KEY_DOWN:
						{						
							if(key_event == MSG_KEY_DOWN)
							{
								if(ctrl->GetIsFocused() == TRUE)
								{
									if(!ctrl->is_lost_focus)
									{
										return 0;
									}

									for(int j=0;j<controls->GetCount();j++)
									{
										UiControl* pCurFocus = (UiControl*)controls->objectAtIndex(j);
										if(pCurFocus == ctrl)
										{
											UiControl* pNextFocus = NULL;
											int k=0;
_FOCUS_CHANGE_DOWN_1:
											if(j+1<controls->GetCount())
											{
												pNextFocus = (UiControl*)controls->objectAtIndex(j+1);
												if(pNextFocus->GetIsEnableFocus() == TRUE)
												{
													if(ParentWnd->GetIsTopWindow() == true)
													{
														pNextFocus->PostMessage(MSG_CTR_FOCUS_CHANGE, MSG_CTR_FOCUS_CHANGE_DOWN, (long)ctrl, 0);
													}
													return 0;
												}
												else
												{
													j++;
													goto _FOCUS_CHANGE_DOWN_1;
												}
											}
											else
											{
_FOCUS_CHANGE_DOWN:
												pNextFocus = (UiControl*)controls->objectAtIndex(k);
												if(pNextFocus->GetIsEnableFocus() == TRUE)
												{
													if(ParentWnd->GetIsTopWindow() == true)
													{
														pNextFocus->PostMessage(MSG_CTR_FOCUS_CHANGE, MSG_CTR_FOCUS_CHANGE_DOWN, (long)ctrl, 0);
													}
													return 0;
												}
												k++;
												goto _FOCUS_CHANGE_DOWN;
											}
										}
									}
								}
							}
						}
						break;
					default:
						if((ctrl->GetIsEnableKeyHandle() == TRUE && ctrl->GetIsFocused() == TRUE)||(ctrl->GetIsEnableKeyHandle() == TRUE && ctrl->GetIsEnableOverallKeyHandle() == TRUE))
						{
							if(ParentWnd->GetIsTopWindow() == true)
							{
								ctrl->PostMessage(MSG_KEY_EINT, sub_message, wParam, lParam);
							}
							//return 0;
						}
						break;
					}
				}
				else
				{
					if((ctrl->GetIsEnableKeyHandle() == TRUE && ctrl->GetIsFocused() == TRUE)||(ctrl->GetIsEnableKeyHandle() == TRUE && ctrl->GetIsEnableOverallKeyHandle() == TRUE))
					{
						if(ParentWnd->GetIsTopWindow() == true)
						{
							ctrl->PostMessage(MSG_KEY_EINT, sub_message, wParam, lParam);
						}
						//return 0;
					}
				}
			}
			else
			if(message == MSG_TOUCH_EINT)
			{
				RECT rcCtrl;
				VMINT x = wParam;
				VMINT y = lParam;
				ctrl->GetRect(&rcCtrl);

				if(ctrl->GetIsEnableTouchHandle() == TRUE)
				{
					if(x > rcCtrl.left && x < rcCtrl.right && y > rcCtrl.top && y < rcCtrl.bottom)
					{
						if(ctrl->GetIsFocused() == FALSE && ctrl->GetIsEnableFocus() == TRUE && ctrl->GetIsVisible() == TRUE)
						{
// 							VafVectorStruct *pFocused = controls->GetArray();
							UiControl* pTemp = NULL;
							for(int j=0;j<controls->GetCount();j++)
							{
								pTemp = (UiControl*)controls->objectAtIndex(j);
								if(pTemp && pTemp->GetIsFocused() == TRUE)
								{
									break;
								}
							}
							if(pTemp)
							{
								UiWindow* ParentWnd = (UiWindow*)parent_hwnd;
								if(ParentWnd->GetIsTopWindow() == true)
								{
									if(ParentWnd->GetIsTopWindow() == true)
									{
										ctrl->PostMessage(MSG_CTR_FOCUS_CHANGE, MSG_CTR_FOCUS_CHANGE_TOUCH, (long)pTemp, 0);
									}
								}
							}
							else
							{
								if(ParentWnd->GetIsTopWindow() == true)
								{
									if(ParentWnd->GetIsTopWindow() == true)
									{
										ctrl->PostMessage(MSG_CTR_FOCUS_CHANGE, MSG_CTR_FOCUS_CHANGE_ME, 0, 0);
									}
								}
							}
						}
						if(ParentWnd->GetIsTopWindow() == true  && ctrl->GetIsVisible() == TRUE)
						{
							ctrl->PostMessage(MSG_TOUCH_EINT, sub_message, wParam, lParam);
						}
	 					//break;
					}
					else
					if(ctrl->GetIsEnableOverallTouchHandle() == TRUE && ctrl->GetIsVisible() == TRUE)
					{
						if(ParentWnd->GetIsTopWindow() == true)
						{
							ctrl->PostMessage(MSG_TOUCH_EINT, sub_message, wParam, lParam);
						}
					}
				}
			}
		}
	}

	return 0;
}

int UiCtrManager::PostMessage(int message, int sub_message, long wParam, long lParam)
{
	return CtrManagerMessageProc(message, sub_message, wParam, lParam);
}

void UiCtrManager::SetParenthWnd(long lhWnd)
{
	parent_hwnd = lhWnd;
}

int UiCtrManager::GetCount()
{
	return controls->GetCount();
}

UiControl* UiCtrManager::GetUIControl( long handle /*= -1*/, int ID /*= -1*/ )
{
	if(handle == -1 && ID == -1)
	{
		return NULL;
	}
	else if(handle == -1 && ID != -1)
	{
		int icount = controls->GetCount();
		for(int i = 0; i < icount; i++)
		{
			UiControl* pTemp = (UiControl*)controls->objectAtIndex(i);
			if(pTemp->GetID() == ID)
			{
				return pTemp;
			}
		}
	}
	else if(handle != -1 && ID == -1)
	{
		int icount = controls->GetCount();
		for(int i = 0; i < icount; i++)
		{
			UiControl* pTemp = (UiControl*)controls->objectAtIndex(i);
			if(pTemp->hBase == handle)
			{
				return pTemp;
			}
		}
	}
	else
	{
		int icount = controls->GetCount();
		int i;
		for(i = 0; i < icount; i++)
		{
			UiControl* pTemp = (UiControl*)controls->objectAtIndex(i);
			if(pTemp->hBase == handle)
			{
				return pTemp;
			}
		}
		for(i = 0; i < icount; i++)
		{
			UiControl* pTemp = (UiControl*)controls->objectAtIndex(i);
			if(pTemp->GetID() == ID)
			{
				return pTemp;
			}
		}
	}
	return NULL;
}

CVArray* UiCtrManager::GetControlList( void )
{
	return controls;
}

void UiCtrManager::AddUIControl( UiControl* control )
{
	controls->addObject(control);
}

void UiCtrManager::RemoveUIControl( UiControl* control )
{
	int index = controls->GetIndexByObject(control);
	controls->removeObjectAtIndex(index);
}

void UiCtrManager::RemoveAllUIControls( void )
{
	controls->removeAllObjects();
}
