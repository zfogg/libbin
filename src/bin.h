#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "16.h"

#include "boolean.h"
#include "math.h"
#include "bitwise.h"


#define CC_RESET "\x1B[0m"
#define CC_RED   "\x1B[31m"
#define CC_GREEN "\x1B[32m"


/**
 * @brief Create a binary number from an integer
 * @param n The integer to convert
 * @return A binary number representation
 */
bin binNew(bin_int_t n);

/**
 * @brief Convert a binary number to an integer
 * @param x The binary number to convert
 * @return The integer representation
 */
bin_int_t binToInt(const bin x);

/**
 * @brief Change the foreground and background colors of the terminal for when you next print text.
 * @param attr The attribute to use (0 = normal, 1 = bold, 2 = dim, 3 = italic, 4 = underline, 5 = blink, 6 = reverse, 7 = hidden)
 * @param fg The foreground color to use (0 = black, 1 = red, 2 = green, 3 = yellow, 4 = blue, 5 = magenta, 6 = cyan, 7 = white)
 * @param bg The background color to use (0 = black, 1 = red, 2 = green, 3 = yellow, 4 = blue, 5 = magenta, 6 = cyan, 7 = white)
 */
void textcolor(int attr, int fg, int bg);

/**
 * @brief Print a binary number to stdout
 * @param x The binary number to print
 */
void binPrint(const bin x);

/**
 * @brief Print an integer to stdout
 * @param x The integer to print
 */
void binIntPrint(bin_int_t x);

/**
 * @brief Print two integers to stdout
 * @param bi1 First integer
 * @param bi2 Second integer
 */
void binIntPrint2(bin_int_t bi1, bin_int_t bi2);


// Random number generation

/**
 * @brief Generate a random binary number between two values
 * @param min The minimum value
 * @param max The maximum value
 * @return A random binary number between two values
 */ 
bin binRandr(bin_int_t min, bin_int_t max);


/**
 * @brief Generate a random binary number
 * @return A random binary number
 */ 
bin binRand(void);