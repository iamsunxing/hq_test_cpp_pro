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
    // 构造函数
    SXString();
    explicit SXString(int ANum, int ARadix=10); //把一个整型转化成字符串，其中ARadix为进制
    SXString(char AStr);
    SXString(const char* AStr);
    SXString(const SXString& AStr);
    // 析构函数
    virtual ~SXString();
    // 功能函数
    void Display();
    SXString SubString(int AStartIndex, int AEndIndex);
    bool Equal(const SXString AStr);
    // 运算符重载
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
    /* 隐藏类的内部结构，只留出对外接口 */
    struct TMemMap;
    TMemMap* TS_Data;

};

}

#endif // SXSTRING_H
