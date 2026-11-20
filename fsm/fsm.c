/*
This code is about a Finite State Machine (FSM). Our goal
is find the steady state probabilities of the given states.

Our FSM has three states. The transition probabilities among
the states are also given. By doing a Monte Carlo simulation,
we estimate the steady state probabilities, that is, the
percentage of time the system will be in each state.

For example, when a day is sunny, 50% of the time the next
day will also be sunny. When a day is rainy, 40% of the time
the next day will be cloudy.
*/

#include <basicgol.h>

#include <time.h>

#define NUM_STEPS 10000

ENUMERACAO(Weather)
    Sunny = 0,
    Cloudy,
    Rainy,
    NUM_STATES
FIM_ENUMERACAO(Weather);

CARACTERE * WeatherStr[NUM_STATES] = {
    "Sunny", "Cloudy", "Rainy"
};

INICIO
    INTEIRO i, j;
    // FSM transition probability matrix
    REAL_CURTO transitions[NUM_STATES][NUM_STATES] = {
        { 0.5, 0.3, 0.2 },
        { 0.1, 0.6, 0.3 },
        { 0.5, 0.4, 0.1 }
    };

    // Make a matrix of cumulative transitions
    REAL_CURTO cumulatives[NUM_STATES][NUM_STATES];
    PARA(i, 0, NUM_STATES - 1) {
        REAL_CURTO sum = 0;
        PARA(j, 0, NUM_STATES - 1) {
            sum += transitions[i][j];
            cumulatives[i][j] = sum;
        }
        SE sum != 1.0 ENTAO
            ESCREVA_FMT("Warning: transitions probabilities from [%s] state "
                   "don't add up to 1.0.\n", WeatherStr[i]);
        FIM_SE
    }

    srand(time(NULL));

    Weather curr_state = Sunny;
    INTEIRO counts[NUM_STATES] = {0};

    PARA(i, 0, NUM_STEPS - 1) {
        REAL_CURTO rn = (REAL_CURTO)(rand()) / RAND_MAX;
        PARA(j, 0, NUM_STATES - 1) {
            SE rn < cumulatives[curr_state][j] ENTAO
                curr_state = j;
                PARE;
            FIM_SE
        }
        counts[curr_state]++;
    }

    PARA(j, 0, NUM_STATES - 1) {
        ESCREVA_FMT("%6s: %4.1f %%\n", WeatherStr[j], counts[j] * 100.0 / NUM_STEPS);
    }

    RETORNE 0;
FIM
