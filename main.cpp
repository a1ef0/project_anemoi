#include <iostream>
#include "bigint/bigint.h"
#include "bigint/functions.h"
using namespace std;
using namespace biginteger;

int main() {
    bigint a = 100;
    for (int i = 1; i < 100; ++i){
        cout << a % i << " = " << a << " - (" << a / i << " * " << i << ')' << endl;
    }
    return 0;
}
