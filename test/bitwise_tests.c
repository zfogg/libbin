#include "bin_tests.h"


void binMSBi_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 1; i < BIN_BITS-1; ++i) {
        bin b = binNew(1 << i);
        r &= i+1 == binToInt(binMSBi(b));
    }
    r &= BIN_BITS == binToInt(binMSBi(binMAX));
    processTestResults("binMSBi", r);
}


void binMSB_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 1; i < BIN_BITS-1; ++i) {
        bin b = binNew(1 << i);
        r &= (1 << i) == binToInt(binMSB(b));
    }
    r &= (1 << (BIN_BITS-1)) == binToInt(binMSB(binMAX));
    processTestResults("binMSB", r);
}


void binNOT_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        r &= (bin_int_t)~i == binToInt(binNOT(binNew(i)));
    }
    processTestResults("binNOT", r);
}


void binShiftL_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binRand();
        bin b2        = binRandr(0, BIN_BITS);
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bin_int_t)(bi1 << bi2) == binToInt(binShiftL(b1, b2));
    }
    processTestResults("binShiftL", r);
}


void binShiftL1_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS; ++i) {
        bin b = binShiftL1(binNew(i));
        r &= (i << 1) == binToInt(b);
    }
    processTestResults("binShiftL1", r);
}


void binShiftOutZerosL_test() {
    processTestResults("binShiftOutZerosL", 0);
}


void binShiftR_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_BITS*BIN_BITS; ++i) {
        bin b1        = binRand();
        bin b2        = binRandr(0, BIN_BITS);
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= bi1 >> bi2 == binToInt(binShiftR(b1, b2));
    }
    processTestResults("binShiftR", r);
}


void binShiftR1_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b        = binRand();
        bin_int_t bi = binToInt(b);
        r &= (bi >> 1) == binToInt(binShiftR1(b));
    }
    processTestResults("binShiftR1", r);
}


void binShiftOutZerosR_test() {
    processTestResults("binShiftOutZerosR", 0);
}


void binAND_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1 = binRand();
        bin b2 = binRand();
        bin b  = binAND(b1, b2);
        r &= (binToInt(b1) & binToInt(b2)) == binToInt(b);
    }
    processTestResults("binAND", r);
}


void binOR_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1 = binRand();
        bin b2 = binRand();
        bin b  = binOR(b1, b2);
        r &= (binToInt(b1) | binToInt(b2)) == binToInt(b);
    }
    processTestResults("binOR", r);
}


void binXOR_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1 = binRand();
        bin b2 = binRand();
        bin b  = binXOR(b1, b2);
        r &= (binToInt(b1) ^ binToInt(b2)) == binToInt(b);
    }
    processTestResults("binXOR", r);
}

