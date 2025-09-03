#if defined(__unix__) || defined(__linux__) || defined(unix) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200112L
#endif

#include "bin_tests.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#if defined(__unix__) || defined(__linux__) || defined(unix) || defined(__APPLE__)
#include <unistd.h>
#endif

// JUnit XML state tracking
#define MAX_TESTS 100
static struct {
    char name[64];
    int passed;
    double duration; // Test execution time in seconds
} test_results[MAX_TESTS];
static int test_count = 0;
static time_t start_time;
static int junit_enabled = 0;
static clock_t current_test_start;

// Initialize JUnit XML output
void initJunitXml(void) {
    junit_enabled = 1;
    test_count = 0;
    start_time = time(NULL);
    current_test_start = 0;
}

// Record a test result for JUnit XML output (legacy function for non-timed tests)
void recordJunitTestResult(const char* testName, bin_int_t results) {
    if (!junit_enabled || test_count >= MAX_TESTS) return;
    
    strncpy(test_results[test_count].name, testName, sizeof(test_results[test_count].name) - 1);
    test_results[test_count].name[sizeof(test_results[test_count].name) - 1] = '\0';
    test_results[test_count].passed = results;
    test_results[test_count].duration = 0.0; // No timing for legacy calls
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
    double total_suite_time = difftime(end_time, start_time);
    
    int failure_count = 0;
    double total_test_time = 0.0;
    for (int i = 0; i < test_count; i++) {
        if (!test_results[i].passed) failure_count++;
        total_test_time += test_results[i].duration;
    }
    
    // Use sum of individual test times if available, otherwise fall back to suite time
    double duration = (total_test_time > 0.0) ? total_test_time : total_suite_time;
    
    fprintf(junit_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(junit_file, "<testsuites>\n");
    
    // Get hostname
    char hostname[256] = "unknown";
    #if defined(__unix__) || defined(__linux__) || defined(unix) || defined(__APPLE__)
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        strcpy(hostname, "unix-host");
    }
    #elif defined(_WIN32)
    strcpy(hostname, "windows-host");
    #else
    strcpy(hostname, "unknown-host");
    #endif
    
    // Format ISO 8601 timestamp
    char iso_timestamp[32];
    struct tm* tm_info = gmtime(&start_time);
    strftime(iso_timestamp, sizeof(iso_timestamp), "%Y-%m-%dT%H:%M:%SZ", tm_info);
    
    fprintf(junit_file, "  <testsuite name=\"libbin_tests\" tests=\"%d\" failures=\"%d\" errors=\"0\" skipped=\"0\" time=\"%.3f\" timestamp=\"%s\" hostname=\"%s\">\n", 
            test_count, failure_count, duration, iso_timestamp, hostname);
    
    // Add properties section with environment info
    fprintf(junit_file, "    <properties>\n");
    fprintf(junit_file, "      <property name=\"test.framework\" value=\"libbin-custom\"/>\n");
    fprintf(junit_file, "      <property name=\"test.language\" value=\"C\"/>\n");
    fprintf(junit_file, "      <property name=\"test.standard\" value=\"c2x\"/>\n");
    fprintf(junit_file, "      <property name=\"test.compiler\" value=\"clang\"/>\n");
    #ifdef __VERSION__
    fprintf(junit_file, "      <property name=\"test.compiler.version\" value=\"%s\"/>\n", __VERSION__);
    #endif
    #ifdef BIN_BITS
    fprintf(junit_file, "      <property name=\"libbin.bits\" value=\"%d\"/>\n", BIN_BITS);
    #endif
    #ifdef BIN_INT_MAX
    fprintf(junit_file, "      <property name=\"libbin.int_max\" value=\"%d\"/>\n", BIN_INT_MAX);
    #endif
    fprintf(junit_file, "      <property name=\"test.date\" value=\"%s\"/>\n", iso_timestamp);
    fprintf(junit_file, "    </properties>\n");
    
    for (int i = 0; i < test_count; i++) {
        // Determine test category from name
        const char* category = "misc";
        if (strstr(test_results[i].name, "bin") == test_results[i].name) {
            if (strstr(test_results[i].name, "MSB") || strstr(test_results[i].name, "LSB") || 
                strstr(test_results[i].name, "Shift") || strstr(test_results[i].name, "AND") || 
                strstr(test_results[i].name, "OR") || strstr(test_results[i].name, "XOR") || 
                strstr(test_results[i].name, "NOT") || strstr(test_results[i].name, "Rotate")) {
                category = "bitwise";
            } else if (strstr(test_results[i].name, "Add") || strstr(test_results[i].name, "Sub") || 
                       strstr(test_results[i].name, "Mult") || strstr(test_results[i].name, "Div") || 
                       strstr(test_results[i].name, "Mod") || strstr(test_results[i].name, "Pow") || 
                       strstr(test_results[i].name, "Sqrt") || strstr(test_results[i].name, "Log")) {
                category = "math";
            } else if (strstr(test_results[i].name, "EQ") || strstr(test_results[i].name, "GT") || 
                       strstr(test_results[i].name, "LT")) {
                category = "boolean";
            }
        }
        
        fprintf(junit_file, "    <testcase name=\"%s\" classname=\"libbin.%s\" time=\"%.6f\"", 
                test_results[i].name, category, test_results[i].duration);
        
        if (test_results[i].passed) {
            fprintf(junit_file, ">\n");
            fprintf(junit_file, "      <system-out><![CDATA[Test passed successfully]]></system-out>\n");
            fprintf(junit_file, "    </testcase>\n");
        } else {
            fprintf(junit_file, ">\n");
            fprintf(junit_file, "      <failure message=\"Test assertion failed\" type=\"AssertionError\">\n");
            fprintf(junit_file, "        <![CDATA[Test '%s' failed assertion checks]]>\n", test_results[i].name);
            fprintf(junit_file, "      </failure>\n");
            fprintf(junit_file, "      <system-err><![CDATA[Test failed - check implementation]]></system-err>\n");
            fprintf(junit_file, "    </testcase>\n");
        }
    }
    
    fprintf(junit_file, "  </testsuite>\n");
    fprintf(junit_file, "</testsuites>\n");
    
    fclose(junit_file);
}

