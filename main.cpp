#include <iostream>
#include "bigint/bigint.h"

using namespace std;

int main()
{
    bigint a = 1260257;
    bigint b = 37;
    bigint c = a / b;
    cout << c << endl;
    return 0;
}
