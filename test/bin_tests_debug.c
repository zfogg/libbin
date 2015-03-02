#include "bin_tests.h"


void processTestResults(const char* testName, const bin_int_t results) {
    bin_testResults &= results;
    const char* color  = results ? CC_GREEN : CC_RED;
    const char* text   = results ? "pass" : "fail";
    const char* format = "\tTesting - %-30s: %s%s%s\n";
    printf(format, testName, color, text, CC_RESET);
    fflush(stdout);
}


bin binRandr(bin_int_t min, bin_int_t max) {
    return binNew(randr(min, max));
}


bin binRand() {
    return binRandr(0, binToInt(binMAX));
}

