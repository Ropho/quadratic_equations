#include "functions.h"


void SetColor (ConsoleColor text, ConsoleColor background) {

   HANDLE hStdout = GetStdHandle (STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute (hStdout, (WORD)((background << 4) | text));
}


int check_equal (float a, float b) {

    assert (!isnan(a));
    assert (!isnan(b));

    return fabs (a - b) < EPS;
}



int linear_solve (float b, float c, float *x1) {

    assert (x1 != NULL);

    assert (!isnan(b));
    assert (!isnan(c));

    if (check_equal (b, 0)){

        if (check_equal (c, 0))
            return INF;

        else
            return ZERO;
    }

    else {

        *x1 = -c / b;

        return ONE;
    }
}


int quadratic_solve (float a, float b, float c, float *x1, float *x2) {

    assert (!isnan(a));
    assert (!isnan(b));
    assert (!isnan(c));

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (check_equal (a, 0))
        return linear_solve (b, c, x1);


    else if (check_equal(c , 0)) {

        *x1 = 0;
        int num_lin_roots = linear_solve (a , b , x2);

        switch (num_lin_roots) {

           case ZERO:
                return ONE;

                break;

           case ONE:
                if (check_equal (*x1, *x2))
                    return ONE;
                else
                    return TWO;

                break;

           case INF:
                return INF;

                break;

           default:
               return INF;

                break;
        }

    }

    else {

        float discriminant = (b * b) - (4 * a * c);

        if (discriminant < 0)
            return ZERO;

        else if (check_equal (discriminant, 0)) {

            *x1 =  -b / (2 * a);

            return ONE;
        }

        else {

            discriminant = sqrt (discriminant);
            a = 2 * a;

            // "discriminant" and "a" values were changed to fasten the program
            *x1 = (-b + discriminant) / a;
            *x2 = (-b - discriminant) / a;

            return TWO;
        }
    }
}
