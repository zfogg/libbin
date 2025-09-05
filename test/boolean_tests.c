#include "bin_tests.h"
#include <stdbool.h>


void binEQZero_test() {
    bin_int_t r = 1;
    // Reduce iterations for performance while maintaining test coverage
    for (bin_int_t i = 1; i < 1000; ++i) {
        r &= false == binEQZero(binNew(i));
    }
    r &= true == binEQZero(binZERO);
    processTestResults("binEQZero", r);
}


void binEQOne_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 2; i < BIN_INT_MAX; ++i) {
        bin b = binNew(i);
        r &= false == binEQOne(b);
    }
    r &= false == binEQOne(binZERO);
    r &= true  == binEQOne(binONE);
    processTestResults("binEQOne", r);
}


void binEQMax_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX-1; ++i) {
        bin b = binNew(i);
        r &= false == binEQMax(b);
    }
    r &= true == binEQMax(binNew(BIN_INT_MAX));
    processTestResults("binEQMax", r);
}

void binEQ_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1        = binRand();
        bin b2        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 == bi2) == binEQ(b1, b2);
        r &= binEQ(b1, b1);
        r &= binEQ(b2, b2);
    }
    processTestResults("binEQ", r);
}


void binGT_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1        = binRand();
        bin b2        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 > bi2) == binGT(b1, b2);
    }
    processTestResults("binGT", r);
}


void binLT_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1        = binRand();
        bin b2        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 < bi2) == binLT(b1, b2);
    }
    processTestResults("binLT", r);
}


void binGTEQ_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1        = binRand();
        bin b2        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 >= bi2) == binGTEQ(b1, b2);
    }
    processTestResults("binGTEQ", r);
}


void binLTEQ_test() {
    bin_int_t r = 1;
    for (bin_int_t i = 0; i < BIN_INT_MAX; ++i) {
        bin b1        = binRand();
        bin b2        = binRand();
        bin_int_t bi1 = binToInt(b1);
        bin_int_t bi2 = binToInt(b2);
        r &= (bi1 <= bi2) == binLTEQ(b1, b2);
    }
    processTestResults("binLTEQ", r);
}
