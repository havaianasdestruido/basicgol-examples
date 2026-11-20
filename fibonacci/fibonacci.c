#include <basicgol.h>

// See https://en.wikipedia.org/wiki/Fibonacci_sequence
// Fibonacci: 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377

#define NUM 15

/* Generate Fibonacci sequence of N numbers.
   We keep track of numbers and print at the end.
*/
PROCEDIMENTO method_0(INTEIRO N) {
    INTEIRO fib[N];
    fib[0] = 0;
    fib[1] = 1;
    for(INTEIRO n = 2; n < N; n++) {
        fib[n] = fib[n-1] + fib[n-2];
    }
    for(INTEIRO n = 0; n < N; n++) {
        ESCREVA_FMT("%d ", fib[n]);
    }
    ESCREVA_LINHA();
}

/* Generate Fibonacci sequence of N numbers.
   We print each number as it is generated.
*/
PROCEDIMENTO method_1(INTEIRO N) {
    INTEIRO Fn_2 = 0;
    INTEIRO Fn_1 = 1;

    ESCREVA_FMT("%d %d ", Fn_2, Fn_1);

    for(INTEIRO n = 2; n < N; n++) {
        INTEIRO Fn = Fn_1 + Fn_2;
        ESCREVA_FMT("%d ", Fn);
        Fn_2 = Fn_1;
        Fn_1 = Fn;
    }
    ESCREVA_LINHA();
}

INICIO
    method_0(NUM);
    method_1(NUM);
    RETORNE 0;
FIM
