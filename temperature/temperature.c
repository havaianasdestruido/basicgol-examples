/*
Temperature conversion from Celsius to Fahrenheit and vice versa.
Should be called with two arguments: temperature and unit.
Unit can be C or F.
Example arguments:
23.4 C
40.1 F
*/

#include <basicgol.h>

FUNCAO REAL_CURTO cel_to_fah(REAL_CURTO temp_in_C) {
    REAL_CURTO temp_in_fah;
    temp_in_fah = (temp_in_C * 9/5) + 32;
    RETORNE temp_in_fah;
}

FUNCAO REAL_CURTO fah_to_cel(REAL_CURTO temp_in_F) {
    REAL_CURTO temp_in_cel;
    temp_in_cel = (temp_in_F - 32) * 5/9;
    RETORNE temp_in_cel;
}

FUNCAO INTEIRO main(INTEIRO argc, CARACTERE *argv[]) {
    SE argc != 3 ENTAO
        ESCREVAL("Error: expecting exactly 2 program arguments. Quitting...");
        RETORNE 1;
    FIM_SE

    REAL_CURTO temperature = (REAL_CURTO)atof(argv[1]);
    CARACTERE unit = argv[2][0];

    // Old code to prompt for user input
    // printf("Enter temperature (C or F): ");
    // scanf("%f %c", &temperature, &unit);

    ESCOLHA(unit)
        CASO 'C':
            ESCREVA_FMT("%f F\n", cel_to_fah(temperature));
            PARE;
        CASO 'F':
            ESCREVA_FMT("%f C\n", fah_to_cel(temperature));
            PARE;
        CONTRARIO:
            ESCREVAL("Error: unrecognized temperature unit. Only celsius or fahrenheit allowed.");
            PARE;
    FIM_ESCOLHA

    RETORNE 0;
}
