#include <cln/io.h>
#include <cln/integer_io.h>

#include "helper_functions.h"

using namespace std;
using namespace cln;

int main() {
    cl_I a = 2;
    auto ans = anemoi::pow<cl_I>(11, -1, 13);
    cout << ans << endl;
    return 0;
}
