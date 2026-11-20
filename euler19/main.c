/*
This code solves Project Euler Problem 19.
See https://projecteuler.net/problem=19
Expected answer is 171.
*/

#include <basicgol.h>

ENUMERACAO(DayOfWeek)
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    NumOfDays
FIM_ENUMERACAO(DayOfWeek);

FUNCAO LOGICO is_leap_year(INTEIRO year) {
    SE year % 400 == 0 ENTAO
        RETORNE VERDADEIRO;
    FIM_SE
    SE year % 100 == 0 ENTAO
        RETORNE FALSO;
    FIM_SE
    RETORNE year MOD 4 == 0;
}

INICIO
    INTEIRO year, i, j;
    INTEIRO days_in_month[12] = { 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    INTEIRO num_sunday_start = 0;

    // 1-Jan-1900 is Monday, find day on 1-Jan-1901
    // 1900 is not a leap year, hence add only 365
    DayOfWeek today = (Monday + 365) % NumOfDays;

    PARA(year, 1901, 2000) {
        days_in_month[1] = is_leap_year(year) ? 29 : 28;
        PARA(i, 0, 11) {
            PARA(j, 0, days_in_month[i] - 1) {
                SE j == 0 E today == Sunday ENTAO
                    num_sunday_start++;
                FIM_SE
                today = (today + 1) % NumOfDays;
            }
        }
    }

    ESCREVA_FMT("%d", num_sunday_start);

    RETORNE 0;
FIM
