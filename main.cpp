#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;
using namespace biginteger;

int main() {
    for (int i = 2; i < 100; ++i) {
        cout << i << ' ' << is_prime(i, 50) << '\n';
    }
    return 0;
}
