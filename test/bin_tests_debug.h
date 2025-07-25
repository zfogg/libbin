#pragma once

#include "../src/bin.h"


/**
 * @brief Global variable to keep track of test results. If any test fails, the value of this variable will be set to 0.
 */
extern bin_int_t bin_testResults;

/**
 * @brief Process test results, keeping track of whether a test has passed or failed in a global variable.
 * @param testName The name of the test
 * @param results The results of the test
 */
void processTestResults(const char* testName, bin_int_t results);
