/*
This code takes an array of strings and returns the longest one.
*/

#include <basicgol.h>

FUNCAO CARACTERE *maxstr(CARACTERE *data[], INTEIRO len) {
    INTEIRO i;
    INTEIRO maxlen = strlen(data[0]);
    CARACTERE *maxstr = data[0];
    PARA(i, 1, len - 1) {
        INTEIRO len = strlen(data[i]);
        SE len > maxlen ENTAO
            maxlen = len;
            maxstr = data[i];
        FIM_SE
    }
    RETORNE maxstr;
}

INICIO
    CARACTERE *data[] = { // array of pointers to strings
        "Chennai",
        "New York",
        "San Francisco",
        "London",
        "Bangalore",
        "Tokyo"
    };
    INTEIRO len = sizeof(data) / sizeof(data[0]);
    ESCREVA_FMT("Maximum string is %s\n", maxstr(data, len));
FIM
