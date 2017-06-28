#include "SXString.h"
using namespace SXLIB;
int main()
{
    SXString Str1 = "hello";
    SXString Str2; //""
    Str1.Display();
    Str2.Display();

    SXString Str3 = Str1+Str2+263+'k';
    Str3.Display();

    SXString Str4(Str1);
    Str4.Display();

    return 0;
}
