/*
Take a string and reverse the string in-place. That is, the reversed string must be stored
in the location of the original string.
For example, if string is "ABCD EFG" it should become "GFE DCBA".
*/

#include <basicgol.h>

PROCEDIMENTO reverse(CARACTERE *data) {
    INTEIRO i;
    INTEIRO len = strlen(data);

    // Works for both odd and even len
    PARA(i, 0, len/2 - 1) {
        CARACTERE temp = data[i];
        data[i] = data[len - i - 1];
        data[len - i - 1] = temp;
    }
}

INICIO
    CARACTERE data[] = "HelloWorld";

    ESCREVA_FMT("Original: %s\n", data);
    reverse(data);
    ESCREVA_FMT("Reversed: %s\n", data);

    RETORNE 0;
FIM
