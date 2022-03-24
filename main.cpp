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
    bigint a = 124;
    bigint b = 253;
    a -= b;
    cout << a << endl;
    return 0;
}
