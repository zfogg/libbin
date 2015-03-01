#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "bin_tests.h"
#include "bin_tests_debug.h"

#include "../src/bin.h"


void binMSBi_test() {
    int r = 1;
    for (int i = 1; i < BIN_BITS-1; ++i) {
        bin b = binNew(1 << i);
        r &= i+1 == binToInt(binMSBi(b));
    }
    r &= BIN_BITS == binToInt(binMSBi(binMAX));
    processTestResults("binMSBi", r);
}


void binMSB_test() {
    int r = 1;
    for (int i = 1; i < BIN_BITS-1; ++i) {
        bin b = binNew(1 << i);
        r &= (1 << i) == binToInt(binMSB(b));
    }
    r &= (1 << (BIN_BITS-1)) == binToInt(binMSB(binMAX));
    processTestResults("binMSB", r);
}


void binNOT_test() {
    int r = 1;
    for (BIN_INT i = 0; i < binToInt(binMAX); ++i)
        r &= binEQ(binNew(~i), binNOT(binNew(i)));
    processTestResults("binNOT", r);
}


void binShiftL_test() {
    int r = 1;
    for (int i = 0; i < BIN_BITS; ++i) {
        bin b = binShiftL(binONE, binNew(i));
        r &= (1 << i) == binToInt(b);
    }
    processTestResults("binShiftL", r);
}


void binShiftL1_test() {
    int r = 1;
    for (int i = 0; i < BIN_BITS; ++i) {
        bin b = binShiftL1(binNew(i));
        r &= (i << 1) == binToInt(b);
    }
    processTestResults("binShiftL1", r);
}


void binShiftOutZerosL_test() {
    processTestResults("binShiftOutZerosL", 0);
}


void binShiftR_test() {
    int r = 1;
    for (int i = 0; i < BIN_BITS; ++i) {
        bin b = binShiftR(binONE, binNew(i));
        r &= (1 >> i) == binToInt(b);
    }
    processTestResults("binShiftR", r);
}


void binShiftR1_test() {
    int r = 1;
    for (int i = 0; i < BIN_BITS; ++i) {
        bin b = binShiftR1(binNew(i));
        r &= (i >> 1) == binToInt(b);
    }
    processTestResults("binShiftR1", r);
}


void binShiftOutZerosR_test() {
    processTestResults("binShiftOutZerosR", 0);
}


void binAND_test() {
    int r = 1;
    for (BIN_INT i = 0; i < binToInt(binMAX); ++i) {
        BIN_INT j = RAND(0, binToInt(binMAX));
        bin b = binAND(binNew(i), binNew(j));
        r &= (i & j) == binToInt(b);
    }
    processTestResults("binAND", r);
}


void binOR_test() {
    int r = 1;
    for (BIN_INT i = 0; i < binToInt(binMAX); ++i) {
        BIN_INT j = RAND(0, binToInt(binMAX));
        bin b = binOR(binNew(i), binNew(j));
        r &= (i | j) == binToInt(b);
    }
    processTestResults("binOR", r);
}


void binXOR_test() {
    int r = 1;
    for (BIN_INT i = 0; i < binToInt(binMAX); ++i) {
        BIN_INT j = RAND(0, binToInt(binMAX));
        bin b = binXOR(binNew(i), binNew(j));
        r &= (i ^ j) == binToInt(b);
    }
    processTestResults("binXOR", r);
}

