#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;
using namespace biginteger;

int main() {
    bigint a;
    for (bigint i = 2; i < 100; ++i) {
        //a = biginteger::get_prime(5);
        //cout << a << endl;
        cout << i << ' ' << get_prime(8) << endl;
        //is_prime(i);
    }
    return 0;
}
//TODO: Check << ostream operator
