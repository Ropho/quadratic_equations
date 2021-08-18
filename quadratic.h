#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <assert.h>



#define NDEBUG_MODE


/*!
\brief checks whether float numbers are in epsilon vicinity (float comparison)
*/
int check(float a, float b);




/*!
\brief input numbers via console
\param[in] a, b, c - pointers on coeffs. of the initial quadratic equation
\returns either 1 - incorrect symbol read or 0 - correct
*/
int input(float *a, float *b, float *c);




/*!
\brief outputs the roots of the equation to the console
\param[in] kol - quantity of roots of the initial equation,
\param[in] x1, x2 - possible roots of the initial quadratic equation
*/
void output(int kol, float x1, float x2);




/*!
\brief finds the roots of the linear equation
\param[in] a, b, c - coefficients of the initial equation
\param[in] x1, x2 - pointers on possible roots of the initial quadratic equation
\returns number of roots of the given linear equation(ZERO, ONE, INF)
*/
int linear(float a, float b, float c, float *x1, float *x2);


/*!
\brief finds the roots of the given quadratic equation
\param[in] a, b, c - coefficients of the initial quadratic equation
\param[in] x1, x2 - pointers on possible roots of the initial quadratic equation
\returns the number of roots of the given quadratic equation(ZERO, ONE, TWO)
*/
int quadratic(float a, float b, float c, float *x1, float *x2);



 /*!
 \brief inputs a, b, c (coeffs. of the initial equation) from the given file)
 \param[in] a, b, c - pointers on the coeffs. of the initial quadratic equation
 \param[in] in - pointer on the given file
 \returns either 1 - incorrect symbol read or 0 - correct
 */
int input_f(float *a, float *b, float *c, FILE *in);




