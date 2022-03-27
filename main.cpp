#include <iostream>
#include "bigint/bigint.h"

using namespace std;

int main()
{
    //int a = -12312312;
    //char a = 123;
    //bool a = false;
    //short a = -12312;
    //float a = -123123.123;
    //uint a = 123456789;
    bigint a = 214748323452345648;
    bigint b = 1231232345234123123;

    cout << a << ' ' << b << ' ' << a*b << endl;
    return 0;
}
