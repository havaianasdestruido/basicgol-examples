#include <basicgol.h>

// Wrong: Shows arguments passed by value
PROCEDIMENTO swap_ko(INTEIRO x, INTEIRO y)
{
    INTEIRO old_y;
    old_y = y;
    y = x;
    x = old_y;
    ESCREVA_FMT("swap_ko(): %p %p : %d %d\n", &x, &y, x, y);
}

// Correct: Shows arguments passed by reference
PROCEDIMENTO swap_ok(INTEIRO *x, INTEIRO *y)
{
    INTEIRO old_y;
    old_y = *y;
    *y = *x;
    *x = old_y;
    ESCREVA_FMT("swap_ok(): %p %p : %d %d\n", x, y, *x, *y);
}

INICIO
    INTEIRO x = 5, y = 10;

    swap_ko(x, y);
    ESCREVA_FMT("main(): %p %p : %d %d\n", &x, &y, x, y);

    swap_ok(&x, &y);
    ESCREVA_FMT("main(): %p %p : %d %d\n", &x, &y, x, y);
FIM
