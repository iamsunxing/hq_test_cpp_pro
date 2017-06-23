/**
 * AddBCDInt.cpp
 *
 *
 *
 * 概述：实现两个大的正整数相加之和
 * 作者：孙兴
 * 版本：1.0
 * 注意事项：无
 * 修订记录：
 * 		2017/6/17		孙兴			创建文件
 */
/*
 #include <iostream>
 #include <cstdlib>
 #include <cstdio>
 using namespace std;
 typedef unsigned char Byte;
 int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2,
 Byte* ADest, int ASize);

 int main()
 {
 Byte num1[] =
 { 0x00, 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34 };
 Byte num2[] =
 { 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x87, 0x65, 0x43, 0x21 };
 //  Byte num1[]={0x95};
 //  Byte num2[]={0x45};
 //  Byte num2[]={};
 const int num3_length = 30;
 Byte num3[num3_length] = { 0 };
 int num1_size = sizeof(num1) / sizeof(Byte);
 int num2_size = sizeof(num2) / sizeof(Byte);
 int ret = AddBCDInt(num1, num1_size, num2, num2_size, num3, num3_length);
 printf("%d\n", ret);
 for (int i = 0; i < ret; i++)
 {
 printf("%02x", num3[i]);
 }
 return 0;
 }

 int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2,
 Byte* ADest, int ASize)
 {
 // 参数有效性检查
 if (ASize1 <= 0 || ASize2 <= 0 || ASize <= 0 || NULL == ANum1
 || NULL == ANum2)
 {
 return -3;
 }

 const Byte *pANum1_trim = NULL;
 const Byte *pANum2_trim = NULL;
 int ASize1_trim = 0;
 int ASize2_trim = 0;

 for (int i = 0, flag = 0; i < ASize1; i++)
 {
 // 检查是否有非法字符
 if ((ANum1[i] >> 4) < 0 || (ANum1[i] >> 4) > 9 || (ANum1[i] & 0x0f) < 0
 || (ANum1[i] & 0x0f) > 9)
 {
 return -1;
 }
 // 去除数组可能存在的若干个前导0
 if (ANum1[i] != 0 && 0 == flag)
 {
 pANum1_trim = &ANum1[i];
 ASize1_trim = ASize1 - i;
 flag = 1;
 }
 }

 for (int i = 0, flag = 0; i < ASize2; i++)
 {
 // 检查是否有非法字符
 if ((ANum2[i] >> 4) < 0 || (ANum2[i] >> 4) > 9 || (ANum2[i] & 0x0f) < 0
 || (ANum2[i] & 0x0f) > 9)
 {
 return -2;
 }
 // 去除数组可能存在的若干个前导0
 if (ANum2[i] != 0 && 0 == flag)
 {
 pANum2_trim = &ANum2[i];
 ASize2_trim = ASize2 - i;
 flag = 1;
 }
 }

 // 获取结果的长度
 int max_size = (ASize2_trim > ASize1_trim) ? ASize2_trim : ASize1_trim;
 int result_length = max_size;
 for (int i = 0; i < max_size; i++)
 {
 // 处理字节的高四位
 int index1 = ASize1_trim - max_size + i;
 int index2 = ASize2_trim - max_size + i;
 Byte tmp_sum = (index1 < 0 ? 0 : pANum1_trim[index1] >> 4)
 + (index2 < 0 ? 0 : pANum2_trim[index2] >> 4);
 if (tmp_sum > 9)
 {
 result_length++;
 break;
 }
 else if (tmp_sum < 9)
 {
 break;
 }
 else if (9 == tmp_sum)
 {
 // 处理字节的低四位
 index1 = ASize1_trim - max_size + i;
 index2 = ASize2_trim - max_size + i;
 tmp_sum = (index1 < 0 ? 0 : pANum1_trim[index1] & 0x0f)
 + (index2 < 0 ? 0 : pANum2_trim[index2] & 0x0f);
 if (tmp_sum > 9)
 {
 result_length++;
 break;
 }
 else if (tmp_sum < 9)
 {
 break;
 }
 }
 }

 // 检查输出缓冲区是否足够大
 if (ASize < result_length)
 {
 return 0;
 }

 Byte flag = 0; // 进位
 for (int i = ASize1_trim - 1, j = ASize2_trim - 1, k = result_length - 1,
 cnt = 0; cnt < max_size || 1 == flag; cnt++)
 {
 if (i < 0 && j < 0 && 0 == flag)
 {
 break;
 }
 ADest[k] = 0;
 // 处理字节的低四位
 Byte tmp_sum = (i < 0 ? 0 : pANum1_trim[i] & 0x0f)
 + (j < 0 ? 0 : pANum2_trim[j] & 0x0f) + flag;
 flag = 0;
 if (tmp_sum > 9)
 {
 ADest[k] |= tmp_sum - 10;
 flag = 1;
 }
 else
 {
 ADest[k] |= tmp_sum;
 }
 // 处理字节的高四位
 tmp_sum = ((i < 0) ? 0 : pANum1_trim[i] >> 4)
 + ((j < 0) ? 0 : pANum2_trim[j] >> 4) + flag;
 flag = 0;
 if (tmp_sum > 9)
 {
 if (0 == k)
 {
 return 0;
 }
 ADest[k] |= (tmp_sum - 10) << 4;
 flag = 1;
 }
 else
 {
 ADest[k] |= tmp_sum << 4;
 }
 i--, j--, k--;
 }
 return result_length;
 }
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef unsigned char Byte;
int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2,
		Byte* ADest, int ASize);
int main()
{
	Byte arrNum1[] =
	{             0x00, 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34 };
	Byte arrNum2[] =
	{ 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x87, 0x65, 0x43, 0x21 };
	const int ResultLength = 30;
	Byte arrDest[ResultLength];
	int Size1 = sizeof(arrNum1) / sizeof(Byte);
	int Size2 = sizeof(arrNum2) / sizeof(Byte);
	int Ret = AddBCDInt(arrNum1, Size1, arrNum2, Size2, arrDest, ResultLength);
	printf("%d\n", Ret);
	for (int i = 0; i < Ret; i++)
	{
		printf("%02x ", arrDest[i]);
	}
	return 0;
}
/**
 * 功能：检查是否有非法字符
 * 参数不合法返回 -1
 * 有非法字符返回 -2
 * 否则正常返回       0
 */
