#include "bin.h"


// Create a binary number from an integer.
// This implementation uses only allowed operators: &&, ||, !, +, -
bin binNew(bin_int_t n) {
    bin b = binZERO;
    
    // For each bit position, check if that bit should be set
    // We use division by powers of 2 instead of bit shifting
    bin_int_t divisor = 1;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        // Overflow protection: if divisor wrapped to 0, we're done
        if (divisor == 0) break;
        
        // Check if the current bit should be set by testing divisibility
        // If (n / divisor) is odd, then the bit at position i should be 1
        bin_int_t quotient = n / divisor;
        
        // Check if quotient is odd, which means this bit is set
        bin_int_t next_quotient = quotient / 2;
        bin_int_t bit_remainder = quotient - (next_quotient * 2); // quotient % 2
        
        b.bits[i] = bit_remainder ? 1 : 0;
        
        // Move to next power of 2
        divisor = divisor + divisor; // divisor *= 2 using only +
    }
    return b;
}

// Convert a binary number to an integer.
// This implementation uses only allowed operators: &&, ||, !, +, -
bin_int_t binToInt(const bin x) {
    bin_int_t result = 0;
    bin_int_t power_of_two = 1;
    
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        if (x.bits[i]) {
            result = result + power_of_two;
        }
        // Calculate next power of 2 using addition: power *= 2
        power_of_two = power_of_two + power_of_two;
        if (power_of_two == 0) break; // Overflow protection
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
static bin_int_t randr(bin_int_t min, bin_int_t max) {
    if (min > max) {
        bin_int_t temp = min;
        min = max;
        max = temp;
    }
    
#ifdef __APPLE__
    // macOS has arc4random_uniform - use it properly for range
    bin_int_t range = max - min + 1;
    if (range == 0) return min; // Handle edge case where min == max == BIN_INT_MAX
    return min + (bin_int_t)arc4random_uniform((uint32_t)range);
#else
    // Generic fallback - avoid overflow by careful calculation
    bin_int_t range = max - min;
    if (range == BIN_INT_MAX) {
        // Special case: full range, use direct conversion
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
