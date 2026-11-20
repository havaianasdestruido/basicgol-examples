/*
This code solves Project Euler Problem 13.
See https://projecteuler.net/problem=13
Expected answer is 5537376230.
Input data filename is hardcoded below.
*/

#include <basicgol.h>

#define NUM_INTS 100
#define INT_LEN 50

INICIO
    INTEIRO i, j;
    CARACTERE data[NUM_INTS][INT_LEN+2]; // \n and \0 at the end

    FILE *fp = fopen("euler13.txt", "r");
    SE fp == NULL ENTAO
        ESCREVAL("Error: Unable to open data file. Quitting...");
        RETORNE 1;
    FIM_SE

    PARA(i, 0, NUM_INTS - 1) {
        fgets(data[i], INT_LEN + 2, fp);
        data[i][INT_LEN] = '\0'; // overwrite \n
        //printf("%2d %s\n", i, data[i]);
    }

    fclose(fp); fp = NULL;

    NATURAL carryover = 0;
    CARACTERE full_sum[2+INT_LEN+1] = {0};
    PARA(j, 0, INT_LEN / 5 - 1) {
        // In this loop, process only 5 digits per iteration.
        // Start processing from rightmost digits and save
        // carryover for next iteration.
        NATURAL sum = carryover;
        NATURAL offset = INT_LEN - (j+1)*5;
        PARA(i, 0, NUM_INTS - 1) {
            // In this loop, add 5 digits of all NUM_INTS integers.
            CARACTERE numstr[5+1] = {0};
            strncpy(numstr, data[i] + offset, 5);
            sum += atoi(numstr);
        }

        CARACTERE sumstr[2+5+1] = {0};
        snprintf(sumstr, sizeof(sumstr), "%07u", sum);
        strncpy(full_sum + 2 + offset, sumstr + 2, 5);
        sumstr[2] = '\0'; // retain only 2 leftmost digits
        carryover = atoi(sumstr);
    }

    // Final carryover
    CARACTERE co_str[2+1] = {0};
    snprintf(co_str, 2+1, "%02u", carryover);
    strncpy(full_sum, co_str, 2);

    ESCREVA_FMT("Sum (%zu digits): %s\n", strlen(full_sum), full_sum);
    full_sum[10] = '\0'; // retain only 10 leftmost digits
    ESCREVA_FMT("Sum (first 10 digits): %s\n", full_sum);

    RETORNE 0;
FIM
