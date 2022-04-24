#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;
using namespace biginteger;

int main()
{
    bigint a = 2;
    bigint b = pow(a, 1120000);
    cout << b << endl;
    return 0;
}
