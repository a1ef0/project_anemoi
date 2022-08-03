#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

#include <cln/integer.h>
#include <cln/real.h>
#include <set>
#include <map>
#include <vector>

/**
 * The namespace itself contains all needed primitives & functions and acts like the standalone library.
 */
namespace anemoi {

const cln::cl_I MINUS_ONE = cln::cl_I(-1);

/**
 * @brief pow   - performs the exponentiation
 * @param base  - integer base for exponentiation
 * @param exp   - integer exponent for exponentiation
 * @return base ^ exp (not XOR, but exponentiation)
 */
cln::cl_I pow(cln::cl_I base, cln::cl_I exp);

/**
 * @brief pow   - performs the exponentiation given modulo mod
 * @param base  - integer base for exponentiation
 * @param exp   - integer exponent for exponentiation
 * @param p     - modulo, on which the operation is performed
 * @return base ^ exp (mod p)
 */
cln::cl_I pow(cln::cl_I base, cln::cl_I exp, const cln::cl_I& p);

/**
 * @brief slow_factorize    - performs integer factorisation on a given positive number
 * @param number            - number to be factored
 * @return set of factors
 */
std::set<cln::cl_I> slow_factorize(cln::cl_I number);

/**
 * @brief ord       - returns order of element in given group (in this case it is F^*_p)
 * @param element   - element to be found order of
 * @param mod       - modulo of given Field
 * @return order of element
 */
cln::cl_I ord(cln::cl_I element, cln::cl_I mod, std::set<cln::cl_I>(*factorize)(cln::cl_I number));

/**
 * @brief shanks_babystep_giantstep - solves DLP for a given base, modulus and logarithm.
 * @param g                         - base
 * @param h                         - logarithm
 * @param p                         - modulus
 * @return integer solution to DLP
 */
cln::cl_I shanks_babystep_giantstep(cln::cl_I g, cln::cl_I h, cln::cl_I p);

}

#endif // BASIC_FUNCTIONS_H
