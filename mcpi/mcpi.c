/*
This program estimates the value of pi using Monte Carlo simulation.
See https://en.wikipedia.org/wiki/Monte_Carlo_method
*/

#include <basicgol.h>

#include <time.h>

#define N 1000000

INICIO
    INTEIRO i;
    INTEIRO inside = 0;

    srand(time(NULL));

    PARA(i, 0, N - 1) {
        REAL x = (REAL)rand() / RAND_MAX;
        REAL y = (REAL)rand() / RAND_MAX;
        SE x*x + y*y <= 1 ENTAO
            inside++;
        FIM_SE // if r <= 1, so is sqrt(r)
    }

    // Area of quarter circle / Area of square =
    // = (pi * 1^2 / 4) / 1^2 = inside / N
    // => pi = 4 * inside / N
    ESCREVA_FMT("Value of pi is %.2f\n", 4.0 * inside / N);

    RETORNE 0;
FIM
