/*
Checks if a given word is a palindrome.
*/

#include <basicgol.h>

FUNCAO LOGICO is_palindrome(CARACTERE const *word) {
    INTEIRO i;
    SE word == NULL ENTAO
        RETORNE FALSO;
    FIM_SE

    INTEIRO len = strlen(word);
    PARA(i, 0, len/2 - 1) {
        SE word[i] != word[len-i-1] ENTAO
            RETORNE FALSO;
        FIM_SE
    }
    RETORNE VERDADEIRO;
}

FUNCAO INTEIRO main(INTEIRO argc, CARACTERE *argv[]) {
    SE argc != 2 ENTAO
        ESCREVAL("Error: expecting input word. Quitting...");
        RETORNE 1;
    FIM_SE

    SE is_palindrome(argv[1]) ENTAO
        ESCREVAL("Word is a palindrome!");
    SENAO
        ESCREVAL("Word is a NOT palindrome!");
    FIM_SE
}
