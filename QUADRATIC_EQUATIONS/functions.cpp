#include "functions.h"


void SetColor (ConsoleColor text, ConsoleColor background) {

   HANDLE hStdout = GetStdHandle (STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute (hStdout, (WORD)((background << 4) | text));
}


int check_equal (float a, float b) {

    return fabs (a - b) < EPS;
}



int linear_solve (float a, float b, float c, float *x1, float *x2) {

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (check_equal (b, 0)){

        if (check_equal (c, 0))
            return INF;

        else
            return ZERO;
    }

    else {

        *x1 = -c / b;
        *x2 = *x1;

        return ONE;
    }
}


int quadratic_solve (float a, float b, float c, float *x1, float *x2) {

    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (check_equal (a, 0))
        return linear_solve (a, b, c, x1, x2);

    else if (c == 0) {

        linear_solve (c , a , b , x1 , x2);
        *x1 = 0;

        return TWO;
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

            float sqr_root = sqrt (discriminant);
            *x1 = (sqr_root - b) / (2 * a);
            *x2 = (-sqr_root - b) / (2 * a);

            return TWO;
        }
    }
}
