/*
The period of a pendulum (with small angle) is given in
https://www.acs.psu.edu/drussell/Demos/Pendulum/Pendulum.html
Given pendulum length and g, write a function to calculate the period of oscillation.
*/

#include <basicgol.h>


FUNCAO REAL_CURTO pendulum_period(REAL_CURTO len)
{
    REAL_CURTO const g = 9.81; // m/s2
    REAL_CURTO T;

    // 0.01 to covert len from cm to m
    T = 2 * acos(-1.0) * RAIZ(len*0.01/g);

    RETORNE T;
}

INICIO
    REAL_CURTO len;

    ESCREVA("Enter length of the pendulum (cm): ");
    SE NAO LEIA_OK(len) ENTAO
        RETORNE 1;
    FIM_SE

    ESCREVA_FMT("Time period of the pendulum of length %.2f cm is %.2f s",
            len, pendulum_period(len));
FIM
