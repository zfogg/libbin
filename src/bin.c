#include "bin.h"


bin binNew(bin_int_t n) {
    bin b;
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        b.bits[i] = (n >> i) & 1;
    return b;
}


bin_int_t binToInt(bin x) {
    bin_int_t r = 0;
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        r |= x.bits[i] << i;
    return r;
}


void textcolor(int attr, int fg, int bg) {
    char command[13];
    sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    printf("%s", command);
}


void binPrint(bin x) {
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        printf("%c", x.bits[BIN_BITS - 1 - i] ? 'X' : 'o');
        if ((i+1) % 4 == 0) // Print human-parsable chunks.
            printf("%c", 32);
    }
    puts("");
    fflush(stdout);
}


void binIntPrint(bin_int_t bi) {
    printf("%"PRINTF_BIN_INT"\n", bi);
    fflush(stdout);
}


void binIntPrint2(bin_int_t bi1, bin_int_t bi2) {
    const char* format = "%"PRINTF_BIN_INT" :: %"PRINTF_BIN_INT"\n";
    printf(format, bi1, bi2);
    fflush(stdout);
}


bin_int_t randr(bin_int_t min, bin_int_t max) {
       double scaled = (double)rand()/RAND_MAX;
       return (max - min + 1)*scaled + min;
}

