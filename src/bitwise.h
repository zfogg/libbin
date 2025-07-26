#pragma once

#include "bin.h"

/**
 * @brief Returns the value of the index of the most significant bit
 * @param x The binary value to analyze
 * @return The index of the most significant bit
 */
bin binMSBi(const bin x);

/**
 * @brief Returns the value of the index of the least significant bit
 * @param x The binary value to analyze
 * @return The index of the least significant bit
 */
bin binLSBi(const bin x);

/**
 * @brief Returns the value of the most significant bit
 * @param x The binary value to analyze
 * @return The value of the most significant bit
 */
bin binMSB(const bin x);

/**
 * @brief Negates a value
 * @param x The binary value to negate
 * @return The negated value
 */
bin binNOT(const bin x);

/**
 * @brief Performs left bit shift
 * @param x The binary value to shift
 * @param y The number of positions to shift left
 * @return The shifted value
 */
bin binShiftL(const bin x, const bin y);

/**
 * @brief Performs left bit shift by one
 * @param x The binary value to shift
 * @return The value shifted left by one position
 */
bin binShiftL1(const bin x);

/**
 * @brief Performs left bit shift until all the highest bit is set
 * @param x The binary value to shift
 * @return The value with zeros shifted out from the left
 */
bin binShiftOutZerosL(const bin x);

/**
 * @brief Performs right bit shift
 * @param x The binary value to shift
 * @param y The number of positions to shift right
 * @return The shifted value
 */
bin binShiftR(const bin x, const bin y);

/**
 * @brief Performs right bit shift by one
 * @param x The binary value to shift
 * @return The value shifted right by one position
 */
bin binShiftR1(const bin x);

/**
 * @brief Performs right bit shift until all the lowest bit is set
 * @param x The binary value to shift
 * @return The value with zeros shifted out from the right
 */
bin binShiftOutZerosR(const bin x);

/**
 * @brief Performs AND logic gate operation
 * @param x The first binary operand
 * @param y The second binary operand
 * @return The result of x AND y
 */
bin binAND(const bin x, const bin y);

/**
 * @brief Performs OR logic gate operation
 * @param x The first binary operand
 * @param y The second binary operand
 * @return The result of x OR y
 */
bin binOR(const bin x, const bin y);

/**
 * @brief Performs XOR logic gate operation
 * @param x The first binary operand
 * @param y The second binary operand
 * @return The result of x XOR y
 */
bin binXOR(const bin x, const bin y);


/**
 * @brief Performs a bitwise left rotation of the bits.
 * @param x The binary operand to rotate.
 * @param rotate_by Rotate bits to the left by this amount.
 * @return The rotated result.
 */
bin binRotateL(const bin x, const bin rotate_by);

/**
 * @brief Performs a bitwise right rotation of the bits.
 * @param x The binary operand to rotate.
 * @param rotate_by Rotate bits to the right by this amount.
 * @return The rotated result.
 */
bin binRotateR(const bin x, const bin rotate_by);
