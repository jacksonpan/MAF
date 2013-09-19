#ifndef __CVString_h__
#define __CVString_h__

#include "../vaf/vaf_include.h"
/**
 * @brief VAF字符串类
 */

class CVString
{
public:
	CVString(void);
	/**
	 * @brief 构造函数
	 * @param str 以str作为初始化字符串.
	 */
	CVString(const CVString &str);
	/**
	 * @brief 构造函数
	 * @param pStr 以pStr作为初始化字符串
	 */
	CVString(const char *pStr);

	/**
	 * @brief 构造函数
	 * @param str_length 默认申请str_length长度的字符串空间并初始化0
	 */
	CVString(int str_length);

	virtual ~CVString(void);

	/// 获得字符串的首指针, 可用于字符串格式化等.
	char* C_Str() const;

	/// 获得字符串的长度（字符个数）
	int Length() const;

	/// 是否为空字符串
	bool IsEmpty() const;

	/// 获得子字符串
	CVString SubStr(int nPosStart, int nCount);

	/// 获得字符串BUFFER的大小
	uint GetBufferSize() const;

	/// 设置字符串BUFFER的大小，参数为字符串的长度，如果已有内容将会被清除
	void SetBufferSize(int str_length);

	/// 把字符串BUFFER置零，但不改变BUFFER的容量
	void ZeroBuffer();

	/// = operator
	CVString& operator=(const CVString &str);
	/// = operator
	CVString& operator=(const char *pStr);

	/// 字符串连接 operator
	CVString operator+(const CVString &str);
	/// 字符串连接 operator
	CVString operator+(const char *pStr);

	/// 字符串比较: 返回值与 C 函数 strcmp 相同
    /**
        @return -1: 对象<pStr; 0: 对象==pStr; 1: 对象>pStr;
     */
	int Compare(const char* pStr) const;
	/// 字符串比较: 返回值与 C 函数 strcmp 相同
    /**
        @return -1: 对象<str; 0: 对象==str; 1: 对象>str;
     */
	int Compare(const CVString& str) const;

	/// == operator
	bool operator==(const char* pStr) const;
	/// == operator
	bool operator==(const CVString& str) const;

    /// 在对象中搜索某个字符串。返回找到的字符串的位置，如果找不到则返回-1。
    int Find(const char* pStr, int beginPos=0) const;
    
    /// 在对象中搜索某个字符串。返回找到的字符串的位置，如果找不到则返回-1。
    int Find(const CVString& str, int beginPos=0) const;

    /// 在字符串中正向搜索单个字符
    /**
       在字符串中正向搜索单个字符
       @param ch 要搜索的字符
       @param beginPos 起始查找位置
       @return 搜索到字符则返回它的位置，否则返回-1
     */
    int Find(char ch, int beginPos=0) const;

    /// 把小写字母转换成大写字母
//     void MakeUpper();

    /// 把大写字母转换成小写字母
//     void MakeLower();

    /// 通过索引直接访问字符串中某个位置的字符
    char& operator[](const int index);
	
	/// type conversion operator
	operator char*() const;
 
    /// += operator
    CVString& operator+=(const CVString &str);
    /// += operator
    CVString& operator+=(const char *pStr);

private:

	void* alloc(int nSize);

	void append(const char* pStr);

	void append(const CVString* pStr);

	void set(const char* pStr);

	void set(const CVString* pStr);

	void Reset(void);

	char* v_pData;

	uint v_nSize;
};

#endif