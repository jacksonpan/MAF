#ifndef __CVWString_h__
#define __CVWString_h__

#include "../vaf/vaf_include.h"
//由于VRE上的双字节字符串类型使用的是short类型，所以在WIN32上调试的时候是无法看到内容的，
//我们也没办法全部转换到wchar_t，所以此类不推荐使用，去掉了所有const可能存在安全隐患，
//如需使用，请尽量不要传NULL指针进来。

/**
 * @brief VAF字符串类
 */

class CVWString
{
public:
	CVWString(void);
	/**
	 * @brief 构造函数
	 * @param str 以str作为初始化字符串.
	 */
	CVWString(CVWString &str);
	/**
	 * @brief 构造函数
	 * @param pStr 以pStr作为初始化字符串
	 */
	CVWString(wchar *pStr);

	/**
	 * @brief 构造函数
	 * @param str_length 默认申请str_length长度的字符串空间并初始化0
	 */
	CVWString(int str_length);

	virtual ~CVWString(void);

	/// 获得字符串的首指针, 可用于字符串格式化等.
	wchar* C_Str() const;

	/// 获得字符串的长度（字符个数）
	int Length() const;

	/// 是否为空字符串
	bool IsEmpty() const;

	/// 获得子字符串
	CVWString SubStr(int nPosStart, int nCount);

	/// 获得字符串BUFFER的大小
	uint GetBufferSize() const;
	
	/// 设置字符串BUFFER的大小，参数为字符串的长度，如果已有内容将会被清除
	void SetBufferSize(int str_length);

	/// 把字符串BUFFER置零，但不改变BUFFER的容量
	void ZeroBuffer();

	/// = operator
	CVWString& operator=(CVWString &str);
	/// = operator
	CVWString& operator=(wchar *pStr);

	/// 字符串连接 operator
	CVWString operator+(CVWString &str);
	/// 字符串连接 operator
	CVWString operator+(wchar *pStr);

	/// 字符串比较: 返回值与 C 函数 strcmp 相同
    /**
        @return -1: 对象<pStr; 0: 对象==pStr; 1: 对象>pStr;
     */
	int Compare(wchar* pStr) const;
	/// 字符串比较: 返回值与 C 函数 strcmp 相同
    /**
        @return -1: 对象<str; 0: 对象==str; 1: 对象>str;
     */
	int Compare(CVWString& str) const;

	/// == operator
	bool operator==(wchar* pStr) const;
	/// == operator
	bool operator==(CVWString& str) const;

    /// 在对象中搜索某个字符串。返回找到的字符串的位置，如果找不到则返回-1。
    int Find(wchar* pStr, int beginPos=0) const;
    
    /// 在对象中搜索某个字符串。返回找到的字符串的位置，如果找不到则返回-1。
    int Find(CVWString& str, int beginPos=0) const;

    /// 在字符串中正向搜索单个字符
    /**
       在字符串中正向搜索单个字符
       @param ch 要搜索的字符
       @param beginPos 起始查找位置
       @return 搜索到字符则返回它的位置，否则返回-1
     */
    int Find(wchar ch, int beginPos=0) const;

    /// 通过索引直接访问字符串中某个位置的字符
    wchar& operator[](const int index);
	
	/// type conversion operator
	operator wchar*() const;
 
    /// += operator
    CVWString& operator+=(CVWString &str);
    /// += operator
    CVWString& operator+=(wchar *pStr);

private:

	void* alloc(int nSize);

	void append(wchar* pStr);

	void append(CVWString* pStr);

	void set(wchar* pStr);

	void set(CVWString* pStr);

	void Reset(void);

	wchar* v_pData;

	uint v_nSize;
};
#endif