/*
Take a list of English words at
https://raw.githubusercontent.com/dwyl/english-words/refs/heads/master/words_alpha.txt
Give a word, write a function to determine if the word is a valid English word.
This program compares the runtime performance of linear search vs binary search.
*/

#include <basicgol.h>

#define DEBUG 1

// TODO Determine these dynamically
const INTEIRO FILE_SIZE = 4235000;
const INTEIRO NUM_WORDS = 370105;

FUNCAO CARACTERE ** load_dict(CARACTERE *filename) {
    INTEIRO i;
    FILE *fp = fopen(filename, "r");
    SE fp == NULL ENTAO
        ESCREVAL("Error: Unable to open data file.");
        RETORNE NULL;
    FIM_SE

    CARACTERE *buffer = malloc(FILE_SIZE);
    SE NAO buffer ENTAO
        ESCREVAL("Error: Allocation failed for file buffer.");
        fclose(fp);
        RETORNE NULL;
    FIM_SE

    INTEIRO bytes_read = fread(buffer, 1, FILE_SIZE, fp);
    buffer[bytes_read] = '\0';
    fclose(fp);

    CARACTERE **words = malloc(NUM_WORDS * sizeof(CARACTERE *));
    SE NAO words ENTAO
        ESCREVAL("Error: Allocation failed for word pointers.");
        free(buffer);
        RETORNE NULL;
    FIM_SE

    INTEIRO curr = 0;
    words[curr++] = buffer;
    PARA(i, 0, bytes_read - 1) {
        SE buffer[i] == '\n' ENTAO
            buffer[i] = '\0';
            SE i + 1 < bytes_read E buffer[i + 1] != '\0' ENTAO
                words[curr++] = &buffer[i + 1];
            FIM_SE
        FIM_SE
    }

    #if DEBUG
    ESCREVA_FMT("Successfully loaded %d words!\n", NUM_WORDS);
    ESCREVA_FMT("First word: %s\n", words[0]);
    ESCREVA_FMT("Last word: %s\n", words[NUM_WORDS - 1]);
    #endif

    RETORNE words;
}

FUNCAO LOGICO linear_search(CARACTERE **words, CARACTERE *word) {
    INTEIRO i;
    PARA(i, 0, NUM_WORDS - 1) {
        SE strcmp(words[i], word)==0 ENTAO
            ESCREVA_FMT("Linear search: found word in %d iterations.\n", i+1);
            RETORNE VERDADEIRO;
        FIM_SE
    }
    RETORNE FALSO;
}

FUNCAO LOGICO binary_search(CARACTERE **words, CARACTERE *word) {
    INTEIRO i = 0;
    INTEIRO old_pivot = -1, pivot = NUM_WORDS >> 1;
    INTEIRO step = pivot;
    ENQUANTO pivot >= 0 E pivot < NUM_WORDS FACA
        i++;
        INTEIRO comp_res = strcmp(words[pivot], word);
        SE comp_res == 0 ENTAO
            ESCREVA_FMT("Binary search: found word in %d iterations.\n", i);
            RETORNE VERDADEIRO;
        FIM_SE
        step = step > 1 ? (step + 1) >> 1 : 1;
        SE step == 1 ENTAO
            // Searched two adjacent words and didn't find a match
            SE (comp_res < 0 E pivot + 1 == old_pivot) OU
                (comp_res > 0 E pivot - 1 == old_pivot) ENTAO
                PARE;
            FIM_SE
        FIM_SE
        old_pivot = pivot;
        SE comp_res < 0 ENTAO
            pivot += step;
        SENAO_SE comp_res > 0 ENTAO
            pivot -= step;
        FIM_SE
    FIM_ENQUANTO
    RETORNE FALSO;
}

FUNCAO LOGICO is_in_dict(CARACTERE **words, CARACTERE *word, LOGICO (*search)(CARACTERE **, CARACTERE *)) {
    LOGICO found = search(words, word);
    SE NAO found ENTAO
        ESCREVAL("Did not find a match in the dictionary.");
    FIM_SE
    RETORNE found;
}

FUNCAO INTEIRO main(INTEIRO argc, CARACTERE *argv[]) {
    SE argc != 2 ENTAO
        ESCREVAL("Error: expecting exactly 1 program argument.");
        RETORNE 1;
    FIM_SE
    CARACTERE *word = argv[1];

    // Already downloaded, sorted and saved to the local system
    CARACTERE **words = load_dict("sorted_words_alpha.txt");
    SE NAO words ENTAO
        RETORNE 2;
    FIM_SE

    is_in_dict(words, word, linear_search);
    is_in_dict(words, word, binary_search);

    RETORNE 0;
}
