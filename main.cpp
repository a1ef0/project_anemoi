#include <cln/io.h>
#include <cln/integer_io.h>

#include "helper_functions.h"

using namespace std;
using namespace cln;

int main() {
    cl_I a = 2;
    cout << anemoi::pow<cl_I>(a, 1000000) << endl;
    return 0;
}
