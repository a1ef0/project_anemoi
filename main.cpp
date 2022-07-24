#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"

using namespace biginteger;

using namespace std;

int main() {

    for (int i = 2; i < 100; ++i) {
        cout << i << ' ' << is_prime(i, 100) << '\n';
    }

    return 0;
}
