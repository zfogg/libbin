#pragma once

#include <stdint.h>
#include <inttypes.h>

/** @brief Number of bits in the binary representation type */
#define BIN_BITS       16

/** @brief Integer type used for individual bits */
#define bin_int_t      uint16_t

/** @brief Maximum value for the binary integer type */
#define BIN_INT_MAX    UINT16_MAX

/** @brief printf format specifier for binary integer type */
#define PRINTF_BIN_INT PRIu16

/**
 * @brief Structure representing a 16-bit binary number
 * 
 * The bin structure contains an array of 16 bits, where each bit
 * is represented as a uint16_t value of either 0 or 1. The bits are
 * stored in little-endian order, with the least significant bit at index 0.
 */
typedef struct bin {
    bin_int_t bits[BIN_BITS]; /**< Array of BIN_BITS bits (0 or 1) */
} bin;

/**
 * @brief Constant representing binary zero (all bits set to 0)
 * 
 * This constant provides a convenient way to initialize binary
 * numbers to zero or compare against zero.
 */
static const bin binZERO = {
    .bits = {
        0, 0, 0, 0,
        0, 0, 0, 0,

        0, 0, 0, 0,
        0, 0, 0, 0,
    }
};

/**
 * @brief Constant representing binary one
 * 
 * This constant represents the binary value 1, with only the
 * least significant bit set to 1 and all other bits set to 0.
 */
static const bin binONE = {
    .bits = {
        1, 0, 0, 0,
        0, 0, 0, 0,

        0, 0, 0, 0,
        0, 0, 0, 0,
    }
};

/**
 * @brief Constant representing the maximum binary value (all bits set to 1)
 * 
 * This constant represents the maximum possible 16-bit binary value,
 * with all 16 bits set to 1. This is equivalent to 65535 in decimal.
 */
static const bin binMAX = {
    .bits = {
        1, 1, 1, 1,
        1, 1, 1, 1,

        1, 1, 1, 1,
        1, 1, 1, 1,
    }
};

/**
 * @brief Pre-computed powers of 2 for ultra-pure binNew implementation
 * 
 * This array contains the powers of 2 from 2^0 to 2^15, allowing
 * binNew() to avoid all arithmetic operations except subtraction and comparison.
 * This is the ultimate constraint-faithful approach for bit extraction.
 */
static const bin_int_t binPOWERS_OF_TWO[BIN_BITS] = {
    1, 2, 4, 8, 16, 32, 64, 128,
    256, 512, 1024, 2048, 4096, 8192, 16384, 32768
};

/**
 * @brief Additional pre-computed bin constants for ultra-pure loop control
 * 
 * These constants allow loops to use bin arithmetic instead of integer arithmetic,
 * eliminating ++ and -- operators from all loop control structures.
 */
static const bin binSIXTEEN = {
    .bits = {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}  // 16 in binary
};

static const bin binFIFTEEN = {
    .bits = {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}  // 15 in binary
};

static const bin binFOUR = {
    .bits = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0}  // 4 in binary
};
