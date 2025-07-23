#pragma once

#include "bin.h"

/**
 * @brief Add two binary numbers
 * 
 * Performs binary addition of two binary numbers. The function handles
 * binary arithmetic with proper carry propagation.
 * 
 * @param x The first binary number (addend)
 * @param y The second binary number (addend)
 * @return The sum of x and y as a binary number
 * 
 * @note This function performs standard binary addition with carry handling.
 *       The result is a binary number representing the arithmetic sum.
 */
bin binAdd(const bin x, const bin y);

/**
 * @brief Increment a binary number by one
 * @param x The binary number to increment
 * @return The incremented binary number (x + 1)
 * 
 * @note Don't try to increment the maximum binary number value.
 *       Currently this won't crash but it should.
 */
bin binIncrement(const bin x);

/**
 * @brief Subtract two binary numbers
 * 
 * Performs binary subtraction of y from x. The function handles
 * binary arithmetic with proper borrow propagation.
 * 
 * @param x The binary number to subtract from (minuend)
 * @param y The binary number to subtract (subtrahend)
 * @return The difference of x and y as a binary number (x - y)
 * 
 * @note This function performs standard binary subtraction with borrow handling.
 *       If y > x, the result will be the two's complement representation.
 */
bin binSubtract(const bin x, const bin y);

/**
 * @brief Decrement a binary number by one
 * @param x The binary number to decrement
 * @return The decremented binary number (x - 1)
 * 
 * @note Don't try to decrement the minimum binary number value (0).
 */
bin binDecrement(const bin x);

/**
 * @brief Multiply two binary numbers
 * 
 * Performs binary multiplication of two binary numbers using
 * the standard recursive multiplication algorithm.
 * 
 * @param x The first binary number (multiplicand)
 * @param y The second binary number (multiplier)
 * @return The product of x and y as a binary number
 */
bin binMultiply(const bin x, const bin y);

/**
 * @brief Divide two binary numbers
 * 
 * Performs binary division of x by y using the standard
 * long division algorithm.
 * 
 * @param x The binary number to divide (dividend)
 * @param y The binary number to divide by (divisor)
 * @return The quotient of x divided by y as a binary number
 * 
 * @note This function assert()s that the divisor is not zero.
 */
bin binDivide(const bin x, const bin y);

/**
 * @brief Calculate the remainder of division
 * 
 * Performs binary division and returns the remainder
 * (modulo operation).
 * 
 * @param x The binary number to divide (dividend)
 * @param y The binary number to divide by (divisor)
 * @return The remainder of x divided by y as a binary number
 * 
 * @note This function assert()s that the divisor is not zero.
 *       
 */
bin binModulus(const bin x, const bin y);

/**
 * @brief Raise a binary number to a power
 * 
 * Calculates x raised to the power of y (x^y).
 * 
 * @param x The base binary number
 * @param y The exponent binary number
 * @return x raised to the power of y as a binary number
 * 
 * @note This function implements binary exponentiation.
 *       For y = 0, the result is 1.
 *       For y = 1, the result is x.
 *       Large exponents may cause overflow.
 */
bin binPow(const bin x, const bin y);

/**
 * @brief Calculate the square root of a binary number
 * @param x The binary number to calculate the square root of
 * @return The square root of x as a binary number
 * 
 * @note This function implements the Newton-Raphson method for square root calculation.
 */
bin binSqrt(const bin x);

/**
 * @brief Calculate the base2 logarithm of a binary number
 * @param x The binary number to calculate the logarithm of
 * @return The logarithm of x as a binary number
 */
bin binLog2(const bin x);

/**
 * @brief Calculate the base10 logarithm of a binary number
 * @param x The binary number to calculate the logarithm of
 * @return The logarithm of x as a binary number
 */
bin binLog10(const bin x);

/**
 * @brief Calculate the natural logarithm of a binary number
 * @param x The binary number to calculate the logarithm of
 * @return The logarithm of x as a binary number
 * 
 * @note This function implements the natural logarithm using the Taylor series expansion.
 */
bin binLog(const bin x);