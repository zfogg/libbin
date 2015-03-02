#include <math.h>

#include "bin_tests.h"


void binAdd_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin b2        = binRandr(0, BIN_INT_MAX - bi1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 + bi2) == binToInt(binAdd(b1, b2));
    }
    processTestResults("binAdd", r);
}


void binIncrement_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b  = binRandr(0, BIN_INT_MAX - 1);
        r &= (binToInt(b) + 1) == binToInt(binIncrement(b));
    }
    processTestResults("binIncrement", r);
}


void binSubtract_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin b2        = binRandr(0, bi1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 - bi2) == binToInt(binSubtract(b1, b2));
    }
    processTestResults("binSubtract", r);
}


void binDecrement_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b        = binRandr(1, BIN_INT_MAX);
        bin_int_t bi = binToInt(b);
        r &= (bin_int_t)(bi - 1) == binToInt(binDecrement(b));
    }
    processTestResults("binDecrement", r);
}


void binMultiply_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin b2        = binRandr(0, BIN_INT_MAX / bi1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bin_int_t)(bi1 * bi2) == binToInt(binMultiply(b1, b2));
    }
    processTestResults("binMultiply", r);
}


void binDivide_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binRandr(1, BIN_INT_MAX);
        bin_int_t bi1 = binToInt(b1);
        bin b2        = binRandr(1, bi1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 / bi2) == binToInt(binDivide(b1, b2));
    }
    processTestResults("binDivide", r);
}


void binModulus_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binNew(i);
        bin_int_t bi1 = binToInt(b1);
        bin b2        = binRand();
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 % bi2) == binToInt(binModulus(b1, b2));
    }
    processTestResults("binModulus", r);
}


void binPow_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binNew(i);
        bin b2        = binNew(sqrt(sqrt(BIN_BITS*BIN_BITS - i + 1) + 1));
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bin_int_t)pow(bi1, bi2) == binToInt(binPow(b1, b2));
    }
    processTestResults("binPow", r);
}

