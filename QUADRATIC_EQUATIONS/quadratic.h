/*!
@mainpage HELLO, USERS OF THE "QUADRATIC EQUATIONS" PROGRAM
================================================================================================

1. TO USE THE PROGRAM TYPE IN 3 COEFFICEINTS @c a, @c b, @c c OF THE QUADRATIC EQUATION ax^2+bx+c=0 and get ur roots

2. TO STOP THE PROGRAM JUST TYPE IN NON-DIGIT.

3. TO DEBUG COMMENT "#define NDEBUG_MODE" AND WRITE IN THE FILE "input.txt" 3 coeffs of the equation,
                number of roots and possible roots. IF THE TEST WAS PASSED THE PROGRAM PRINTS "GOOD" ELSE "BAD"

*/
//=======================================================================================================


#ifndef QUDRATIC_H
#define QUADRATIC_H


#include "stdio.h"
#include "math.h"
#include "string.h"
#include "locale.h"
#include "assert.h"
#include "TXLib.h"

//! if commented u enter debug mode and 're able to use unit-tests from the file, otherwise standard console input
#define NDEBUG_MODE


//! determines used errors with a number
enum ERRORS {
    ERR_FILE_NOT_FOUND = 1
};


/*!
    \brief outputs the roots of the equation to the console
    \param[in] num_roots - quantity of roots of the equation,
    \param[in] x1, x2 - possible roots of the quadratic equation
 */
void output_roots (int num_roots, float x1, float x2);


/*!
    \brief inputs a, b, c (coeffs. of the equation) from the given file and compares the answer in the test with a answer from the program)
    \param[in] a, b, c - pointers on the coeffs. of the quadratic equation
    \param[in] in - pointer on the given file
    \return either 1 - incorrect symbol read or 0 - correct
 */
int input_coeffs_file (float *a, float *b, float *c, FILE *in);


/*!
    \brief inputs, calculates and prints in the console roots of the given in the file quadratic equation
    \param[in] in - pointer on the file
*/
void quadratic_test (FILE *in);


#endif // QUDRATIC_H
