#include <basicgol.h>

// ===========================================
// Correct char * return example
// ===========================================
FUNCAO CARACTERE *allocate_str_ok1(size_t n, CARACTERE init)
{
    CARACTERE *p = malloc(n + 1); // n+1 bytes
    memset(p, init, n);
    p[n] = 0;
    RETORNE p;
}

// ===========================================
// Wrong char *p argument example
// ===========================================
PROCEDIMENTO allocate_str_ko(CARACTERE *p, size_t n, CARACTERE init)
{
    p = malloc(n + 1);
    memset(p, init, n);
    p[n] = 0;
}

// ===========================================
// Correct char **p argument example
// ===========================================
PROCEDIMENTO allocate_str_ok2(CARACTERE **p, size_t n, CARACTERE init)
{
    *p = malloc(n + 1);
    memset(*p, init, n);
    (*p)[n] = 0;
}

INICIO
    CARACTERE *ptr = NULL;
    ptr = allocate_str_ok1(10, 'A');
    ESCREVA_FMT("ok1: %s\n", ptr);
    free(ptr); ptr = NULL;

    allocate_str_ko(ptr, 10, 'A');
    ESCREVA_FMT(" ko: %s\n", ptr);
    free(ptr); ptr = NULL;

    allocate_str_ok2(&ptr, 10, 'A');
    ESCREVA_FMT("ok2: %s\n", ptr);
    free(ptr); ptr = NULL;
FIM
