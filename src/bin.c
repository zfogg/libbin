#include "bin.h"


// Create a binary number from an integer.
bin binNew(bin_int_t n) {
    bin b;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        b.bits[i] = (n >> i) & 1;
    }
    return b;
}

// Convert a binary number to an integer.
bin_int_t binToInt(const bin x) {
    bin_int_t r = 0;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        r |= x.bits[i] << i;
    }
    return r;
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
#ifdef __APPLE__
    // macOS has arc4random_uniform
    double scaled = (double)arc4random_uniform(UINT32_MAX) / UINT32_MAX;
#else
    // Generic fallback
    double scaled = (double)rand() / RAND_MAX;
#endif
    return (max - min + 1)*scaled + min;
}

// Generate a random binary number between two values.
bin binRandr(bin_int_t min, bin_int_t max) {
    if (min > max) {
        bin_int_t temp = min;
        min = max;
        max = temp;
    }
    return binNew(randr(min, max));
}

// Generate a random // Generate a random binary number.
bin binRand(void) {
    return binRandr(0, BIN_INT_MAX);
}