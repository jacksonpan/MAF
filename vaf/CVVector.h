/********************************************************************
	created:	2011/03/23
	created:	23:3:2011   23:47
	filename: 	C:\SVN_AppDev\trunk\VAF\common\CVVector.h
	file path:	C:\SVN_AppDev\trunk\VAF\common
	file base:	CVVector
	file ext:	h
	author:		jack
	
	purpose:	
*********************************************************************/
#ifndef __CVVector_h__
#define __CVVector_h__

#include "../vaf/vaf_include.h"

#define VafVector				CVVector
#define VafVectorStruct		CVVectorStruct

typedef struct _CVVectorStruct
{
	int index;
	void* p;
	int len;
	struct _CVVectorStruct* prev;
	struct _CVVectorStruct* next;
}CVVectorStruct;

class CVVector
{
public:
	CVVector(void);
	~CVVector(void);
	
	void Add(void* p);
	void Add(void* p, int len);
	void Insert(void*p, int index);
	void Insert(void*p, int len, int index);
	void Modify(int index, void* pData);
	void Modify(int index, void* pData, int len);
	void Delete(int index);
	void Swap(int index1, int index2);
	void Rearrange(void);
	void* GetData(int index);
	int GetCount(void);
	
	void Destroy(void);
public:
	CVVectorStruct* GetVector(void);
private:
	CVVectorStruct* Find(int index);
private:
	CVVectorStruct *vvlist;
	CVVectorStruct *vvlist_last;
	int count;
};

#endif // __CVVector_h__