#include "bin.h"
#include <assert.h>


// Add two binary numbers.
bin binAdd(const bin x, const bin y) {
    bin r = binZERO;
    bin_int_t carry = 0;
    
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        bin_int_t sum = x.bits[i] + y.bits[i] + carry;
        r.bits[i] = sum & 1;  // Extract least significant bit
        carry = sum >> 1;     // Extract carry bit
    }
    
    return r;
}


// Increment a binary number. Do not increment the maximum value.
bin binIncrement(const bin x) {
    return binAdd(x, binONE);
}


// Subtract two binary numbers.
bin binSubtract(const bin x, const bin y) {
    return binAdd(x, binIncrement(binNOT(y)));
}


// Decrement a binary number. Do not decrement zero.
bin binDecrement(const bin x) {
    assert(!binEQ(x, binZERO));
    return binSubtract(x, binONE);
}


// Multiply two binary numbers.
bin binMultiply(const bin x, const bin y) {
    if (binEQZero(y))
        return binZERO;
    else if (binEQOne(y))
        return x;

    // Use binary multiplication algorithm (similar to long multiplication)
    // For each bit in the multiplier, if it's 1, add the shifted multiplicand
    bin result = binZERO;
    bin multiplicand = x;

    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        if (y.bits[i])
            result = binAdd(result, multiplicand);
        multiplicand = binShiftL1(multiplicand);
    }

    return result;
}


// Divide two binary numbers. Do not divide by zero.
bin binDivide(const bin numerator, const bin denominator) {
    assert(!binEQZero(denominator));

    bin quotient  = binZERO,
        remainder = binZERO;

    for (int i = BIN_BITS-1; i >= 0; --i) {
        remainder = binShiftL1(remainder);
        remainder.bits[0] = numerator.bits[i];

        if (binGTEQ(remainder, denominator)) {
            remainder = binSubtract(remainder, denominator);
            quotient.bits[i] = 1;
        }
    }

    return quotient;
}


// Calculate the modulus of two binary numbers. Do not modulus by zero.
bin binModulus(const bin x, const bin y) {
    assert(!binEQZero(y));

    if (binLT(x, y))
        return x;
    
    // Use the same algorithm as division but return remainder instead
    bin remainder = binZERO;
    
    for (int i = BIN_BITS-1; i >= 0; --i) {
        remainder = binShiftL1(remainder);
        remainder.bits[0] = x.bits[i];
        
        if (binGTEQ(remainder, y))
            remainder = binSubtract(remainder, y);
    }
    
    return remainder;
}


// Calculate the power of two binary numbers.
bin binPow(const bin x, const bin y) {
    if (binEQZero(y))
        return binONE;
    else if (binEQOne(y))
        return x;
    
    // Use binary exponentiation (square and multiply)
    bin result = binONE;
    bin base = x;
    bin exponent = y;

    while (!binEQZero(exponent)) {
        if (exponent.bits[0]) // If least significant bit is 1
            result = binMultiply(result, base);
        base = binMultiply(base, base);
        exponent = binShiftR1(exponent);
    }
    
    return result;
}
