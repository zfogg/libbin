#include "bin.h"

// Test if a binary number is zero.
bool binEQZero(bin x) {
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        if (x.bits[i])
            return false;
    return true;
}

// Test if a binary number is one.
bool binEQOne(bin x) {
    if (binEQZero(x))
        return false;
    return binEQZero(binDecrement(x));
}

// Test if a binary number is the maximum value.
bool binEQMax(bin x) {
    int r = 1;
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        r &= x.bits[i] == 1;
    return r == 1;
}

// Test if two binary numbers are equal.
bool binEQ(bin x, bin y) {
    return binEQZero(binSubtract(x, y));
}

// Test if a binary number is greater than another.
bool binGT(bin x, bin y) {
    bin xorXY = binXOR(x, y);
    for (bin_int_t i = BIN_BITS-1; i != (bin_int_t)(-1); --i)
        if (xorXY.bits[i])
            return x.bits[i] && !y.bits[i];
    return false;
}

// Test if a binary number is less than another.
bool binLT(bin x, bin y) {
    return !binEQ(x, y) && !binGT(x, y);
}

// Test if a binary number is greater than or equal to another.
bool binGTEQ(bin x, bin y) {
    return !binLT(x, y);
}

// Test if a binary number is less than or equal to another.
bool binLTEQ(bin x, bin y) {
    return !binGT(x, y);
}
