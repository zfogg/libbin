#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "bin_tests.h"


bin_int_t bin_testResults = 1;

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));
    
    // Initialize JUnit XML output only if requested
    int generate_junit = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--junit") == 0) {
            generate_junit = 1;
            break;
        }
    }
    
    // Also check environment variable
    if (getenv("GENERATE_JUNIT")) {
        generate_junit = 1;
    }
    
    if (generate_junit) {
        initJunitXml();
    }

    // puts("");
    RUN_TIMED_TEST(binMSBi_test);
    RUN_TIMED_TEST(binLSBi_test);
    RUN_TIMED_TEST(binMSB_test);
    RUN_TIMED_TEST(binNOT_test);
    RUN_TIMED_TEST(binShiftL_test);
    RUN_TIMED_TEST(binShiftL1_test);
    RUN_TIMED_TEST(binShiftOutZerosL_test);
    RUN_TIMED_TEST(binShiftR_test);
    RUN_TIMED_TEST(binShiftR1_test);
    RUN_TIMED_TEST(binShiftOutZerosR_test);
    RUN_TIMED_TEST(binAND_test);
    RUN_TIMED_TEST(binOR_test);
    RUN_TIMED_TEST(binXOR_test);
    RUN_TIMED_TEST(binRotateL_test);
    RUN_TIMED_TEST(binRotateR_test);

    puts("");
    RUN_TIMED_TEST(binAdd_test);
    RUN_TIMED_TEST(binIncrement_test);
    RUN_TIMED_TEST(binSubtract_test);
    RUN_TIMED_TEST(binDecrement_test);
    RUN_TIMED_TEST(binMultiply_test);
    RUN_TIMED_TEST(binDivide_test);
    RUN_TIMED_TEST(binModulus_test);
    RUN_TIMED_TEST(binPow_test);
    RUN_TIMED_TEST(binSqrt_test);
    RUN_TIMED_TEST(binLog2Test);
    RUN_TIMED_TEST(binLog10Test);
    RUN_TIMED_TEST(binLogTest);

    puts("");
    RUN_TIMED_TEST(binEQZero_test);
    RUN_TIMED_TEST(binEQOne_test);
    RUN_TIMED_TEST(binEQMax_test);
    RUN_TIMED_TEST(binEQ_test);
    RUN_TIMED_TEST(binGT_test);
    RUN_TIMED_TEST(binLT_test);
    RUN_TIMED_TEST(binGTEQ_test);
    RUN_TIMED_TEST(binLTEQ_test);

    puts("");
    RUN_TIMED_TEST(binRandr_edge_cases_test);
    RUN_TIMED_TEST(binNew_binToInt_edge_cases_test);

    puts("");
    processTestResults("🥳 Pass ALL the tests 🎊", bin_testResults);
    
    // Finalize JUnit XML output if it was enabled
    if (generate_junit) {
        finalizeJunitXml();
    }

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

