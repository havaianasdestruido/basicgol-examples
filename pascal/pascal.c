/*
Prints the Pascal's Triangle.
See https://en.wikipedia.org/wiki/Pascal%27s_triangle
*/

#include <basicgol.h>

#define NUM 15

INICIO
    INTEIRO i, j;
    INTEIRO prev[NUM] = {0};
    INTEIRO curr[NUM] = {0};

    PARA(i, 0, NUM - 1) {
        PARA(j, 0, i) {
            curr[j] = (j == 0 OU j == i) ?
                       1 : prev[j-1] + prev[j];
            ESCREVA_FMT("%4d ", curr[j]);
        }
        ESCREVA_LINHA();
        memcpy(prev, curr, sizeof(curr));
    }
FIM
