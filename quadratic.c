#include "quadratic.h"

int main(void){

    #ifndef NDEBUG_MODE
    {
        FILE *in = NULL;
        if ((in = fopen("input.txt", "r")) == NULL){
            fprintf(stderr, "file not found\n");
            return FILE_NOT_FOUND;
        }
        vvod_from_file(in);
        fclose(in);
    }

    #else

        while(1){
            printf("input equation like a * x ^ 2 + b * x + c = 0\n");
            float a = 0, b = 0,c = 0, x1 = 0, x2 = 0;

            if(input_f(&a, &b, &c, stdin) == 1){
                printf("Symbol not digit");
                return 0;
            }
            int kol = quadratic(a, b, c, &x1 , &x2);
            output(kol , x1 , x2);
        }

    #endif
    return 0;
}

void vvod_from_file(FILE *in){
    int kolvo_str = 0;
    fscanf(in, "%d ", &kolvo_str);

    for (int i = 0; i < kolvo_str; ++i){
        float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
        if (input_f(&a, &b, &c, in) == 1){
                fprintf(stderr, "error");
                break;
        }

        int kol = quadratic(a, b, c, &x1, &x2);
        int ans_kol_roots = 0;
        fscanf(in, "%d ", &ans_kol_roots);

        switch (kol){

        case ZERO:{
            if (ans_kol_roots == ZERO)
                printf("%d GOOD\n", i + 1);
            else
                printf("%d BAD\n", i + 1);
            break;
        }
        case ONE:{
            float temp = 0;
            fscanf(in," %f", &temp);
            if (check(x1, temp))
                printf("%d GOOD\n", i + 1);
            else
                printf("%d BAD\n", i + 1);
            break;
        }
        case TWO:{
            float temp1 = 0, temp2 = 0;
            fscanf(in," %f %f ", &temp1, &temp2);
            if ((check(x1, temp1) && check(x2, temp2)) || (check(x1, temp2) && check(x2, temp1)))
                printf("%d GOOD\n", i + 1);
            else
                printf("%d BAD\n", i + 1);
            break;
        }
        case INF:{
            if (ans_kol_roots == INF)
                printf("%d GOOD\n", i + 1);
            else
                printf("%d BAD\n", i + 1);
            break;
        }
        default:
            break;
        }

    }
}





int check(float a, float b){
    return fabs(a - b) < e;
}


int input_f(float *a, float *b, float *c, FILE *in){
    assert(in != NULL);
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(! (a == b || b == c || a == c));

    return (fscanf(in,"%f %f %f", a, b, c) != 3);
}

void output(int kol, float x1, float x2){
    switch (kol)
    {
    case INF:
        printf("INF\n");
        break;
    case ZERO:
        printf("ZERO roots\n");
        break;
    case ONE:{
        if (!check(x1, 0))
            printf("x == %.2f\n", x1);
        else
            printf("x == 0\n");
    }
        break;
    case TWO:{
        if (check(x1, 0) && !check(x2, 0))
            printf("x1 == 0 \t x2 == %.2f\n", x2);
        else if (!check(x1 ,0) && check(x2, 0))
            printf("x1 == %.2f \t x2 == 0\n", x1);
        else
            printf("x1 == %.2f \t x2 == %.2f\n", x1, x2);
        }
        break;
    default:
        break;
    }
}


int linear(float a, float b, float c, float *x1, float *x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (check(b, 0)){
        if (check(c, 0))
            return INF;
        else
            return ZERO;
    }
    else {
        *x1 = -c / b;
        // *x2 = *x1;
        return ONE;
    }
}
int quadratic(float a, float b, float c, float *x1, float *x2){
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (check(a, 0))
        return linear(a, b, c, x1, x2);
    else {
        float discriminant = (b * b) - (4 * a * c);

        if (discriminant < 0)
            return ZERO;
        else if (check(discriminant, 0)){
            *x1 =  -b / (2 * a);
            // *x2 =  *x1;
            return ONE;
        }
        else {
            *x1 = (sqrt(discriminant) - b) / (2 * a);
            *x2 = (-sqrt(discriminant) - b) / (2 * a);
            return TWO;
        }
    }
}


