/*
This consists of a few exercises to practice the handling of arrays.
*/

#include <basicgol.h>

// Take two arrays and find items common to both not necessarily in the same index
PROCEDIMENTO find_commons(INTEIRO a[], INTEIRO b[], INTEIRO size) {
    // TODO Find common items and print here
}

// Take the average of n consecutive items
PROCEDIMENTO find_moving_average(INTEIRO a[], INTEIRO size, INTEIRO n) {
    // TODO Calculate and print the moving averages here
}

// Sort an array of integers from lowest to highest values
PROCEDIMENTO sort_nums(INTEIRO a[], INTEIRO size) {
    // TODO Sort and print the sorted array here
}

// Sort an array of strings in ASCII order
PROCEDIMENTO sort_strings(CARACTERE * a[], INTEIRO size) {
    // TODO Sort and print the sorted array here
}

INICIO
    INTEIRO a[] = { 2, 3, 7, 3, 4, 3, 4, 5, 6, 1 };
    INTEIRO b[] = { 7, 2, 10, 2, 7, 4, 9, 4, 9, 8 };

    find_commons(a, b, TAMANHO_VETOR(a));

    find_moving_average(a, TAMANHO_VETOR(a), 3);

    sort_nums(b, TAMANHO_VETOR(b));

    CARACTERE * s[] = {
        "hello",
        "world",
        "kitty",
        "Delhi",
        "hi",
        "average",
        "yellow",
        "caller"
    };
    sort_strings(s, TAMANHO_VETOR(s));

    RETORNE 0;
FIM
