#include <iostream>
#include "bigint/bigint.h"

using namespace std;

int main()
{
    //bigint a = 1260257;
    //bigint b = 37;
    bigint a = ((size_t) 1 << 31);
    a *= 2;
    bigint b = 7;
    cout << (a / b) << endl;
    cout << a * (a / b) << endl;
    bigint c = a % b;
    cout << c << endl;
    return 0;
}
