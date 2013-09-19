#ifndef __CVString_h__
#define __CVString_h__

#include "../vaf/vaf_include.h"
/**
 * @brief VAF�ַ�����
 */

class CVString
{
public:
	CVString(void);
	/**
	 * @brief ���캯��
	 * @param str ��str��Ϊ��ʼ���ַ���.
	 */
	CVString(const CVString &str);
	/**
	 * @brief ���캯��
	 * @param pStr ��pStr��Ϊ��ʼ���ַ���
	 */
	CVString(const char *pStr);

	/**
	 * @brief ���캯��
	 * @param str_length Ĭ������str_length���ȵ��ַ����ռ䲢��ʼ��0
	 */
	CVString(int str_length);

	virtual ~CVString(void);

	/// ����ַ�������ָ��, �������ַ�����ʽ����.
	char* C_Str() const;

	/// ����ַ����ĳ��ȣ��ַ�������
	int Length() const;

	/// �Ƿ�Ϊ���ַ���
	bool IsEmpty() const;

	/// ������ַ���
	CVString SubStr(int nPosStart, int nCount);

	/// ����ַ���BUFFER�Ĵ�С
	uint GetBufferSize() const;

	/// �����ַ���BUFFER�Ĵ�С������Ϊ�ַ����ĳ��ȣ�����������ݽ��ᱻ���
	void SetBufferSize(int str_length);

	/// ���ַ���BUFFER���㣬�����ı�BUFFER������
	void ZeroBuffer();

	/// = operator
	CVString& operator=(const CVString &str);
	/// = operator
	CVString& operator=(const char *pStr);

	/// �ַ������� operator
	CVString operator+(const CVString &str);
	/// �ַ������� operator
	CVString operator+(const char *pStr);

	/// �ַ����Ƚ�: ����ֵ�� C ���� strcmp ��ͬ
    /**
        @return -1: ����<pStr; 0: ����==pStr; 1: ����>pStr;
     */
	int Compare(const char* pStr) const;
	/// �ַ����Ƚ�: ����ֵ�� C ���� strcmp ��ͬ
    /**
        @return -1: ����<str; 0: ����==str; 1: ����>str;
     */
	int Compare(const CVString& str) const;

	/// == operator
	bool operator==(const char* pStr) const;
	/// == operator
	bool operator==(const CVString& str) const;

    /// �ڶ���������ĳ���ַ����������ҵ����ַ�����λ�ã�����Ҳ����򷵻�-1��
    int Find(const char* pStr, int beginPos=0) const;
    
    /// �ڶ���������ĳ���ַ����������ҵ����ַ�����λ�ã�����Ҳ����򷵻�-1��
    int Find(const CVString& str, int beginPos=0) const;

    /// ���ַ������������������ַ�
    /**
       ���ַ������������������ַ�
       @param ch Ҫ�������ַ�
       @param beginPos ��ʼ����λ��
       @return �������ַ��򷵻�����λ�ã����򷵻�-1
     */
    int Find(char ch, int beginPos=0) const;

    /// ��Сд��ĸת���ɴ�д��ĸ
//     void MakeUpper();

    /// �Ѵ�д��ĸת����Сд��ĸ
//     void MakeLower();

    /// ͨ������ֱ�ӷ����ַ�����ĳ��λ�õ��ַ�
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