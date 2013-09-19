#include "CVArray.h"

CVArray::CVArray( int len /*= CVARRAY_COUNT_LEN*/ )
{
	arrayLen = len;
	arrayList = NULL;
	count = 0;
	allocArrayList(&arrayList, arrayLen);
}

CVArray::~CVArray( void )
{
	removeAllObjects();
}

void CVArray::freeArrayList( ArrayListStruct** list, int* len )
{
	if(list)
	{
		if(*list)
		{
			delete[] *list;
			*list = NULL;
			*len = 0;
		}
	}
}

void CVArray::allocArrayList( ArrayListStruct** list, int len )
{
	if(list)
	{
		if(*list == NULL)
		{
			*list = new ArrayListStruct[len];
			memset(*list, 0, sizeof(ArrayListStruct)*len);
			sortArrayList(*list, len);
		}
		else
		{
			freeArrayList(list, &len);
			allocArrayList(list, len);
		}
	}
}

void CVArray::sortArrayList( ArrayListStruct* list, int len )
{
	for(int i=0;i<len;i++)
	{
		list[i].index = i;
	}
}

void CVArray::addObject( void* object )
{
	if(arrayList)
	{
		arrayList[count].ptr = object;
		count++;
		if(count == arrayLen)
		{
			reallocArrayList(&arrayList, &arrayLen, arrayLen + CVARRAY_COUNT_LEN);
		}
	}
	else
	{
		arrayLen = CVARRAY_COUNT_LEN;
		allocArrayList(&arrayList, arrayLen);
		addObject(object);
	}
}

void CVArray::insertObject( void* object, int index )
{
	if(arrayList)
	{
		if(index >= arrayLen)
		{
			reallocArrayList(&arrayList, &arrayLen, arrayLen + CVARRAY_COUNT_LEN);
		}
		if(arrayList[index].ptr == NULL)
		{
			arrayList[index].ptr = object;
		}
		else
		{
			for(int i=count;i>=index;i--)
			{
				arrayList[i].ptr = arrayList[i-1].ptr;
			}
			arrayList[index].ptr = object;
			count++;
		}
	}
	else
	{
		addObject(object);
	}
}

void* CVArray::objectAtIndex( int index )
{
	if(index < arrayLen && arrayList)
	{
		return arrayList[index].ptr;
	}
	return NULL;
}

void CVArray::reallocArrayList( ArrayListStruct** list, int* src_len, int new_len )
{
	if(list)
	{
		if(*list)
		{
			ArrayListStruct* newList = NULL;
			allocArrayList(&newList, new_len);
			for(int i=0;i<*src_len;i++)
			{
				newList[i] = (*list)[i];
			}
			freeArrayList(list, src_len);
			*list = newList;
			*src_len = new_len;
		}
		else
		{
			allocArrayList(list, new_len);
		}
	}
}

void CVArray::removeAllObjects( void )
{
	freeArrayList(&arrayList, &arrayLen);
	count = 0;
}

int CVArray::GetCount( void )
{
//	return arrayLen;
	return count;
}

int CVArray::GetIndexByObject( void* object )
{
	if(arrayList)
	{
		for(int i=0;i<GetCount();i++)
		{
			if(arrayList[i].ptr == object)
			{
				return i;
			}
		}
	}
	return -1;
}

void CVArray::replaceObjectAtIndex( int index, void* object )
{
	if(arrayList && index < GetCount())
	{
		arrayList->ptr = object;
	}
}

void CVArray::removeObjectAtIndex( int index )
{
	if(arrayList && index < GetCount())
	{
		arrayList[index].ptr = NULL;
		resortArrayList(arrayList, arrayLen);
		count--;
	}
}

void CVArray::resortArrayList( ArrayListStruct* list, int len )
{
	if(list)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].ptr == NULL)
			{
				if(i != len - 1)
				{
					list[i].ptr = list[i+1].ptr;
					list[i+1].ptr = NULL;
				}
			}
		}
	}
}

void CVArray::removeLastObject( void )
{
	removeObjectAtIndex(count - 1);
}

void* CVArray::operator[]( int index )
{
	if(arrayList && index < GetCount())
	{
		return arrayList[index].ptr;
	}

	return NULL;
}

