#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <windows.h>


//#define NDEBUG_MODE
const float EPS = 0.01;


//!@mainpage
//! @c a

enum NUM_ROOTS {
    ZERO = 0,
    ONE  = 1,
    TWO  = 2,
    INF  = 10
};

enum ERRORS {
    ERR_FILE_NOT_FOUND = 1
};


/*!
\brief checks whether float numbers are in epsilon vicinity (float comparison)
*/
int check_equal (float a, float b);



/*!
 *   \brief outputs the roots of the equation to the console
 *   \param[in] num_roots - quantity of roots of the equation,
 *   \param[in] x1, x2 - possible roots of the quadratic equation
 */
void output_roots (int num_roots, float x1, float x2);




/*!
\brief finds the roots of the linear equation
\param[in] a, b, c - coefficients of the equation
\param[in] x1, x2 - pointers on possible roots of the quadratic equation
\return number of roots of the given linear equation(ZERO, ONE, INF)
*/
int linear_solve (float a, float b, float c, float *x1, float *x2);


/*!
\brief finds the roots of the given quadratic equation
\param[in] a, b, c - coefficients of the quadratic equation
\param[in] x1, x2 - pointers on possible roots of the quadratic equation
\return the number of roots of the given quadratic equation(ZERO, ONE, TWO)
*/
int quadratic_solve (float a, float b, float c, float *x1, float *x2);



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

