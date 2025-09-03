#include <time.h>

#include "bin_tests.h"


bin_int_t bin_testResults = 1;

int main(int argc, char* argv[]) {
    (void)(argc); (void)(argv);
    srand((unsigned int)time(NULL));

    // puts("");
    binMSBi_test            ();
    binLSBi_test            ();
    binMSB_test             ();
    binNOT_test             ();
    binShiftL_test          ();
    binShiftL1_test         ();
    binShiftOutZerosL_test  ();
    binShiftR_test          ();
    binShiftR1_test         ();
    binShiftOutZerosR_test  ();
    binAND_test             ();
    binOR_test              ();
    binXOR_test             ();
    binRotateL_test         ();
    binRotateR_test         ();

    puts("");
    binAdd_test             ();
    binIncrement_test       ();
    binSubtract_test        ();
    binDecrement_test       ();
    binMultiply_test        ();
    binDivide_test          ();
    binModulus_test         ();
    binPow_test             ();
    binSqrt_test            ();
    binLog2Test             ();
    binLog10Test            ();
    binLogTest              ();

    puts("");
    binEQZero_test          ();
    binEQOne_test           ();
    binEQMax_test           ();
    binEQ_test              ();
    binGT_test              ();
    binLT_test              ();
    binGTEQ_test            ();
    binLTEQ_test            ();

    puts("");
    binRandr_edge_cases_test();
    binNew_binToInt_edge_cases_test();

    puts("");
    processTestResults("🥳 Pass ALL the tests 🎊", bin_testResults);

    return !bin_testResults;
}

// Test edge cases for random number generation
void binRandr_edge_cases_test() {
    bin_int_t r = 1;
    
    // Test edge case: min == max
    bin b1 = binRandr(100, 100);
    r &= 100 == binToInt(b1);
    
    // Test edge case: min > max (should swap)
    bin b2 = binRandr(200, 50);
    bin_int_t val2 = binToInt(b2);
    r &= val2 >= 50 && val2 <= 200;
    
    // Test edge case: full range
    bin b3 = binRandr(0, BIN_INT_MAX);
    bin_int_t val3 = binToInt(b3);
    r &= val3 >= 0 && val3 <= BIN_INT_MAX;
    
    processTestResults("binRandr_edge_cases", r);
}

// Test that binNew/binToInt work correctly for edge cases
void binNew_binToInt_edge_cases_test() {
    bin_int_t r = 1;
    
    // Test boundary values
    r &= 0 == binToInt(binNew(0));
    r &= 1 == binToInt(binNew(1));
    r &= BIN_INT_MAX == binToInt(binNew(BIN_INT_MAX));
    
    // Test powers of 2
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        bin_int_t power = 1;
        for (bin_int_t j = 0; j < i; j++) {
            power = power + power; // power *= 2
        }
        r &= power == binToInt(binNew(power));
    }
    
    // Test round-trip consistency for all values
    for (bin_int_t i = 0; i < 1000; i++) { // Test subset for speed
        r &= i == binToInt(binNew(i));
    }
    
    processTestResults("binNew_binToInt_edge_cases", r);
}

