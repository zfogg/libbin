#include <stdio.h>
#include <stdlib.h>

#include "bin_tests.h"
#include "bin_tests_debug.h"


void processTestResults(const char* testName, int results) {
    const char* color = results ? GREEN_CC : RED_CC;
    const char* text  = results ? "pass" : "fail";
    printf("\tTesting - %-30s: %s%s%s\n", testName, color, text, WHITE_CC);
    bin_testResults &= results;
}


bin randTestVal() {
    bin r;
    for (int i = 0; i < BIN_BITS; i++)
        r.bits[i] = rand() % 2;
    return r;
}

