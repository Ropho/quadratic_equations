
//добавить цвета в ответ
#include "TXLib.h"
#include "quadratic.h"

int main (int argc, const char *argv[]) {



//добавить вначале автора, про программу
    printf ("ПРОГРАММА РЕШАЕТ....  АВТОР ГЕНИЙ!!! \n");



    #ifndef NDEBUG_MODE

    {
        FILE *input = fopen ("input.txt", "r");
        if (!input) {
            fprintf (stderr, "error (%s (%d) %s): file \"input.txt\" not found\n", __FILE__, __LINE__, __PRETTY_FUNCTION__); //perror

            return ERR_FILE_NOT_FOUND;
        }
        quadratic_test (input);
        fclose (input);
    }

    #else

        while (1) {
            printf ("input equation like a * x ^ 2 + b * x + c = 0\n");
            float a = 0, b = 0,c = 0, x1 = 0, x2 = 0;

            if (input_coeffs_file (&a, &b, &c, stdin) == 1) {
                printf ("Symbol not digit");
                return 0;
            }

            int num_roots = quadratic_solve (a, b, c, &x1 , &x2);
            output_roots (num_roots , x1 , x2);
        }

    #endif

    return 0;
}

void quadratic_test (FILE *in) {
    int num_lines = 0;
    fscanf (in, "%d ", &num_lines);

    for (int i = 0; i < num_lines; ++i) {
        float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

        if (input_coeffs_file (&a, &b, &c, in) == 1) {
            fprintf (stderr, "NON-DIGIT INPUT");
            break;
        }

        int num_roots = quadratic_solve (a, b, c, &x1, &x2);
        int ans_num_roots = 0;
        fscanf (in, "%d ", &ans_num_roots);

        switch (num_roots) {

            case ZERO: {
                if (ans_num_roots == ZERO) printf ("%d GOOD\n", i + 1);

                else                       printf ("%d BAD\n",  i + 1);

                break;
            }

            case ONE: {
                float root = 0;
                fscanf (in," %f", &root);
                int good = check_equal (x1, root);
                printf ("%d %s\n", i + 1, (good ? "GOOD" : "BAD"));

                break;
            }

            case TWO: {
                float root1 = 0, root2 = 0;
                fscanf (in," %f %f ", &root1, &root2);

                if ((check_equal (x1, root1) && check_equal (x2, root2)) ||
                    (check_equal (x1, root2) && check_equal (x2, root1)))
                    printf ("%d GOOD\n", i + 1);

                else
                    printf ("%d BAD\n", i + 1);

                break;
            }

            case INF: {

                if (ans_num_roots == INF)
                    printf ("%d GOOD\n", i + 1);

                else
                    printf ("%d BAD\n", i + 1);

                break;
            }

            default:

                break;
        }
    }
}





int check_equal (float a, float b) {

    return fabs (a - b) < EPS;

}


int input_coeffs_file (float *a, float *b, float *c, FILE *in) {

    assert (in != NULL);
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);
    assert (! (a == b || b == c || a == c));

    return (fscanf (in,"%f %f %f", a, b, c) != 3);
}

void output_roots (int num_roots, float x1, float x2) {

    switch (num_roots) {

        case INF: {

            printf ("INF\n");

            break;
        }

        case ZERO: {

            printf ("ZERO roots\n");

            break;
        }

        case ONE: {

            if (!check_equal (x1, 0))      //one root for elves
                printf ("x == %.2f\n", x1);

            else
                printf ("x == 0\n");
                                   //second root for dwarves
            break;
        }

        case TWO:{

            if (check_equal (x1, 0) && !check_equal (x2, 0))
                printf ("x1 == 0 \t x2 == %.2f\n", x2);

            else if (!check_equal (x1 ,0) && check_equal (x2, 0))
                printf ("x1 == %.2f \t x2 == 0\n", x1);

            else
                printf ("x1 == %.2f \t x2 == %.2f\n", x1, x2);

            break;
        }

        default:

            break;
    }
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


