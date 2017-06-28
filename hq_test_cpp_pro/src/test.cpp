/**
 * AddBCDInt.cpp
 * 概述：实现两个大的正整数（BCD）相加之和
 * 作者：孙兴
 * 版本：4.0
 * 备注：本文档全部用的空格缩进
 * 修订记录：
 *      2017/6/17    1.0    孙兴    创建文件
 *      2017/6/23    2.0/3.0孙兴    进行模块化，命名标准化,代码重新组织
 *      2017/6/26    4.0    孙兴    修复bug，优化程序，提高效率
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef unsigned char Byte;
//函数声明
static void L_AddTwoBCD(Byte ANum1, Byte ANum2, Byte& ADest, int& ACarryFlag);
static bool L_CheckCharactor(const Byte* ANum, int ASize);
static const Byte* L_ClearPreZero(const Byte* ANum, int ASize, int& ASizeOut);
int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2, Byte* ADest, int ASize);

int main0()
{
    Byte arrNum1[] = { 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34 };
    Byte arrNum2[] = { 0x09, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x87, 0x65, 0x43, 0x21 };
    //  Byte arrNum2[] = {0x00,0x00};
    const int intBufferLength = 12;
    Byte arrDest[intBufferLength];
    int intSize1 = sizeof(arrNum1);
    int intSize2 = sizeof(arrNum2);
    int intRet = AddBCDInt(arrNum1, intSize1, arrNum2, intSize2, arrDest, intBufferLength);
    printf("intRet: %d\n", intRet);
    for (int i = 0; i < intRet; i++)
        printf("%02x ", arrDest[i]);
    return 0;
}

int AddBCDInt(const Byte* ANum1, int ASize1, const Byte* ANum2, int ASize2, Byte* ADest, int ASize)
{
    // 检查参数是否合法
    if (NULL == ANum1 || NULL == ANum2 || NULL == ADest || ASize <= 0 || ASize1 <= 0 || ASize2 <= 0)
        return -3;
    if (!L_CheckCharactor(ANum1, ASize1)) return -1;
    if (!L_CheckCharactor(ANum2, ASize2)) return -2;

    int intSize1 = 0;                                            // 用来存储从pNum1开始的字节数
    int intSize2 = 0;                                            // 用来存储从pNum1开始的字节数
    const Byte* pNum1 = L_ClearPreZero(ANum1, ASize1, intSize1); // 用来存储ASize1的第一个非0字节的地址
    const Byte* pNum2 = L_ClearPreZero(ANum2, ASize2, intSize2); // 用来存储ASize2的第一个非0字节的地址
    int intMinSize = intSize1;                                   // 存储最小长度
    int intOffLength = intSize2 - intSize1;                      // 长度偏离值，也就是差值
    int intResultLength = intSize2;                              // 存储结果长度
    /**
     * 注：
     * intCarryFlag,其值没有进位是0，有进位是1。虽然用byte和bool
     * 就可以存储并且节省几个字节的空间，但是int类型和处理器位宽
     * 一致，效率比byte高（之前看过生成的汇编，比用byte要少约2条指
     * 令）由于这个变量会被频繁访问，所以应该会少执行很多条汇编指令的。
     */
    int intCarryFlag = 0;                                        //表示进位
    // 预处理
    if (intSize1 > intSize2)
    {
        intMinSize = intSize2;
        intOffLength = intSize1 - intSize2;
        intResultLength = intSize1;
    }
    else if (intSize1 == intSize2)
    {
        L_AddTwoBCD(*pNum1, *pNum2, *ADest, intCarryFlag);
        intResultLength += intCarryFlag;
    }

    // 第一次检查目标空间是否够用
    if (ASize < intResultLength)  return 0;

    // 移动指针至末尾，并且多移动1
    Byte* pDest = ADest + intResultLength;
    pNum1 += intSize1;
    pNum2 += intSize2;
    while (intMinSize--)
    {
        pDest--, pNum1--, pNum2--;
        L_AddTwoBCD(*pNum1, *pNum2, *pDest, intCarryFlag);
    }

    // pNum2指向去掉前导0后较长的串，避免重新定义一个byte指针
    if (intSize1 > intSize2) pNum2 = pNum1;

    // 处理较长的串中多出来的部分
    while(intOffLength)
    {
        if (!intCarryFlag)
        {
            memcpy(pDest - intOffLength, pNum2 - intOffLength, intOffLength);
            return intResultLength;
        }
        pNum2--, pDest--, intOffLength--;
        L_AddTwoBCD(*pNum2, 0, *pDest, intCarryFlag);
    }

    if (intCarryFlag)
    {
        // 最后有进位,还需要一个字节空间，再次检查目标空间是否够用
        if (ASize == intResultLength) return 0;
        memmove(ADest + 1, pDest, intResultLength);
        *ADest = 1;
        intResultLength++;
    }
    return intResultLength;
}

/**
* 名称：L_CheckCharactor
* 功能：检查是否有非法字符
* 参数：ANum  输入参数，起始地址；
*       ASize 输入参数，从ANum开始的字节数
* 返回：
*       false 存在非法值
*       true  正常结束
* 备注：
*       无
*/
static bool L_CheckCharactor(const Byte* ANum, int ASize)
{
    while (ASize--)
    {
        if ((*ANum >> 4) > 9 || (*ANum & 0x0F) > 9)
            return false;
        ANum++;
    }
    return true;
}
/**
 * 名称：L_ClearPreZero
 * 功能：去掉可能存在的前导0
 * 参数：ANum 输入参数，起始地址；
 *       ASize 输入参数，从ANum开始的字节数
 *       ASizeOut 输出参数，表示从第一个非0字节开始的字节数
 * 返回：
 *       表示第一个非0字节的地址
 * 备注：
 *       无
 */
static const Byte* L_ClearPreZero(const Byte* ANum, int ASize, int& ASizeOut)
{
    while (ASize--)
    {
        if (*ANum)
        {
            ASizeOut = ASize + 1;
            return ANum;
        }
        ANum++;
    }
    return ANum;
}
/**
 * 名称：L_AddTwoBCD
 * 功能：去掉可能存在的前导0
 * 参数：ANum1 输入参数，表示一个BCD数
 *       ANum2 输入参数，表示一个BCD数
 *       ADest 输出参数，用来存储相加后的结果
 *       ACarryFlag 输出参数，用来存储相加后的进位
 * 返回：
 *       无
 * 备注：
 *       无
 */
static void L_AddTwoBCD(Byte ANum1, Byte ANum2, Byte& ADest, int& ACarryFlag)
{
    // 处理低四位
    int intTmp = (ANum1 & 0x0F) + (ANum2 & 0x0F) + ACarryFlag;
    if (intTmp > 9)
    {
        ADest = intTmp - 10;
        ACarryFlag = 1;
    }
    else
    {
        ADest = intTmp;
        ACarryFlag = 0;
    }
    // 处理高四位
    intTmp = (ANum1 >> 4) + (ANum2 >> 4) + ACarryFlag;
    if (intTmp > 9)
    {
        ADest |= (intTmp - 10) << 4;
        ACarryFlag = 1;
    }
    else
    {
        ADest |= intTmp << 4;
        ACarryFlag = 0;
    }
}
