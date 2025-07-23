#include "bin_tests.h"


// Print the results of a test to the terminal in a nice format.
void processTestResults(const char* testName, const bin_int_t results) {
    bin_testResults &= results;
    const char* color  = results ? CC_GREEN : CC_RED;
    const char* text   = results ? "pass" : "fail";
    const char* format = "\tTesting - %-30s: %s%s%s\n";
    printf(format, testName, color, text, CC_RESET);
    fflush(stdout);
}
