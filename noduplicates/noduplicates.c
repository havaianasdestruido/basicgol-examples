/*
We take an array of integers, and remove the duplicates in the array.
We shift the unique values to the left and return the number of unique elements.
For example, if array is
{1, 5, 3, 4, 5, 6, 6, 6, 9, 1} it should become
{1, 5, 3, 4, 6, 9, x, x, x, x} and function should return 6. x is undefined.
*/

#include <basicgol.h>

FUNCAO INTEIRO nodup(INTEIRO *arr, INTEIRO len) {
    INTEIRO i, j;
    INTEIRO num_dups = 0;
    PARA(i, 0, len-num_dups - 1) {
        // Search to the left previous unique values
        PARA(j, 0, i - 1) {
            SE arr[j] == arr[i] ENTAO
                num_dups++;

                // Shift values from the right
                for(INTEIRO k = i; k < len; k++) {
                    arr[k] = arr[k+1];
                }

                // arr[i] now contains a new value from the right,
                // need to process this position again
                i--;

                PARE; // since duplicate already found
            FIM_SE
        }
    }
    RETORNE len - num_dups;
}

INICIO
    INTEIRO i;
    INTEIRO arr[] = {1, 5, 3, 4, 5, 6, 6, 6, 7, 6, 6, 6, 9, 1};
    INTEIRO len = TAMANHO_VETOR(arr);
    INTEIRO num_uniq = nodup(arr, len);
    ESCREVA_FMT("Length of array without duplicates is %d\n", num_uniq);
    PARA(i, 0, num_uniq - 1) ESCREVA_FMT("%d ", arr[i]);
FIM
