#include <iostream>
#include "bigint/big_integer.h"

using namespace std;

int main()
{
    //bigint b{"1234567890123456789012345678901234567890234567892345678934567893456789345678934567893456789234567890234567892345678934567893456789023456789023456789034567893456789345678945678903456789"};
    //cout << b << endl;
    long long a = 987112123123;
    a = abs(a);
    uint lo = (a & 0xFFFFFFFF);
    cout << lo << endl;
    //uint hi = (a >> 32);
    unsigned long long hi = (a >> 32);
    long long b = ((hi << 32) + lo);
    cout << b << endl;

    return 0;
}
