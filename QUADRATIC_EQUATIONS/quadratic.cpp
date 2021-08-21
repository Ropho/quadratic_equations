#include "functions.h"
#include "quadratic.h"

int main (int argc, const char *argv[]) {

    #ifndef NDEBUG_MODE

        FILE *input = fopen ("input.txt", "r");

        if (!input) {

            SetColor (LightRed, Black);
            fprintf (stderr, "ERROR : (%s\n%s (%d))\nfile \"input.txt\" not found\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);

            return ERR_FILE_NOT_FOUND;
        }
        quadratic_test (input);
        fclose (input);

    #else

        SetColor (White, Black);

        while (1) {

            printf ("input equation like a * x ^ 2 + b * x + c = 0\n");
            double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;

            if (input_coeffs_file (&a, &b, &c, stdin) == 1) {

                SetColor (LightBlue, Black);
                printf ("U printed a non-digit symbol. Closing the program...");

                return 0;
            }

            int num_roots = quadratic_solve (a, b, c, &x1 , &x2);
            output_roots (num_roots , x1 , x2);
        }

    #endif

    return 0;
}

void quadratic_test (FILE *in) {

    assert (in != NULL);

    int num_lines = 0;

    if (fscanf (in, "%d ", &num_lines) == 0) {

        SetColor (LightRed , Black);
        fprintf (stderr, "ERROR : NUMBER OF LINES NON-DIGIT INPUT");


    }

    for (int i = 0; i < num_lines; ++i) {

        double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;

        if (input_coeffs_file (&a, &b, &c, in) == 1) {

            SetColor (LightRed , Black);
            fprintf (stderr, "ERROR : COEFFICIENT NON-DIGIT INPUT");

            break;
        }

        int num_roots = quadratic_solve (a, b, c, &x1, &x2);
        int ans_num_roots = 0;

        if (fscanf (in, "%d ", &ans_num_roots) == 0) {

            SetColor (LightRed , Black);
            fprintf (stderr, "ERROR : NUMBER OF ROOTS NON-DIGIT INPUT");

            break;
        }

        switch (num_roots) {

            case ZERO: {

                if (ans_num_roots == ZERO) {

                    SetColor (LightGreen, Black);
                    printf ("%d GOOD\n", i + 1);
                }

                else {

                    SetColor (LightRed, Black);
                    printf ("%d BAD : TEST ROOT AND CALCULATED ROOT ARE DIFFERENT\n", i + 1);
                }

                break;
            }

            case ONE: {

                if (ans_num_roots == ONE) {

                    double root = NAN;

                    if (fscanf (in," %lf", &root) == 1) {

                        int good = check_equal (x1, root);

                        if (good) {

                            SetColor (LightGreen, Black);
                            printf ("%d GOOD\n", i + 1);
                        }

                        else {

                            SetColor (LightRed, Black);
                            printf ("%d BAD : TEST ROOT AND CALCULATED ROOT ARE DIFFERENT\n", i + 1);

                        }
                    }

                    else {

                        SetColor (LightRed , Black);
                        fprintf (stderr, "ERROR : ROOT NON-DIGIT INPUT");

                        break;
                    }
                }

                else {

                    SetColor (LightRed, Black);
                    printf ("%d BAD : NUMBER OF TEST AND CALCULATED ROOTS DOESN'T MATCH\n", i + 1);
                }

                break;
            }

            case TWO: {

                if (ans_num_roots == TWO) {

                    double root1 = NAN, root2 = NAN;
                    if (fscanf (in," %lf %lf ", &root1, &root2) == 2) {

                        if ((check_equal (x1, root1) && check_equal (x2, root2)) ||
                            (check_equal (x1, root2) && check_equal (x2, root1))) {

                            SetColor (LightGreen, Black);
                            printf ("%d GOOD\n", i + 1);
                        }

                        else {

                            SetColor (LightRed, Black);
                            printf ("%d BAD : TEST ROOTS AND CALCULATED ROOTS ARE DIFFERENT\n", i + 1);

                        }

                    }

                    else {

                        SetColor (LightRed , Black);
                        fprintf (stderr, "ERROR : ROOTS NON-DIGIT INPUT");

                        break;

                    }
                }

                else {

                    SetColor (LightRed, Black);
                    printf ("%d BAD : TEST ROOT AND CALCULATED ROOT ARE DIFFERENT\n", i + 1);
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
                    printf ("%d BAD : TEST ROOT AND CALCULATED ROOT ARE DIFFERENT\n", i + 1);
                }

                break;
            }

            default:

                break;
        }
    }
}

int input_coeffs_file (double *a, double *b, double *c, FILE *in) {

    assert (in != NULL);
    assert (a  != NULL);
    assert (b  != NULL);
    assert (c  != NULL);
    assert (! (a == b || b == c || a == c));

    return (fscanf (in, "%lf %lf %lf", a, b, c) != 3);
}

void output_roots (int num_roots, double x1, double x2) {

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

            assert (!isnan(x1));

            if (!check_equal (x1, 0))
                printf ("x == %.2lf\n", x1);

            else
                printf ("x == 0\n");

            break;
        }

        case TWO: {

            assert (!isnan(x1));
            assert (!isnan(x2));

            if (check_equal (x1, 0) && !check_equal (x2, 0))
                printf ("x1 == 0 \t x2 == %.2lf\n", x2);

            else if (!check_equal (x1 ,0) && check_equal (x2, 0))
                printf ("x1 == %.2lf \t x2 == 0\n", x1);

            else
                printf ("x1 == %.2lf \t x2 == %.2lf\n", x1, x2);

            break;
        }

        default:

            break;
    }
}
