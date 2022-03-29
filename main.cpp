#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;

int main()
{
    bigint a = 5;
    bigint b = biginteger::pow(a, -1, 37);
    cout << b << endl;
    return 0;
}
