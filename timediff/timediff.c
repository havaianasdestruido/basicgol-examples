/*
Takes two times in HH:MM:SS 24-hour format. Both times  belong to the same day.
Finds the absolute difference of the two times in seconds.
*/

#include <basicgol.h>

/*
Take time in HH:MM:SS 24-hour format.
Return the number of seconds since midnight (00:00:00).
*/
FUNCAO INTEIRO time2secs(CARACTERE *time) {
    INTEIRO hour, min, sec;
    sscanf(time, "%02d:%02d:%02d", &hour, &min, &sec);
    RETORNE hour*60*60 + min*60 + sec;
}

FUNCAO INTEIRO main(INTEIRO argc, CARACTERE *argv[]) {
    SE argc != 3 ENTAO
        ESCREVAL("Error: expecting exactly 2 program arguments. Quitting...");
        RETORNE 1;
    FIM_SE

    INTEIRO t1 = time2secs(argv[1]);
    INTEIRO t2 = time2secs(argv[2]);

    ESCREVA_FMT("Time difference is %d secs\n", abs(t1 - t2));

    RETORNE 0;
}
