#include "bin.h"
#include "boolean.h"
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

    // Check for overflow
    // if (carry != 0) {
    //     puts("overflow:");
    //     binPrint(x);
    //     binPrint(y);
    //     puts("");
    //     // abort();
    // }

    return r;
}


// Increment a binary number. Do not increment the maximum value.
bin binIncrement(const bin x) {
    assert(!binEQMax(x));
    return binAdd(x, binONE);
}


// Subtract two binary numbers. Do not subtract a larger number from a smaller number.
bin binSubtract(const bin x, const bin y) {
    assert(binGTEQ(x, y));
    if (binEQZero(y))
        return x;
    // For two's complement subtraction: x - y = x + (~y + 1)
    return binAdd(x, binIncrement(binNOT(y)));
}


// Decrement a binary number. Do not decrement zero.
bin binDecrement(const bin x) {
    assert(!binEQZero(x));
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
        if (y.bits[i]) {
            // Check if adding multiplicand would cause overflow
            // If result + multiplicand > MAX, then overflow would occur
            // bin_int_t result_int = binToInt(result);
            // bin_int_t multiplicand_int = binToInt(multiplicand);
            // if (result_int > BIN_INT_MAX - multiplicand_int) {
            //     puts("overflow in multiplication:");
            //     binPrint(x);
            //     binPrint(y);
            //     puts("");
            //     // abort();
            // }
            result = binAdd(result, multiplicand);
        }
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


// Calculate x modulus y. Do not modulus by zero.
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


// Calculate x to the power of y.
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

// Calculate the square root of a binary number
bin binSqrt(const bin x) {
    if (binEQZero(x))
        return binZERO;
    else if (binEQOne(x))
        return binONE;
    
    // Use Newton-Raphson method: x_{n+1} = (x_n + a/x_n) / 2
    // Start with x/2 as initial guess
    bin guess = binShiftR1(x);
    bin prev_guess;
    bin_int_t iterations = 0;
    const bin_int_t max_iterations = 30; // Prevent infinite loops
    
    do {
        prev_guess = guess;
        
        // Calculate a/guess
        bin quotient = binDivide(x, guess);
        
        // Calculate (guess + a/guess) / 2
        bin sum = binAdd(guess, quotient);
        guess = binShiftR1(sum);
        
        iterations++;
        
        // Stop if we've converged or hit max iterations
    } while (!binEQ(guess, prev_guess) && iterations < max_iterations);
    
    return guess;
}

// Calculate the base2 logarithm of a binary number
bin binLog2(const bin x) {
    assert(!binEQZero(x)); // log2(0) is undefined
    
    if (binEQOne(x))
        return binZERO; // log2(1) = 0
    
    // Find the position of the most significant bit (MSB)
    // This gives us the integer part of log2(x)
    return binMSBi(x);
}


// Calculate the base10 logarithm of a binary number
bin binLog10(const bin x) {
    assert(!binEQZero(x)); // log10(0) is undefined
    
    if (binEQOne(x))
        return binZERO; // log10(1) = 0
    
    // Use a lookup table approach for common values
    // For values 1-1000, we can pre-calculate log10
    if (binLTEQ(x, binNew(1000))) {
        // Simple lookup table for powers of 10 and common values
        if (binEQ(x, binNew(10))) return binNew(1);
        if (binEQ(x, binNew(100))) return binNew(2);
        if (binEQ(x, binNew(1000))) return binNew(3);
        
        // For other values, find the largest power of 10 that fits
        if (binGTEQ(x, binNew(100))) return binNew(2);
        if (binGTEQ(x, binNew(10))) return binNew(1);
        return binZERO; // x < 10
    }
    
    // For larger values, use a different approach
    // Count the number of digits in base 10 representation
    bin temp = x;
    bin_int_t digit_count = 0;
    while (binGT(temp, binZERO)) {
        temp = binDivide(temp, binNew(10));
        digit_count++;
    }
    
    // log10(x) is approximately (number of digits - 1)
    return binNew(digit_count - 1);
}


// Calculate the natural logarithm of a binary number
// This is a simplified integer-based approach that maintains the constraint-based design
bin binLog(const bin x) {
    assert(!binEQZero(x)); // log(0) is undefined
    
    if (binEQOne(x))
        return binZERO; // log(1) = 0
    
    // For integer natural logarithm, we use a simple approximation:
    // ln(x) ≈ ln(2) * log2(x) where ln(2) ≈ 0.693
    // Since we're working with integers, we'll use a scaled approach
    
    // Get the log2 value (MSB position)
    bin log2_val = binLog2(x);
    
    // Simple lookup table approach for small values (more accurate)
    if (binLTEQ(x, binNew(16))) {
        // Pre-calculated ln(x) values scaled by 1 (rounded to nearest integer)
        // ln(1)=0, ln(2)=1, ln(3)=1, ln(4)=1, ln(5)=2, ln(6)=2, ln(7)=2, ln(8)=2
        // ln(9)=2, ln(10)=2, ln(11)=2, ln(12)=2, ln(13)=3, ln(14)=3, ln(15)=3, ln(16)=3
        bin_int_t x_int = binToInt(x);
        if (x_int <= 1) return binZERO;
        else if (x_int <= 4) return binONE;
        else if (x_int <= 12) return binNew(2);
        else return binNew(3);
    }
    
    // For larger values, use the approximation ln(x) ≈ 0.7 * log2(x)
    // We'll use integer arithmetic: ln(x) ≈ (7 * log2(x)) / 10
    // But since we need integer results, we'll round: ln(x) ≈ (7 * log2(x) + 5) / 10
    
    bin seven = binNew(7);
    bin ten = binNew(10);
    bin five = binNew(5);
    
    // Calculate (7 * log2_val + 5) / 10
    bin scaled = binAdd(binMultiply(seven, log2_val), five);
    return binDivide(scaled, ten);
}