// Global variable to track if we're currently timing a test
static int currently_timing_test = 0;

// Run a test function with proper timing
void runTimedTest(const char* testName, void (*testFunction)(void)) {
    currently_timing_test = 1;
    
    // Start timing
    if (junit_enabled) {
        current_test_start = clock();
    }
    
    // Save the current test results state
    bin_int_t old_results = bin_testResults;
    
    // Execute the actual test function
    testFunction();
    
    // Calculate if this specific test passed (compare before/after state)
    bin_int_t test_passed = (bin_testResults == old_results) ? old_results : bin_testResults;
    
    // Calculate test duration
    double duration = 0.0;
    if (junit_enabled && current_test_start != 0) {
        clock_t end_time = clock();
        duration = ((double)(end_time - current_test_start)) / CLOCKS_PER_SEC;
    }
    
    // Record the result with timing
    if (junit_enabled && test_count < MAX_TESTS) {
        strncpy(test_results[test_count].name, testName, sizeof(test_results[test_count].name) - 1);
        test_results[test_count].name[sizeof(test_results[test_count].name) - 1] = '\0';
        test_results[test_count].passed = test_passed;
        test_results[test_count].duration = duration;
        test_count++;
    }
    
    currently_timing_test = 0;
}

// Print the results of a test to the terminal in a nice format.
void processTestResults(const char* testName, const bin_int_t results) {
    bin_testResults &= results;
    const char* color  = results ? CC_GREEN : CC_RED;
    const char* text   = results ? "pass" : "fail";
    const char* format = "\tTesting - %-30s: %s%s%s\n";
    printf(format, testName, color, text, CC_RESET);
    fflush(stdout);
    
    // Only record for JUnit XML if we're not already timing this test
    if (!currently_timing_test) {
        recordJunitTestResult(testName, results);
    }
}