static int L_CheckCharactor(const Byte* ANum, int ASize)
{
	if (NULL == ANum || ASize <= 0)
	{
		return -1;
	}
	int HighFourBits = 0;
	int LowFourBits = 0;
	while (ASize--)
	{
		HighFourBits = *ANum >> 4;
		LowFourBits = *ANum & 0x0F;
		if (HighFourBits > 9 || LowFourBits > 9)
		{
			return -2;
		}
		ANum++;
	}
	return 0;
}
/**
 * 功能：去掉前面可能存在的0
 * 参数不合法返回 -1
 * 否则正常返回      0
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
int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2,
		Byte* ADest, int ASize)
{
	if (NULL == ANum1 || NULL == ANum2 || NULL == ADest || ASize <= 0
			|| ASize1 <= 0 || ASize2 <= 0)
	{
		return -3;
	}

	const Byte* pNum1 = NULL;
	const Byte* pNum2 = NULL;
	int Size1 = 0;
	int Size2 = 0;

	int Tmp = L_CheckCharactor(ANum1, ASize1);
	if (-1 == Tmp)
	{
		return -3;
	}
	else if (-2 == Tmp)
	{
		return -1;
	}
	Tmp = L_CheckCharactor(ANum2, ASize2);
	if (-1 == Tmp)
	{
		return -3;
	}
	else if (-2 == Tmp)
	{
		return -2;
	}

	Tmp = L_ClearPreZero(ANum1, ASize1, &pNum1, &Size1);
	if (-1 == Tmp)
	{
		return -3;
	}
	Tmp = L_ClearPreZero(ANum2, ASize2, &pNum2, &Size2);
	if (-1 == Tmp)
	{
		return -3;
	}

	int CarryFlag = 0;

	pNum1 += Size1;
	pNum2 += Size2;

	int MinSize = Size1;
	int MaxSize = Size2;
	int ResultLength = Size2;
	if (Size1 > Size2)
	{
		MinSize = Size2;
		MaxSize = Size1;
		ResultLength = Size1;
	}
	else if (Size1 == Size2)
	{
		Tmp = (*pNum1 >> 4) + (*pNum2 >> 4);
		if (Tmp > 0x99)
		{
			ResultLength++;
		}
	}
	Byte* pDest = ADest;
	pDest += ResultLength;
	for (int i = 0; i < MinSize; i++)
	{
		--pDest, --pNum1, --pNum2;
		Tmp = (*pNum1 & 0x0F) + (*pNum2 & 0x0F) + CarryFlag;
		if (Tmp > 9)
		{
			*pDest = Tmp - 10;
			CarryFlag = 1;
		}
		else
		{
			*pDest = Tmp;
			CarryFlag = 0;
		}
		Tmp = (*pNum1 >> 4) + (*pNum2 >> 4) + CarryFlag;
		if (Tmp > 9)
		{
			*pDest |= (Tmp - 10) << 4;
			CarryFlag = 1;
		}
		else
		{
			*pDest |= Tmp << 4;
			CarryFlag = 0;
		}
	}

	if (Size1 > Size2)
	{
		for (int i = MinSize; i < MaxSize; i++)
		{
			--pDest,--pNum1;
			Tmp = (*pNum1 & 0x0F) + CarryFlag;
			if (Tmp > 9)
			{
				*pDest = Tmp - 10;
				CarryFlag = 1;
			}else
			{
				*pDest = Tmp;
				CarryFlag = 0;
			}

			Tmp = (*pNum1 >> 4) + CarryFlag;
			if (Tmp > 9)
			{
				*pDest |= (Tmp - 10) << 4;
				CarryFlag = 1;
			}else
			{
				*pDest |= Tmp << 4;
				CarryFlag = 0;
			}
		}
	}else if(Size1 < Size2)
	{
		for (int i = MinSize; i < MaxSize; i++)
		{
			--pDest,--pNum2;
			Tmp = (*pNum2 & 0x0F) + CarryFlag;
			if (Tmp > 9)
			{
				*pDest = Tmp - 10;
				CarryFlag = 1;
			}else
			{
				*pDest = Tmp;
				CarryFlag = 0;
			}

			Tmp = (*pNum2 >> 4) + CarryFlag;
			if (Tmp > 9)
			{
				*pDest |= (Tmp - 10) << 4;
				CarryFlag = 1;
			}else
			{
				*pDest |= Tmp << 4;
				CarryFlag = 0;
			}
		}
	}

	if (1 == CarryFlag)
	{
		memmove(ADest+1,pDest,ResultLength);
		*ADest = 1;
		ResultLength++;
	}
	return ResultLength;
}
/*
 * 10 00 00 00 12345666555555
 */
