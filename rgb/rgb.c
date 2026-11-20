/*
This code converts RGB color from hex form to decimal form.
Hex form starts with '#' character, which is common on webpages.
Example: #66CCDE in decimal is (102, 204, 222)
*/

#include <basicgol.h>

REGISTRO(Color)
    NATURAL r;
    NATURAL g;
    NATURAL b;
FIM_REGISTRO(Color);

INICIO
    CARACTERE bg_color[] = "#66CCDE";

    Color c;
    sscanf(bg_color, "#%2x%2x%2x", &c.r, &c.g, &c.b);
    ESCREVA_FMT("%u %u %u\n", c.r, c.g, c.b);

    // Illustrating pointer syntax to struct member variables
    Color *p = &c;
    ESCREVA_FMT("%u %u %u\n", p->r, p->g, p->b);
FIM
