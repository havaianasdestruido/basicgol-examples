/*
This code implements an encoder and a decoder for Morse Code.

The International Morse Code can be seen at
https://en.wikipedia.org/wiki/Morse_code

While encoding, source symbols (letters or digits) of the same word
are separated by a single space. Source words are separated by
three spaces. If original message has punctuation, it is replaced
with a space. Multiple consecutive spaces are replaced with a single
space before encoding.

While decoding, all letters are output in uppercase.
*/

#include <basicgol.h>

#include <ctype.h>

CARACTERE * digits[] = {
    // 0        1        2        3        4
    "-----", ".----", "..---", "...--", "....-",
    // 5        6        7        8        9
    ".....", "-....", "--...", "---..", "----."
};

CARACTERE * letters[] = {
    // A      B       C       D      E
    ".-",   "-...", "-.-.", "-..",  ".",
    // F      G       H       I      J
    "..-.", "--.",  "....", "..",   ".---",
    // K      L       M       N      O
    "-.-",  ".-..", "--",   "-.",   "---",
    // P      Q       R       S      T
    ".--.", "--.-", ".-.",  "...",  "-",
    // U      V       W       X      Y
    "..-",  "...-", ".--",  "-..-", "-.--",
    // Z
    "--.."
};

FUNCAO CARACTERE search(CARACTERE * needle, CARACTERE * haystack[], INTEIRO size, CARACTERE start) {
    INTEIRO i;
    PARA(i, 0, size - 1) {
        SE strcmp(needle, haystack[i]) == 0 ENTAO
            RETORNE start + i;
        FIM_SE
    }
    RETORNE '\0';
}

FUNCAO CARACTERE * decoder(CARACTERE const * enc_msg) {
    CARACTERE * decoded_msg = calloc(strlen(enc_msg), sizeof(CARACTERE));

    // Each character can be at most 5 dots or dashes plus NUL character
    CARACTERE curr_symbol[5+1] = {0};

    INTEIRO num_spaces = 0;
    CARACTERE curr_char;
    CARACTERE dec_char;
    for (INTEIRO i = 0; i < strlen(enc_msg); i++) {
        curr_char = enc_msg[i];
        SE curr_char == ' ' ENTAO
            num_spaces++;
            SE num_spaces == 3 ENTAO // three spaces => word boundary
                dec_char = ' ';
            SENAO_SE strlen(curr_symbol) == 5 ENTAO // digit
                dec_char = search(curr_symbol, digits, TAMANHO_VETOR(digits), '0');
            SENAO // letter
                dec_char = search(curr_symbol, letters, TAMANHO_VETOR(letters), 'A');
            FIM_SE
            decoded_msg[strlen(decoded_msg)] = dec_char;
            memset(curr_symbol, 0, sizeof(curr_symbol)); // reset to receive next symbol
        SENAO
            num_spaces = 0;
            curr_symbol[strlen(curr_symbol)] = curr_char;
        FIM_SE
    }

    RETORNE decoded_msg;
}

FUNCAO CARACTERE * encoder(CARACTERE const * msg) {
    // Each character can be at most 5 dots or dashes plus a space
    CARACTERE * encoded_msg = malloc(strlen(msg)*5 + 1);
    encoded_msg[0] = '\0';

    CARACTERE curr_char, prev_char = '\0';
    for (INTEIRO i = 0; i < strlen(msg); i++) {
        curr_char = msg[i];
        SE isalpha(curr_char) ENTAO
            INTEIRO idx = toupper(curr_char) - 'A';
            strcat(encoded_msg, letters[idx]);
            strcat(encoded_msg, " ");
        SENAO_SE isdigit(curr_char) ENTAO
            INTEIRO idx = curr_char - '0';
            strcat(encoded_msg, digits[idx]);
            strcat(encoded_msg, " ");
        SENAO
            curr_char = ' ';
            SE curr_char == ' ' E prev_char != ' ' ENTAO
                strcat(encoded_msg, "  ");
            FIM_SE
        FIM_SE
        prev_char = curr_char;
    }

    RETORNE encoded_msg;
}

INICIO
    CARACTERE msg[]  = {
        "Lorem's Ipsum is simply, dummy text of the printing and typesetting industry."
    };

    CARACTERE * enc_msg = encoder(msg);
    ESCREVA_FMT("Encoded message: %s\n", enc_msg);

    CARACTERE * dec_msg = decoder(enc_msg);
    ESCREVA_FMT("Decoded message: %s\n", dec_msg);

    RETORNE 0;
FIM
