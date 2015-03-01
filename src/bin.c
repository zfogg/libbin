#include <stdlib.h>
#include <stdio.h>

#include "bin.h"


bin binNew(BIN_INT n) {
    bin r;
    for (int i = 0; i < BIN_BITS; i++)
        r.bits[i] = (n >> i) & 1;
    return r;
}


BIN_INT binToInt(bin x) {
    int r = 0;
    for (int i = 0; i < BIN_BITS; i++)
        r |= x.bits[i] << i;
    return r;
}


void binPrint(bin x) {
    for (int i = 0; i < BIN_BITS; i++) {
        BIN_INT bit = x.bits[BIN_BITS - 1 - i];
        char* color = bit ? GREEN_CC : RED_CC;
        printf("%s%d", color, bit);
        if ((i+1) % 4 == 0) // Print human-parsable chunks.
            printf(" ");
    }
    puts(WHITE_CC);
    fflush(stdout);
}

