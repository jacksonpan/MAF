/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   23:48
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVVector.cpp
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVVector
	file ext:	cpp
	author:		jack
	
	purpose:	
*********************************************************************/
#include "CVVector.h"

CVVector::CVVector(void)
{
	vvlist = NULL;
	vvlist_last = NULL;
	count = 0;
}

CVVector::~CVVector(void)
{
	Destroy();
}

void CVVector::Add(void* p)
{
	if(p)
	{
		if(vvlist == NULL)
		{
			vvlist = new CVVectorStruct;
			vvlist->index = count;
			vvlist->len = 0;
			vvlist->p = p;
			vvlist->prev = NULL;
			vvlist->next = NULL;
			vvlist_last = vvlist;
		}
		else
		{
			CVVectorStruct* temp = new CVVectorStruct;
			temp->index = count;
			temp->len = 0;
			temp->p = p;
			temp->prev = vvlist_last;
			temp->next = NULL;
			vvlist_last->next = temp;
			vvlist_last = temp;
		}

		count++;
	}
}

void CVVector::Add(void* p, int len)
{
	if(p && len > 0)
	{
		if(vvlist == NULL)
		{
			vvlist = new CVVectorStruct;
			vvlist->index = count;
			vvlist->len = len;
			vvlist->p = vaf_malloc(len);
			memcpy(vvlist->p, p, len);
			vvlist->prev = NULL;
			vvlist->next = NULL;
			vvlist_last = vvlist;
		}
		else
		{
			CVVectorStruct* temp = new CVVectorStruct;
			temp->index = count;
			temp->len = len;
			temp->p = vaf_malloc(len);
			memcpy(temp->p, p, len);
			temp->prev = vvlist_last;
			temp->next = NULL;
			vvlist_last->next = temp;
			vvlist_last = temp;
		}

		count++;
	}
}

void CVVector::Insert( void*p, int index )
{
	if(p)
	{
		if(vvlist == NULL && index == 0)
		{
			vvlist = new CVVectorStruct;
			vvlist->index = count;
			vvlist->len = 0;
			vvlist->p = p;
			vvlist->prev = NULL;
			vvlist->next = NULL;
			vvlist_last = vvlist;
			count++;
		}
		else if(vvlist == NULL && index != 0)
		{
			return;
		}
		else
		{
			CVVectorStruct* pCurIndex = Find(index);
			CVVectorStruct* temp = new CVVectorStruct;
			if(index == count - 1)
			{
				temp->index = count;
				temp->len = 0;
				temp->p = p;
				temp->prev = pCurIndex;
				temp->next = NULL;
				pCurIndex->next = temp;
				vvlist_last = temp;
				count++;
			}
			else
			{
				temp->index = -1;
				temp->len = 0;
				temp->p = p;
				temp->prev = pCurIndex;
				temp->next = pCurIndex->next;
				pCurIndex->next = temp;
				count++;
				Rearrange();
			}
		}
	}
}

void CVVector::Insert( void*p, int len, int index )
{
	//wait to show
}

CVVectorStruct* CVVector::Find(int index)
{
	CVVectorStruct* p = vvlist;
	while(p)
	{
		if(p->index == index)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void CVVector::Modify(int index, void* pData)
{
	CVVectorStruct* p = vvlist;
	if(pData)
	{
		while(p)
		{
			if(p->index == index)
			{
				p->p = pData;
				break;
			}
			p = p->next;
		}
	}
}

void CVVector::Modify(int index, void* pData, int len)
{
	CVVectorStruct* p = vvlist;
	if(pData && len >0)
	{
		while(p)
		{
			if(p->index == index)
			{
				if(p->p)
				{
					vaf_free(p->p);
					p->p = NULL;
				}
				p->p = vaf_malloc(len);
				memcpy(p->p, pData, len);
				break;
			}
			p = p->next;
		}
	}
}

void CVVector::Delete(int index)
{
	CVVectorStruct* pPrev = NULL;
	CVVectorStruct* pCur = NULL;	
	CVVectorStruct* pNext = NULL;
	
	pPrev = Find(index - 1);
	pCur = Find(index);
	pNext = Find(index + 1);
	
	if(pPrev == NULL)
	{
		vvlist = pNext;
		if(pCur->p && pCur->len != 0)
		{
			vaf_free(pCur->p);
			pCur->p = NULL;
		}
		else
		{
			pCur->p = NULL;
		}
		delete pCur;
		pCur = NULL;
	}
	else
	if(pNext == NULL)
	{
		pPrev->next = NULL;
		if(pCur->p && pCur->len != 0)
		{
			vaf_free(pCur->p);
			pCur->p = NULL;
		}
		else
		{
			pCur->p = NULL;
		}
		delete pCur;
		pCur = NULL;
		vvlist_last = pPrev;
	}
	else
	{
		pPrev->next = pNext;
		pNext->prev = pPrev;
		if(pCur->p && pCur->len != 0)
		{
			vaf_free(pCur->p);
			pCur->p = NULL;
		}
		else
		{
			pCur->p = NULL;
		}
		delete pCur;
		pCur = NULL;
	}

	Rearrange();
}

void CVVector::Swap(int index1, int index2)
{
	CVVectorStruct* p1 = NULL;
	CVVectorStruct* p2 = NULL;
	void* temp;
	int temp_len;
	
	if(index1 >= count || index1 < 0)
	{
		return;
	}
	if(index2 >= count || index2 < 0)
	{
		return;
	}
	
	p1 = Find(index1);
	p2 = Find(index2);
	
	temp = p1->p;
	temp_len = p1->len;
	p1->p = p2->p;
	p1->len = p2->len;
	p2->p = temp;
	p2->len = temp_len;

	Rearrange();
}

void CVVector::Rearrange(void)
{

	CVVectorStruct* p = vvlist;
	CVVectorStruct* pPrev = NULL;
	count = 0;
	
	while(p)
	{
		pPrev = p;
		p->index = count;
		p = p->next;
		count++;
	}
	vvlist_last = pPrev;
}

void CVVector::Destroy(void)
{
	CVVectorStruct* p = vvlist;
	while(p)
	{
		CVVectorStruct* ptemp = p->next;
		if(p->p && p->len != 0)
		{
			vaf_free(p->p);
			p->p = NULL;
		}
		else
		{
			p->p = NULL;
		}
		delete p;
		p = ptemp;
	}

	vvlist = NULL;
	vvlist_last = NULL;
	count = 0;
}

void* CVVector::GetData(int index)
{
	CVVectorStruct* p = Find(index);
	if(p)
	{
		return p->p;
	}
	return 0;
}

int CVVector::GetCount(void)
{
	return count;
}

CVVectorStruct* CVVector::GetVector( void )
{
	return vvlist;
}
