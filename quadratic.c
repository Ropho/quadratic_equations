#include "quadratic.h"

int main(void){
    setlocale(LC_ALL, "Russian");

    #ifndef NDEBUG_MODE
    {                            //ВВОД ИЗ ФАЙЛА
        FILE *in = NULL;
        if ((in = fopen("input.txt", "r")) == NULL){
            fprintf(stderr, "файл не найден\n");
            return FILE_NOT_FOUND;
        }
        vvod_from_file(in);
        fclose(in);
    }

    #else           //ВВОД ИЗ КОНСОЛИ

        while(1){
            printf("введите аргументы уравнения a * x ^ 2 + b * x + c = 0\n");
            float a = 0, b = 0,c = 0, x1 = 0, x2 = 0;

            if(input(&a, &b, &c) == 1){
                printf("ВВЕДЕН нечисловой символ((((");
                return ONE;
            }
            int kol = quadratic(a, b, c, &x1 , &x2);
            output(kol , x1 , x2);
        }

    #endif

}

void vvod_from_file(FILE *in){
    int kolvo_str = 0;
    fscanf(in, "%d ", &kolvo_str);

    for(int i = 0;i < kolvo_str; ++i){
        float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
        if (input_f(&a, &b, &c, in) == 1){
                fprintf(stderr, "нечисленный символ");
                break;
        }

        int kol = quadratic(a, b, c, &x1, &x2);
        char ans[30] = "";
        fgets(ans, 30, in);
        printf("тест: %.2f %.2f %.2f ответ: %s", a , b , c, ans);
        output(kol , x1 , x2);
    }
}





int check(float a, float b){
    return fabs(a - b) < e;
}

int input(float *a, float *b, float *c){
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(! (a == b || b == c || a == c));

    if (scanf("%f", a) == 0)
        return ONE;
    if (scanf("%f", b) == 0)
        return ONE;
    if (scanf("%f", c) == 0)
        return ONE;
    return ZERO;
}

void output(int kol, float x1, float x2){
    switch (kol)
    {
    case INF:
        printf("любое число\n");
        break;
    case ZERO:
        printf("нет корней\n");
        break;
    case ONE:
        if (!check(x1, 0))
            printf("x == %.2f\n", x1);
        else
            printf("x == 0\n");
        break;
    default:
         if (check(x1, 0) && !check(x2, 0))
            printf("x1 == 0 \t x2 == %.2f\n", x2);
        else if (!check(x1 ,0) && check(x2, 0))
            printf("x1 == %.2f \t x2 == 0\n", x1);
        else
            printf("x1 == %.2f \t x2 == %.2f\n", x1, x2);
        break;
    }
}


int linear(float a, float b, float c, float *x1, float *x2){
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

int input_f(float *a, float *b, float *c, FILE *in){
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(! (a == b || b == c || a == c));

    if (fscanf(in, "%f", a) == 0)
        return 1;
    if (fscanf(in, "%f", b) == 0)
        return 1;
    if (fscanf(in, "%f", c) == 0)
        return 1;
    return 0;
}
