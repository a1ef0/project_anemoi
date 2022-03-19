#include <iostream>
#include <vector>
#include "bigint/big_integer.h"

using namespace std;

int main()
{
    //int a = -12312312;
    //char a = 123;
    //bool a = false;
    //short a = -12312;
    //float a = -123123.123;
    //uint a = 123456789;
    bigint a;
    bigint b(1235);
    cout << a << " " << b << endl;
    cout << (b >= a) << endl;
    return 0;
}
