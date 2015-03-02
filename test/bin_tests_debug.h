#pragma once

#include "../src/bin.h"


extern bin_int_t bin_testResults;

void processTestResults(const char* testName, bin_int_t results);

bin binRandr(bin_int_t min, bin_int_t max);

bin binRand();

