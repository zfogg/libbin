#include "bin_tests.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

// JUnit XML state tracking
#define MAX_TESTS 100
static struct {
    char name[64];
    int passed;
} test_results[MAX_TESTS];
static int test_count = 0;
static time_t start_time;
static int junit_enabled = 0;

// Initialize JUnit XML output
void initJunitXml(void) {
    junit_enabled = 1;
    test_count = 0;
    start_time = time(NULL);
}

// Record a test result for JUnit XML output
void recordJunitTestResult(const char* testName, bin_int_t results) {
    if (!junit_enabled || test_count >= MAX_TESTS) return;
    
    strncpy(test_results[test_count].name, testName, sizeof(test_results[test_count].name) - 1);
    test_results[test_count].name[sizeof(test_results[test_count].name) - 1] = '\0';
    test_results[test_count].passed = results;
    test_count++;
}

// Finalize and write JUnit XML output to file
void finalizeJunitXml(void) {
    if (!junit_enabled) return;
    
    FILE* junit_file = fopen("junit.xml", "w");
    if (!junit_file) {
        fprintf(stderr, "Warning: Could not create junit.xml file\n");
        return;
    }
    
    time_t end_time = time(NULL);
    double duration = difftime(end_time, start_time);
    
    int failure_count = 0;
    for (int i = 0; i < test_count; i++) {
        if (!test_results[i].passed) failure_count++;
    }
    
    fprintf(junit_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(junit_file, "<testsuites>\n");
    fprintf(junit_file, "  <testsuite name=\"libbin_tests\" tests=\"%d\" failures=\"%d\" time=\"%.3f\" timestamp=\"%ld\">\n", 
            test_count, failure_count, duration, (long)start_time);
    
    for (int i = 0; i < test_count; i++) {
        fprintf(junit_file, "    <testcase name=\"%s\" classname=\"libbin\"", test_results[i].name);
        if (test_results[i].passed) {
            fprintf(junit_file, "/>\n");
        } else {
            fprintf(junit_file, ">\n");
            fprintf(junit_file, "      <failure message=\"Test failed\" type=\"AssertionError\"></failure>\n");
            fprintf(junit_file, "    </testcase>\n");
        }
    }
    
    fprintf(junit_file, "  </testsuite>\n");
    fprintf(junit_file, "</testsuites>\n");
    
    fclose(junit_file);
}

// Print the results of a test to the terminal in a nice format.
void processTestResults(const char* testName, const bin_int_t results) {
    bin_testResults &= results;
    const char* color  = results ? CC_GREEN : CC_RED;
    const char* text   = results ? "pass" : "fail";
    const char* format = "\tTesting - %-30s: %s%s%s\n";
    printf(format, testName, color, text, CC_RESET);
    fflush(stdout);
    
    // Also record for JUnit XML
    recordJunitTestResult(testName, results);
}
