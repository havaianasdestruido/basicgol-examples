/*
Find the sum of the first 10 terms of convergent series, 1 + 2/7 + 3/7^2 + ...
*/

#include <basicgol.h>

INICIO
    INTEIRO i;
    REAL sum = 0;

    PARA(i, 0, 9) {
        sum += (i + 1) / POTENCIA(7, i);
    }

    ESCREVA_FMT("Sum is %.6f\n", sum);

    RETORNE 0;
FIM
