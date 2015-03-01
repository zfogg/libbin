#include "boolean.h"
#include "bin.h"
#include "math.h"
#include "bitwise.h"


bool binEQZero(bin x) {
    for (int i = 0; i < BIN_BITS; i++)
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
    for (int i = BIN_BITS-1; i >= 0; i--)
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
