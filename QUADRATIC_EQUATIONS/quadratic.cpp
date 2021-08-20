#include "functions.h"
#include "quadratic.h"

int main (int argc, const char *argv[]) {


    #ifndef NDEBUG_MODE


        FILE *input = fopen ("input.txt", "r");

        if (!input) {

            SetColor(White, Black);

            fprintf (stderr, "error (%s (%d) %s): file \"input.txt\" not found\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);

            return ERR_FILE_NOT_FOUND;
        }
        quadratic_test (input);
        fclose (input);


    #else


        SetColor(White, Black);

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

            SetColor (White , Black);
            fprintf (stderr, "NON-DIGIT INPUT");

            break;
        }

        int num_roots = quadratic_solve (a, b, c, &x1, &x2);
        int ans_num_roots = 0;
        fscanf (in, "%d ", &ans_num_roots);

        switch (num_roots) {

            case ZERO: {

                if (ans_num_roots == ZERO) {

                    SetColor (LightGreen, Black);
                    printf ("%d GOOD\n", i + 1);
                }

                else {

                    SetColor (LightRed, Black);
                    printf ("%d BAD\n", i + 1);
                }

                break;
            }

            case ONE: {

                float root = 0;
                fscanf (in," %f", &root);
                int good = check_equal (x1, root);

                if (good) {

                    SetColor (LightGreen, Black);
                    printf ("%d GOOD\n", i + 1);
                }
                else {

                    SetColor (LightRed, Black);
                    printf ("%d BAD\n", i + 1);
                }

                break;
            }

            case TWO: {

                float root1 = 0, root2 = 0;
                fscanf (in," %f %f ", &root1, &root2);

                if ((check_equal (x1, root1) && check_equal (x2, root2)) ||
                    (check_equal (x1, root2) && check_equal (x2, root1))) {

                    SetColor (LightGreen, Black);
                    printf ("%d GOOD\n", i + 1);
                }

                else
                    {

                    SetColor (LightRed, Black);
                    printf ("%d BAD\n", i + 1);
                }

                break;
            }

            case INF: {

                if (ans_num_roots == INF) {

                    SetColor (LightGreen, Black);
                    printf ("%d GOOD\n", i + 1);
                }

                else {

                    SetColor (LightRed, Black);
                    printf ("%d BAD\n", i + 1);
                }

                break;
            }

            default:

                break;
        }
    }
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

            if (!check_equal (x1, 0))
                printf ("x == %.2f\n", x1);

            else
                printf ("x == 0\n");

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
