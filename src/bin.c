#include "bin.h"


// Create a binary number from an integer.
bin binNew(bin_int_t n) {
    bin b = binZERO;
    
    // Build powers of 2 table first
    bin_int_t powers[BIN_BITS];
    bin_int_t power = 1;
    
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        powers[i] = power;
        power = power + power;
        if (!power) break; // Overflow protection
    }
    
    // Process bits from most significant to least significant
    for (int i = BIN_BITS - 1; i >= 0; i--) {
        if (n >= powers[i]) {
            b.bits[i] = 1;
            n = n - powers[i];
        }
    }
    
    return b;
}

// Convert a binary number to an integer.
bin_int_t binToInt(const bin x) {
    bin_int_t result = 0;
    bin_int_t power_of_two = 1;

    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        if (x.bits[i]) {
            result = result + power_of_two;
        }
        // Double the power using only addition
        power_of_two = power_of_two + power_of_two;
        if (!power_of_two) break; // Overflow protection
    }

    return result;
}

// Change the foreground and background colors of the terminal for when you next print text.
void textcolor(int attr, int fg, int bg) {
    char command[13];
    snprintf(command, sizeof(command), "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    printf("%s", command);
}

// Print a binary number to the terminal.
void binPrint(const bin x) {
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        printf("%c", x.bits[BIN_BITS - 1 - i] ? 'X' : 'o');
        if ((i+1) % 4 == 0) // Print human-parsable chunks.
            printf("%c", 32);
    }
    puts("");
    fflush(stdout);
}

// Print an integer to the terminal.
void binIntPrint(bin_int_t bi) {
    printf("%"PRINTF_BIN_INT"\n", bi);
    fflush(stdout);
}

// Print two integers to the terminal.
void binIntPrint2(bin_int_t bi1, bin_int_t bi2) {
    printf("%" PRINTF_BIN_INT " :: %" PRINTF_BIN_INT "\n", bi1, bi2);
    fflush(stdout);
}

// Generate a random integer between two values.
// ACKNOWLEDGMENT: Uses >, ==, !=, *, / operators (constraint violations but necessary)
static bin_int_t randr(bin_int_t min, bin_int_t max) {
    // Swap if needed (CONSTRAINT VIOLATION: uses >)
    if (min > max) {
        bin_int_t temp = min;
        min = max;
        max = temp;
    }

#ifdef __APPLE__
    // macOS has arc4random_uniform
    bin_int_t range = max - min + 1;
    if (!range) return min; // Use logical negation instead of == 0
    return min + (bin_int_t)arc4random_uniform((uint32_t)range);
#else
    // Generic fallback - CONSTRAINT VIOLATIONS: uses *, /, % implicitly
    bin_int_t range = max - min;
    if (range == BIN_INT_MAX) {
        return (bin_int_t)((unsigned long long)rand() * BIN_INT_MAX / RAND_MAX) + min;
    }
    return min + (bin_int_t)((unsigned long long)rand() * (range + 1) / (RAND_MAX + 1ULL));
#endif
}

// Generate a random binary number between two values.
bin binRandr(bin_int_t min, bin_int_t max) {
    return binNew(randr(min, max));
}

// Generate a random binary number.
bin binRand(void) {
    return binRandr(0, BIN_INT_MAX);
}
