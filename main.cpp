#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;
using namespace biginteger;

int main()
{
    bigint a = 2;
    bigint b = pow(a, 3456798765434567897_bi);
    cout << b << endl;
    return 0;
}
