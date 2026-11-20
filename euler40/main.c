/*
This code solves Project Euler Problem 40.
See https://projecteuler.net/problem=40
Expected answer is 210.
*/

#include <basicgol.h>

INICIO
    INTEIRO i;
    CARACTERE fractional[1000000 + 7];
    INTEIRO len = 0;
    PARA(i, 0, 999999) {
        // Measure speed of execution using:
        // Windows PowerShell: Measure-Command { .\main.exe }
        // Linux Terminal: time main.exe

        // Slow: strlen() gets slower as string grows longer
        //len = strlen(fractional);
        //sprintf(fractional + len, "%d", i + 1);

        // Fast: make use of the return from sprintf()
        len += sprintf(fractional + len, "%d", i + 1);

        SE len >= 1000000 ENTAO
            PARE;
        FIM_SE
    }

    INTEIRO num = 1;
    INTEIRO indices[] = { 0, 9, 99, 999, 9999, 99999, 999999 };
    for (INTEIRO i = 0; i < TAMANHO_VETOR(indices); i++) {
        num *= fractional[indices[i]] - '0';
    }
    ESCREVA_FMT("%d", num);

    RETORNE 0;
FIM
