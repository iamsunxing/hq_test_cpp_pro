#ifndef SXSTRING_H
#define SXSTRING_H
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>

namespace SXLIB
{

class SXString
{
public:
    // ���캯��
    SXString();
    explicit SXString(int ANum, int ARadix=10); //��һ������ת�����ַ���������ARadixΪ����
    SXString(char AStr);
    SXString(const char* AStr);
    SXString(const SXString& AStr);
    // ��������
    virtual ~SXString();
    // ���ܺ���
    void Display();
    SXString SubString(int AStartIndex, int AEndIndex);
    bool Equal(const SXString AStr);
    // ���������
    void      operator += (const SXString& AStr);
    SXString  operator +  (const SXString& AStr);
    SXString& operator =  (const SXString& AStr);

    template<typename T>
    inline SXString operator +  (T AStr)
    {
        return (*this + SXString(AStr));
    }
    template<typename T>
    inline SXString operator += (T AStr)
    {
        *this += SXString(AStr);
        return *this;
    }

    inline SXString& operator = (const char& AStr)
    {
        *this = SXString(AStr);
        return *this;
    }
    inline SXString& operator = (const char* AStr)
    {
        *this = SXString(AStr);
        return *this;
    }
private:

    inline int   GetLength()const;
    inline char* GetC_Str()const;
    inline void  SetLength(int ALength);
    inline void  SetC_Str(char* AStr);
private:
    /* ��������ڲ��ṹ��ֻ��������ӿ� */
    struct TMemMap;
    TMemMap* TS_Data;

};

}

#endif // SXSTRING_H
