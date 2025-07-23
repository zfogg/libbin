#pragma once

#include <stdbool.h>
#include "bin.h"

/**
 * @brief Convert a boolean value to a string representation
 * @param b The boolean value to convert
 * @return "TRUE" if b is true, "FALSE" if b is false
 * 
 * @note This macro converts a boolean value to its string representation.
 *       It's useful for debugging and logging purposes.
 */
#define boolToString(b) ((b) ? "TRUE" : "FALSE")

/**
 * @brief Find the minimum of two binary numbers
 * @param a First binary number
 * @param b Second binary number
 * @return The smaller of the two binary numbers
 * 
 * @note This macro compares two binary numbers and returns the minimum value.
 *       It uses binLT() for comparison.
 */
#define binMin(a,b) (binLT((a),(b)) ? (a) : (b))

/**
 * @brief Find the maximum of two binary numbers
 * @param a First binary number
 * @param b Second binary number
 * @return The larger of the two binary numbers
 * 
 * @note This macro compares two binary numbers and returns the maximum value.
 *       It uses binGT() for comparison.
 */
#define binMax(a,b) (binGT((a),(b)) ? (a) : (b))

/**
 * @brief Check if a binary number equals zero
 * @param x The binary number to check
 * @return true if x equals zero, false otherwise
 */
bool binEQZero(const bin x);

/**
 * @brief Check if a binary number equals one
 * @param x The binary number to check
 * @return true if x equals one, false otherwise
 */
bool binEQOne(const bin x);

/**
 * @brief Check if a binary number equals the maximum value
 * @param x The binary number to check
 * @return true if x equals the maximum value, false otherwise
 */
bool binEQMax(const bin x);

/**
 * @brief Check if two binary numbers are equal
 * @param x First binary number
 * @param y Second binary number
 * @return true if x equals y, false otherwise
 */
bool binEQ(const bin x, const bin y);

/**
 * @brief Check if one binary number is greater than another
 * @param x First binary number
 * @param y Second binary number
 * @return true if x > y, false otherwise
 */
bool binGT(const bin x, const bin y);

/**
 * @brief Check if one binary number is less than another
 * @param x First binary number
 * @param y Second binary number
 * @return true if x < y, false otherwise
 */
bool binLT(const bin x, const bin y);

/**
 * @brief Check if one binary number is greater than or equal to another
 * @param x First binary number
 * @param y Second binary number
 * @return true if x >= y, false otherwise
 */
bool binGTEQ(const bin x, const bin y);

/**
 * @brief Check if one binary number is less than or equal to another
 * @param x First binary number
 * @param y Second binary number
 * @return true if x <= y, false otherwise
 */
bool binLTEQ(const bin x, const bin y);

