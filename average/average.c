#include <basicgol.h>

FUNCAO REAL average(NATURAL arr[], NATURAL n) { // unsigned int *arr
    REAL sum = 0;

    for (INTEIRO i = 0; i < n; i++) {
        sum += arr[i]; // *(arr+i)
    }

    RETORNE sum / n;
}

INICIO
    NATURAL scores[] = { 67, 55, 89, 77, 60, 72, 84, 63, 91, 59 };
    REAL mean = average(scores, TAMANHO_VETOR(scores));
    ESCREVA_FMT("%.3g", mean);
FIM
