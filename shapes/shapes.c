/*
A few examples to practice handling of strings and printf().
In these examples we print various shapes of letters or digits.
*/

#include <basicgol.h>

/*
a
ab
abc
abcd
abcde
abcdef
*/
PROCEDIMENTO abcdef() {
    INTEIRO i;
    CARACTERE data[] = "abcdef";
    CARACTERE excess[sizeof(data)] = {0};

    PARA(i, 0, 5) {
        excess[i] = data[i];
        ESCREVA_FMT("%s\n", excess);
    }
}

/*
        9
       898
      78987
     6789876
    567898765
   45678987654
  3456789876543
 234567898765432
12345678987654321
*/
PROCEDIMENTO numbers() {
    INTEIRO i, j;
    // In this code, we treats the digits as char, not int
    CARACTERE data[] = "12345678987654321";

    // Solution 1: each digit is printed separately,
    // first digit is printed with extra left spaces
    PARA(i, 0, 8) { // 0-indexed row num
        PARA(j, -i, i) { // loop for number of chars in row
            // Example: 898: i==1 and j is [-1, 0, 1]
            SE j == -i ENTAO
                // for first char in row add left padding
                CARACTERE format[4];
                sprintf(format, "%%%dc\0", 9+j);
                ESCREVA_FMT(format, data[8+j]);
            SENAO
                ESCREVA_FMT("%c", data[8+j]);
            FIM_SE
        }
        ESCREVA_LINHA();
    }

    // Solution 2: all digits in a row are printed together
    // along with extra left spaces
    PARA(i, 0, 8) {
        /*
        i   #spaces  #digits   #chars   format
            8-i      2*i+1     i+9
        0 : 8        1         8        %9s\n
        1 : 7        3         7        %10s\n
        2 : 6        5         6        %11s\n
        */
        CARACTERE num[sizeof(data)] = {0};
        strncpy(num, data + 8 - i, 2*i + 1);

        CARACTERE format[6] = {0};
        sprintf(format , "%%%ds\n", i + 9);
        ESCREVA_FMT(format, num);
    }

}

/*
   A
  B B
 C   C
D     D
 E   E
  F F
   G
*/
PROCEDIMENTO diamond() {
    INTEIRO i, s, k, m;
    // Solution 1: We use the symmetry around 'D'.
    // The beauty of this code is 'center' variable can be
    // and the rest of the code will work.
    CARACTERE center = 'D';
    INTEIRO depth = center - 'A';
    PARA(i, -depth, depth) {
        /*
         i  #spaces letter  #spaces  letter
        -3  3       A
        -2  2       B       1        B
        -1  1       C       3        C
         0  0       D       5        D
         1  1       E       3        E
         2  2       F       1        F
         3  3       G
        */
        INTEIRO abs_val = i < 0 ? -i : i; // get absolute value, or call abs() of math.h
        CARACTERE format[5];

        sprintf(format, "%%%dc\0", abs_val+1);
        ESCREVA_FMT(format, center + i);

        SE abs_val != depth ENTAO
            sprintf(format, "%%%dc\0", 2*(depth-1-abs_val)+2);
            ESCREVA_FMT(format, center + i);
        FIM_SE
        ESCREVA_LINHA();
    }

    // Solution 2: Use formulae for left and center spaces
    // len/2 points to widest part of the diamond
    // abs(len/2-i) measures the distance from the widest part
    // We can add more chars to data[] and this code will still work
    CARACTERE data[]="ABCDEFG";
    INTEIRO len = strlen(data);

    PARA(i, 0, len - 1) {
        // Left spaces
        for (INTEIRO s = 0; s < abs(len/2-i); s++) {
            ESCREVA(" ");
        }

        SE i != 0 E i != len-1 ENTAO
            ESCREVA_FMT("%c", data[i]);
        FIM_SE

        // Center spaces
        for (INTEIRO s = 0; s < len-2-2*abs(len/2-i); s++) {
            ESCREVA(" ");
        }

        ESCREVA_FMT("%c\n", data[i]);
    }

    // Solution 3: Works but code is long and hard to maintain.
    {
        CARACTERE data[]="ABBCCDDEEFFG";
        for (INTEIRO i = 0; i < strlen(data); i++) {
            // Leading spaces
            for (INTEIRO s = 3; s > i; s--) {
                ESCREVA(" ");
            }

            SE i==0 ENTAO // diamond start point
                ESCREVA_FMT("%c\n", data[0]);
            SENAO_SE i%2 != 0 E i < 6 ENTAO // diamond opening
                ESCREVA_FMT("%c", data[i]);
                PARA(s, 0, i - 1) {
                    ESCREVA(" ");
                }
                ESCREVA_FMT("%c\n", data[i]);
            SENAO_SE i%2 != 0 E i > 6 E i < 11 ENTAO // diamond closing
                SE i==7 ENTAO
                    PARA(k, 6, i - 1) {
                        ESCREVA(" ");
                    }
                    ESCREVA_FMT("%c", data[i]);
                    for (INTEIRO l = 10; l > i; l--) {
                        ESCREVA(" ");
                    }
                    ESCREVA_FMT("%c\n", data[i+1]);
                SENAO_SE i==9 ENTAO
                    PARA(k, 7, i - 1) {
                        ESCREVA(" ");
                    }
                    ESCREVA_FMT("%c", data[i]);
                    for (INTEIRO l = 10; l>i; l--) {
                        ESCREVA(" ");
                    }
                    ESCREVA_FMT("%c\n", data[i+1]);
                FIM_SE
            SENAO_SE i==11 ENTAO // diamond end point
                PARA(m, 0, 2) {
                    ESCREVA(" ");
                }
                ESCREVA_FMT("%c\n", data[i]);
            FIM_SE
        }
    }
}

INICIO
    abcdef();
    ESCREVA_FMT("\n\n");

    numbers();
    ESCREVA_FMT("\n\n");

    diamond();
    ESCREVA_FMT("\n\n");

    RETORNE 0;
FIM
