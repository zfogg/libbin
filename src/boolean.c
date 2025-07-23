#include "bin.h"

// Test if a binary number is zero.
bool binEQZero(const bin x) {
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        if (x.bits[i])
            return false;
    }
    return true;
}

// Test if a binary number is one.
bool binEQOne(const bin x) {
    // Check if the least significant bit is 1 and all others are 0
    if (!x.bits[0])
        return false;
    for (bin_int_t i = 1; i < BIN_BITS; i++) {
        if (x.bits[i])
            return false;
    }
    return true;
}

// Test if a binary number is the maximum value.
bool binEQMax(const bin x) {
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        if (!x.bits[i])
            return false;
    }
    return true;
}

// Test if two binary numbers are equal.
bool binEQ(const bin x, const bin y) {
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        if (x.bits[i] != y.bits[i])
            return false;
    }
    return true;
}

// Test if a binary number is greater than another.
bool binGT(const bin x, const bin y) {
    for (int i = BIN_BITS-1; i >= 0; --i) {
        if (x.bits[i] != y.bits[i])
            return x.bits[i] && !y.bits[i];
    }
    return false;
}

// Test if a binary number is less than another.
bool binLT(const bin x, const bin y) {
    return !binEQ(x, y) && !binGT(x, y);
}

// Test if a binary number is greater than or equal to another.
bool binGTEQ(const bin x, const bin y) {
    return !binLT(x, y);
}

// Test if a binary number is less than or equal to another.
bool binLTEQ(const bin x, const bin y) {
    return !binGT(x, y);
}
