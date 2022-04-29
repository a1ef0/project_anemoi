#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;
using namespace biginteger;

int main() {
    bigint a = 2;
    //bigint b = pow(a, 112045678987654678912342837469827634897321340_bi, 213124123_bi);
    //cout << b << endl;
    cout << random(a) << endl;
    return 0;
}
