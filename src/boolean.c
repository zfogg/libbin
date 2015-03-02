#include "bin.h"


bool binEQZero(bin x) {
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        if (x.bits[i])
            return FALSE;
    return TRUE;
}

bool binEQOne(bin x) {
    return binEQZero(binDecrement(x));
}

bool binEQ(bin x, bin y) {
    return binEQZero(binSubtract(x, y));
}


bool binGT(bin x, bin y) {
    bin xorXY = binXOR(x, y);
    for (bin_int_t i = BIN_BITS-1; i != (bin_int_t)(-1); --i)
        if (xorXY.bits[i])
            return x.bits[i] && !y.bits[i];
    return FALSE;
}

bool binLT(bin x, bin y) {
    return !binEQ(x, y) && !binGT(x, y);
}


bool binGTEQ(bin x, bin y) {
    return !binLT(x, y);
}

bool binLTEQ(bin x, bin y) {
    return !binGT(x, y);
}
