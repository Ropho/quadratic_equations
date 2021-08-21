/*!
@brief Library with useful functions for solving quadratic and linear equations and some more
================================================================================================

@note coeffs and answers of the equation can be real numbers, u can get 0, 1, 2 and infinite number of roots

*/
//=======================================================================================================


#ifndef FUNCTIONS_H
#define FUNCTIOS_H


#include "stdio.h"
#include "math.h"
#include "string.h"
#include "locale.h"
#include "assert.h"
#include "TXLib.h"

//! the constant used in comparison of double numbers
const double EPS = 0.01;

//! determines used number (word) with its number in the program
enum NUM_ROOTS {
    ZERO = 0,
    ONE  = 1,
    TWO  = 2,
    INF  = 10
};

//! determines used color with its number in the program
enum ConsoleColor
{
        Black         = 0,
        Blue          = 1,
        Green         = 2,
        Cyan          = 3,
        Red           = 4,
        Magenta       = 5,
        Brown         = 6,
        LightGray     = 7,
        DarkGray      = 8,
        LightBlue     = 9,
        LightGreen    = 10,
        LightCyan     = 11,
        LightRed      = 12,
        LightMagenta  = 13,
        Yellow        = 14,
        White         = 15
};

/*!
    \brief changes the color of the text and background
    \param[in] text - desired color of the text
    \param[in] background - desired color of the background
*/
void SetColor (ConsoleColor text, ConsoleColor background);



/*!
    \brief checks whether double numbers are in epsilon vicinity (double comparison)
*/
int check_equal (double a, double b);


/*!
    \brief finds the roots of the linear equation
    \param[in] a, b, c - coefficients of the equation
    \param[in] x1, x2 - pointers on possible roots of the quadratic equation
    \return number of roots of the given linear equation(ZERO, ONE, INF)
*/
int linear_solve (double b, double c, double *x1, double *x2);


/*!
    \brief finds the roots of the given quadratic equation
    \param[in] a, b, c - coefficients of the quadratic equation
    \param[in] x1, x2 - pointers on possible roots of the quadratic equation
    \return the number of roots of the given quadratic equation(ZERO, ONE, TWO)
*/
int quadratic_solve (double a, double b, double c, double* x1, double *x2);


#endif // FUNCTIONS_H
