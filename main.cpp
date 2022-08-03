#include <cln/io.h>
#include <cln/integer_io.h>

#include "basic_functions.h"

using namespace std;
using namespace cln;

int main() {
    //cl_I a = 2;
    //auto ans = anemoi::pow(11, -1, 13);
    //cout << ans << endl;
    //cout << anemoi::ord(9704, 17389, anemoi::slow_factorize) << endl;
    //cout << anemoi::shanks_babystep_giantstep(2, 13896, 17389) << endl;
    vector<cl_I> ms = {3, 7, 16};
    vector<cl_I> as = {2, 3, 4};
    cout << anemoi::solve_crt(as, ms, 3) << endl;
    return 0;
}
