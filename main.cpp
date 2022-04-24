#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;
using namespace biginteger;

int main()
{
    bigint a = 2;
    bigint b = pow(a, 345679876543456789876544567878654567898765456789897654456789987654456789876545678_bi, 37);
    cout << b << endl;
    return 0;
}
