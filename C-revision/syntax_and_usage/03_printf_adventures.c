#include <stdio.h>
#include <limits.h>
#include <float.h>

/*
    https://en.wikipedia.org/wiki/Printf_format_string
    https://en.wikipedia.org/wiki/Escape_sequences_in_C
    https://www.codingeek.com/tutorials/c-programming/escape-sequences-and-format-specifiers-in-c-programming-language/

    If this helps at all:
    %[parameter][flags][width][.precision][length]type
*/

int main(int argc, char** argv) {
    printf("CHAR_BIT    :   %d\n", CHAR_BIT);
    printf("CHAR_MAX    :   %d\n", CHAR_MAX);
    printf("CHAR_MIN    :   %d\n", CHAR_MIN);

    /* %x is only for unsigned ints */
    printf("CHAR_BIT (hex)    :   %x\n", CHAR_BIT);
    printf("CHAR_BIT (hex)    :   %#x\n", CHAR_BIT);
    printf("CHAR_MAX (hex)    :   %x = 127 = 112 + 15 = 16 * 7 + 15\n", CHAR_MAX);
    printf("CHAR_MIN (hex)    :   %x\n", CHAR_MIN);

    printf("\n\n");

    /* l := tells printf to expect long-sized integer */
    /* u := unsigned integer */
    printf("Storage size for float : %lu \n", sizeof(float));
    printf("FLT_MAX     :   %g\n", (float) FLT_MAX);
    printf("FLT_MAX     :   %f\n", (float) FLT_MAX);
    printf("FLT_MIN     :   %g\n", (float) FLT_MIN);
    printf("-FLT_MAX    :   %g\n", (float) -FLT_MAX);
    printf("-FLT_MIN    :   %g\n", (float) -FLT_MIN);
    printf("DBL_MAX     :   %g\n", (double) DBL_MAX);
    printf("DBL_MIN     :   %g\n", (double) DBL_MIN);
    printf("-DBL_MAX     :  %g\n", (double) -DBL_MAX);
    printf("Precision value: %d\n", FLT_DIG );

    printf("\n\n");

    printf("Let's try some decimal configurations for fun here.\n");
    printf("FLT_MAX (%%g)    :   %g\n", (float) FLT_MAX);
    printf("FLT_MAX (%%f)    :   %f\n", (float) FLT_MAX);
    printf("FLT_MAX (%%f)    :   %f\n", (float) FLT_MAX);
    printf("3.123456789 (%%.*f, 2)    :   %.*f\n", 2, (float) 3.123456789);
    printf("3.123456789 (%%.2f)       :   %.2f\n", (float) 3.123456789);
    printf("3.123456789 (%%.*f, 5)    :   %.*f\n", 5, (float) 3.123456789);
    printf("3.123456789 (%%.5f)       :   %.5f\n", (float) 3.123456789);
    printf("POSITION OF PARAMETER: %3$d %1$d %2$d;\n", 16, 17, 11);
    printf("POSITION OF PARAMETER: %3$d %1$04d %2$d;\n", 16, 17, 11);
    return 0;
}