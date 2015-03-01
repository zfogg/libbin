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
    printf("%s", WHITE_CC);
    char* color;
    BIN_INT bit;
    for (int i = 0; i < BIN_BITS; i++) {
        bit = x.bits[BIN_BITS - 1 - i];
        color = bit ? GREEN_CC : RED_CC;
        printf("%s%d%s", color, bit, WHITE_CC);
        if ((i+1) % 4 == 0)
            printf(" ");
    }
    printf("\n");
}

