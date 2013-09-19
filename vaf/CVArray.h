#ifndef __CVArray_h__
#define __CVArray_h__

#include "../vaf/vaf_include.h"

#define CVARRAY_COUNT_LEN	4
typedef struct _ArrayListStruct 
{
	int index;
	void* ptr;
}ArrayListStruct;

class CVArray
{
public:
	CVArray(int len = CVARRAY_COUNT_LEN);
	~CVArray(void);
public:
	void addObject(void* object);
	void insertObject(void* object, int index);
	void removeLastObject(void);
	void removeObjectAtIndex(int index);
	void replaceObjectAtIndex(int index, void* object);
	int GetCount(void);
	void* objectAtIndex(int index);
	int GetIndexByObject(void* object);
	void removeAllObjects(void);

    void* operator[](int index);
private:
	void allocArrayList(ArrayListStruct** list, int len);
	void reallocArrayList(ArrayListStruct** list, int* src_len, int new_len);
	void freeArrayList(ArrayListStruct** list, int* len);
	void sortArrayList(ArrayListStruct* list, int len);
	void resortArrayList(ArrayListStruct* list, int len);
protected:
	ArrayListStruct* arrayList;
	int arrayLen;
	int count;
};
#endif
