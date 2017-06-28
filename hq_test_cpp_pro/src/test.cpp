/**
 * AddBCDInt.cpp
 * ������ʵ�����������������BCD�����֮��
 * ���ߣ�����
 * �汾��4.0
 * ��ע�����ĵ�ȫ���õĿո�����
 * �޶���¼��
 *      2017/6/17    1.0    ����    �����ļ�
 *      2017/6/23    2.0/3.0����    ����ģ�黯��������׼��,����������֯
 *      2017/6/26    4.0    ����    �޸�bug���Ż��������Ч��
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef unsigned char Byte;
//��������
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
    // �������Ƿ�Ϸ�
    if (NULL == ANum1 || NULL == ANum2 || NULL == ADest || ASize <= 0 || ASize1 <= 0 || ASize2 <= 0)
        return -3;
    if (!L_CheckCharactor(ANum1, ASize1)) return -1;
    if (!L_CheckCharactor(ANum2, ASize2)) return -2;

    int intSize1 = 0;                                            // �����洢��pNum1��ʼ���ֽ���
    int intSize2 = 0;                                            // �����洢��pNum1��ʼ���ֽ���
    const Byte* pNum1 = L_ClearPreZero(ANum1, ASize1, intSize1); // �����洢ASize1�ĵ�һ����0�ֽڵĵ�ַ
    const Byte* pNum2 = L_ClearPreZero(ANum2, ASize2, intSize2); // �����洢ASize2�ĵ�һ����0�ֽڵĵ�ַ
    int intMinSize = intSize1;                                   // �洢��С����
    int intOffLength = intSize2 - intSize1;                      // ����ƫ��ֵ��Ҳ���ǲ�ֵ
    int intResultLength = intSize2;                              // �洢�������
    /**
     * ע��
     * intCarryFlag,��ֵû�н�λ��0���н�λ��1����Ȼ��byte��bool
     * �Ϳ��Դ洢���ҽ�ʡ�����ֽڵĿռ䣬����int���ͺʹ�����λ��
     * һ�£�Ч�ʱ�byte�ߣ�֮ǰ�������ɵĻ�࣬����byteҪ��Լ2��ָ
     * �������������ᱻƵ�����ʣ�����Ӧ�û���ִ�кܶ������ָ��ġ�
     */
    int intCarryFlag = 0;                                        //��ʾ��λ
    // Ԥ����
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

    // ��һ�μ��Ŀ��ռ��Ƿ���
    if (ASize < intResultLength)  return 0;

    // �ƶ�ָ����ĩβ�����Ҷ��ƶ�1
    Byte* pDest = ADest + intResultLength;
    pNum1 += intSize1;
    pNum2 += intSize2;
    while (intMinSize--)
    {
        pDest--, pNum1--, pNum2--;
        L_AddTwoBCD(*pNum1, *pNum2, *pDest, intCarryFlag);
    }

    // pNum2ָ��ȥ��ǰ��0��ϳ��Ĵ����������¶���һ��byteָ��
    if (intSize1 > intSize2) pNum2 = pNum1;

    // ����ϳ��Ĵ��ж�����Ĳ���
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
        // ����н�λ,����Ҫһ���ֽڿռ䣬�ٴμ��Ŀ��ռ��Ƿ���
        if (ASize == intResultLength) return 0;
        memmove(ADest + 1, pDest, intResultLength);
        *ADest = 1;
        intResultLength++;
    }
    return intResultLength;
}

/**
* ���ƣ�L_CheckCharactor
* ���ܣ�����Ƿ��зǷ��ַ�
* ������ANum  �����������ʼ��ַ��
*       ASize �����������ANum��ʼ���ֽ���
* ���أ�
*       false ���ڷǷ�ֵ
*       true  ��������
* ��ע��
*       ��
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
 * ���ƣ�L_ClearPreZero
 * ���ܣ�ȥ�����ܴ��ڵ�ǰ��0
 * ������ANum �����������ʼ��ַ��
 *       ASize �����������ANum��ʼ���ֽ���
 *       ASizeOut �����������ʾ�ӵ�һ����0�ֽڿ�ʼ���ֽ���
 * ���أ�
 *       ��ʾ��һ����0�ֽڵĵ�ַ
 * ��ע��
 *       ��
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
 * ���ƣ�L_AddTwoBCD
 * ���ܣ�ȥ�����ܴ��ڵ�ǰ��0
 * ������ANum1 �����������ʾһ��BCD��
 *       ANum2 �����������ʾһ��BCD��
 *       ADest ��������������洢��Ӻ�Ľ��
 *       ACarryFlag ��������������洢��Ӻ�Ľ�λ
 * ���أ�
 *       ��
 * ��ע��
 *       ��
 */
static void L_AddTwoBCD(Byte ANum1, Byte ANum2, Byte& ADest, int& ACarryFlag)
{
    // �������λ
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
    // �������λ
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
