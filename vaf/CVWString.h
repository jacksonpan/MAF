#ifndef __CVWString_h__
#define __CVWString_h__

#include "../vaf/vaf_include.h"
//����VRE�ϵ�˫�ֽ��ַ�������ʹ�õ���short���ͣ�������WIN32�ϵ��Ե�ʱ�����޷��������ݵģ�
//����Ҳû�취ȫ��ת����wchar_t�����Դ��಻�Ƽ�ʹ�ã�ȥ��������const���ܴ��ڰ�ȫ������
//����ʹ�ã��뾡����Ҫ��NULLָ�������

/**
 * @brief VAF�ַ�����
 */

class CVWString
{
public:
	CVWString(void);
	/**
	 * @brief ���캯��
	 * @param str ��str��Ϊ��ʼ���ַ���.
	 */
	CVWString(CVWString &str);
	/**
	 * @brief ���캯��
	 * @param pStr ��pStr��Ϊ��ʼ���ַ���
	 */
	CVWString(wchar *pStr);

	/**
	 * @brief ���캯��
	 * @param str_length Ĭ������str_length���ȵ��ַ����ռ䲢��ʼ��0
	 */
	CVWString(int str_length);

	virtual ~CVWString(void);

	/// ����ַ�������ָ��, �������ַ�����ʽ����.
	wchar* C_Str() const;

	/// ����ַ����ĳ��ȣ��ַ�������
	int Length() const;

	/// �Ƿ�Ϊ���ַ���
	bool IsEmpty() const;

	/// ������ַ���
	CVWString SubStr(int nPosStart, int nCount);

	/// ����ַ���BUFFER�Ĵ�С
	uint GetBufferSize() const;
	
	/// �����ַ���BUFFER�Ĵ�С������Ϊ�ַ����ĳ��ȣ�����������ݽ��ᱻ���
	void SetBufferSize(int str_length);

	/// ���ַ���BUFFER���㣬�����ı�BUFFER������
	void ZeroBuffer();

	/// = operator
	CVWString& operator=(CVWString &str);
	/// = operator
	CVWString& operator=(wchar *pStr);

	/// �ַ������� operator
	CVWString operator+(CVWString &str);
	/// �ַ������� operator
	CVWString operator+(wchar *pStr);

	/// �ַ����Ƚ�: ����ֵ�� C ���� strcmp ��ͬ
    /**
        @return -1: ����<pStr; 0: ����==pStr; 1: ����>pStr;
     */
	int Compare(wchar* pStr) const;
	/// �ַ����Ƚ�: ����ֵ�� C ���� strcmp ��ͬ
    /**
        @return -1: ����<str; 0: ����==str; 1: ����>str;
     */
	int Compare(CVWString& str) const;

	/// == operator
	bool operator==(wchar* pStr) const;
	/// == operator
	bool operator==(CVWString& str) const;

    /// �ڶ���������ĳ���ַ����������ҵ����ַ�����λ�ã�����Ҳ����򷵻�-1��
    int Find(wchar* pStr, int beginPos=0) const;
    
    /// �ڶ���������ĳ���ַ����������ҵ����ַ�����λ�ã�����Ҳ����򷵻�-1��
    int Find(CVWString& str, int beginPos=0) const;

    /// ���ַ������������������ַ�
    /**
       ���ַ������������������ַ�
       @param ch Ҫ�������ַ�
       @param beginPos ��ʼ����λ��
       @return �������ַ��򷵻�����λ�ã����򷵻�-1
     */
    int Find(wchar ch, int beginPos=0) const;

    /// ͨ������ֱ�ӷ����ַ�����ĳ��λ�õ��ַ�
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