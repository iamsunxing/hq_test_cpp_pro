/**
 *  孙兴
 *  2017/6/28
 */
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include "SXString.h"
using namespace SXLIB;
using namespace std;

#pragma pack(push,1)
//全部是默认的公有成员
struct SXString::TMemMap
{
    char* TMM_Data;
    int TMM_Length;
  //  int TMM_Refcount; //还不会用。。。
    TMemMap();
    TMemMap(int ANum, int ARadix=10);
    TMemMap(char AStr);
    TMemMap(const char* AStr);
    TMemMap(const SXString& AStr);
    virtual ~TMemMap();
};
#pragma pack(pop)

SXString::TMemMap::TMemMap()
{
    TMM_Length = 0;
    TMM_Data = new char[1];
    *(TMM_Data) = '\0';
}

SXString::TMemMap::TMemMap(int ANum, int ARadix)
{
    TMM_Data = new char[40];
    char* pNum = TMM_Data;
    memset(TMM_Data,0,40);
    itoa(ANum,TMM_Data,ARadix);
    for(int i=0; i<40; i++)
    {
        if(*pNum++ == 0)
        {
            TMM_Length = i;
            break;
        }
    }
}

SXString::TMemMap::TMemMap(char AStr)
{
    TMM_Length = 1;
    TMM_Data = new char[2];
    *(TMM_Data) = AStr;
    *(TMM_Data+1) = '\0';
}

SXString::TMemMap::TMemMap(const char* AStr)
{
    this->TMM_Length = strlen(AStr);
    this->TMM_Data = new char[this->TMM_Length+1];
    memcpy(this->TMM_Data,AStr,this->TMM_Length);
    TMM_Data[this->TMM_Length] = '\0';
}

SXString::TMemMap::TMemMap(const SXString& AStr)
{
    this->TMM_Length = AStr.GetLength();
    this->TMM_Data = new char[TMM_Length+1];
    memcpy(TMM_Data,AStr.GetC_Str(),TMM_Length);
    TMM_Data[this->TMM_Length] = '\0';
}

SXString::TMemMap::~TMemMap()
{
    delete []TMM_Data;
}

SXString::SXString/*:TS_Data(new TMemMap)*/()
{
    TS_Data = new TMemMap;

}

SXString::SXString(int ANum, int ARadix)
{
    TS_Data = new TMemMap(ANum,ARadix);
}

SXString::SXString(char AStr)
{
    TS_Data = new TMemMap(AStr);
}

SXString::SXString(const char* AStr)
{
    TS_Data = new TMemMap(AStr);
}

SXString::SXString(const SXString& AStr)
{
    TS_Data = new TMemMap(AStr);
}

SXString::~SXString()
{
    delete TS_Data;
}

inline void SXString::SetLength(int ALength)
{
    TS_Data->TMM_Length = ALength;
}

inline int SXString::GetLength() const
{
    return TS_Data->TMM_Length;
}

inline void SXString::SetC_Str(char* AStr)
{
    delete TS_Data->TMM_Data;
    TS_Data->TMM_Data = AStr;
}

inline char* SXString::GetC_Str() const
{
    return TS_Data->TMM_Data;
}

void SXString::Display()
{
    cout <<"["<< TS_Data->TMM_Data <<"]"<<endl;
}

// 运算符重载
SXString& SXString::operator = (const SXString& AStr)
{
    char* pTemp = new char[AStr.GetLength()+1];
    memcpy(pTemp,AStr.GetC_Str(),AStr.GetLength());
    pTemp[AStr.GetLength()] = '\0';
    this->SetC_Str(pTemp);
    this->SetLength(AStr.GetLength());
    return *this;
}

SXString SXString::operator + (const SXString& AStr)
{
    char* pTemp = new char[this->GetLength()+AStr.GetLength()+1];
    memcpy(pTemp,this->GetC_Str(), this->GetLength());
    memcpy(pTemp+this->GetLength(), AStr.GetC_Str(),AStr.GetLength());
    pTemp[this->GetLength()+AStr.GetLength()]='\0';
    SXString AStr1(pTemp);
    delete []pTemp;
    return AStr1;//返回临时对象
}

void SXString::operator += (const SXString& AStr)
{
    char* pTemp = new char[this->GetLength()+AStr.GetLength()+1];
    memcpy(pTemp,this->GetC_Str(),this->GetLength());
    memcpy(pTemp+this->GetLength(),AStr.GetC_Str(),AStr.GetLength());
    pTemp[this->GetLength()+AStr.GetLength()] = '\0';
    this->SetC_Str(pTemp);
    this->SetLength(this->GetLength()+AStr.GetLength());
}

//下标从0开始
SXString SXString::SubString(int AStartIndex, int AEndIndex)
{
    if (AStartIndex<0 || AEndIndex<AStartIndex || AEndIndex>=this->GetLength())
        return SXString("");
    char* pTemp = new char[AEndIndex - AStartIndex + 2];
    memcpy(pTemp, this->GetC_Str()+AStartIndex, AEndIndex - AStartIndex + 1);
    pTemp[AEndIndex - AStartIndex + 1] = '\0';
    SXString Str(pTemp);
    delete []pTemp;
    return Str;
}

bool SXString::Equal(const SXString AStr)
{
    if(this->GetLength() != AStr.GetLength())
        return false;
    else
        return strcmp(this->GetC_Str(),AStr.GetC_Str());
}
