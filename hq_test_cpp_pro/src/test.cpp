/**
 * AddBCDInt.cpp
 *
 * 概述：实现两个大的正整数相加之和
 * 作者：孙兴
 * 版本：3.0
 * 注意事项：无
 * 修订记录：
 * 		2017/6/17		孙兴			创建文件
 * 		2017/6/23		孙兴			进行模块化，命名标准化,代码重新组织
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef unsigned char Byte;

static int L_AddTwoBCD(Byte ANum1, Byte ANum2, Byte* ADest, int* ACarryFlag);
static int L_CheckCharactor(const Byte* ANum, int ASize);
static int L_ClearPreZero(const Byte* ANum, int ASize, const Byte** ANumOut,
		int* ASizeOut);
int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2,
		Byte* ADest, int ASize);

int main()
{
	Byte arrNum1[] =
	{ 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34 };
	Byte arrNum2[] =
	{ 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x87, 0x65, 0x43, 0x21 };
	const int intResultLength = 30;
	Byte arrDest[intResultLength];
	int intSize1 = sizeof(arrNum1) / sizeof(Byte);
	int intSize2 = sizeof(arrNum2) / sizeof(Byte);
	int intRet = AddBCDInt(arrNum1, intSize1, arrNum2, intSize2, arrDest,
			intResultLength);
	printf("%d\n", intRet);
	for (int i = 0; i < intRet; i++)
	{
		printf("%02x ", arrDest[i]);
	}
	return 0;
}

int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2,
		Byte* ADest, int ASize)
{
	// 检查参数是否合法
	if (NULL == ANum1 || NULL == ANum2 || NULL == ADest || ASize <= 0
			|| ASize1 <= 0 || ASize2 <= 0)
	{
		return -3;
	}

	const Byte* pNum1 = NULL;   // 指向ASize1的第一个非0字节
	const Byte* pNum2 = NULL;   // 指向ASize2的第一个非0字节
	int intSize1 = 0;			// 从pNum1开始的字节数
	int intSize2 = 0;			// 从pNum1开始的字节数
	int intCarryFlag = 0;		// 进位标识

	int intTmp = L_CheckCharactor(ANum1, ASize1);
	if (-2 == intTmp)
		return -1;
	intTmp = L_CheckCharactor(ANum2, ASize2);
	if (-2 == intTmp)
		return -2;
	intTmp = L_ClearPreZero(ANum1, ASize1, &pNum1, &intSize1);
	if (-1 == intTmp)
		return -3;
	intTmp = L_ClearPreZero(ANum2, ASize2, &pNum2, &intSize2);
	if (-1 == intTmp)
		return -3;

	int intMinSize = intSize1;
	int intMaxSize = intSize2;
	int intResultLength = intSize2;
	if (intSize1 > intSize2)
	{
		intMinSize = intSize2;
		intMaxSize = intSize1;
		intResultLength = intSize1;
	}
	else if (intSize1 == intSize2)
	{
		intTmp = (*pNum1 >> 4);
		intTmp += (*pNum2 >> 4);
		if (intTmp > 0x99)
			intResultLength++;
	}

	if (ASize < intMaxSize)
		return 0;
	Byte* pDest = ADest;
	pDest += intResultLength;
	pNum1 += intSize1;
	pNum2 += intSize2;
	for (int i = 0; i < intMinSize; i++)
	{
		--pDest, --pNum1, --pNum2;
		L_AddTwoBCD(*pNum1, *pNum2, pDest, &intCarryFlag);
	}

	if (intSize1 > intSize2)
	{
		for (int i = intMinSize; i < intMaxSize; i++)
		{
			--pDest, --pNum1;
			L_AddTwoBCD(*pNum1, 0, pDest, &intCarryFlag);
		}
	}
	else if (intSize1 < intSize2)
	{
		for (int i = intMinSize; i < intMaxSize; i++)
		{
			--pDest, --pNum2;
			L_AddTwoBCD(*pNum2, 0, pDest, &intCarryFlag);
		}
	}

	if (1 == intCarryFlag)
	{
		memmove(ADest + 1, pDest, intResultLength);
		*ADest = 1;
		intResultLength++;
	}
	return intResultLength;
}

/**
 * 名称：L_CheckCharactor
 * 功能：检查是否有非法字符
 * 参数：ANum 输入参数，起始地址；
 * 		 ASize 输入参数，从ANum开始的字节数
 * 返回值：
 *       -1  参数不合法
 *       -2  存在非法值
 *        0  正常结束
 * 备注：
 * 		 无
 */
static int L_CheckCharactor(const Byte* ANum, int ASize)
{
	if (NULL == ANum || ASize <= 0)
	{
		return -1;
	}
//	int intHighFourBits = 0;
//	int intLowFourBits = 0;
	while (ASize--)
	{
//		intHighFourBits = *ANum >> 4;
//		intLowFourBits = *ANum & 0x0F;
		if ((*ANum >> 4) > 9 || (*ANum & 0x0F) > 9)
		{
			return -2;
		}
		ANum++;
	}
	return 0;
}
/**
 * 名称：L_ClearPreZero
 * 功能：去掉可能存在的前导0
 * 参数：ANum 输入参数，起始地址；
 * 		 ASize 输入参数，从ANum开始的字节数
 * 		 ANumOut 输出参数，表示第一个非0字节的地址
 * 		 ASizeOut 输出参数，表示去除前导0后从ANumOut开始的字节数
 * 返回值：
 *       -1  参数不合法
 *       0   正常结束
 * 备注：
 * 		 无
 */
static int L_ClearPreZero(const Byte* ANum, int ASize, const Byte** ANumOut,
		int* ASizeOut)
{
	if (NULL == ANum || ASize <= 0 || NULL == ANumOut || NULL == ASizeOut)
	{
		return -1;
	}
	while (ASize--)
	{
		if (0 != *ANum)
		{
			*ANumOut = ANum;
			*ASizeOut = ASize + 1;
			return 0;
		}
		else
		{
			ANum++;
		}
	}
	return 0;
}
/**
 * 名称：L_AddTwoBCD
 * 功能：去掉可能存在的前导0
 * 参数：ANum1 输入参数，表示一个BCD数
 * 		 ANum2 输入参数，表示一个BCD数
 * 		 ADest 输出参数，用来存储相加后的结果
 * 		 ACarryFlag 输出参数，用来存储相加后的进位
 * 返回值：
 *       -1  参数不合法
 *       0   正常结束
 * 备注：
 * 		 无
 */
static int L_AddTwoBCD(Byte ANum1, Byte ANum2, Byte* ADest, int* ACarryFlag)
{
	if (NULL == ADest || NULL == ACarryFlag)
	{
		return -1;
	}
	int intTmp = (ANum1 & 0x0F) + (ANum2 & 0x0F) + *ACarryFlag;
	if (intTmp > 9)
	{
		*ADest = intTmp - 10;
		*ACarryFlag = 1;
	}
	else
	{
		*ADest = intTmp;
		*ACarryFlag = 0;
	}
	intTmp = (ANum1 >> 4) + (ANum2 >> 4) + *ACarryFlag;
	if (intTmp > 9)
	{
		*ADest |= (intTmp - 10) << 4;
		*ACarryFlag = 1;
	}
	else
	{
		*ADest |= intTmp << 4;
		*ACarryFlag = 0;
	}
	return 0;
}

