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
bin binLog(const bin _x) {
  assert(!binEQZero(_x)); // log(0) is undefined

  if (binEQOne(_x))
    return binZERO; // log(1) = 0

  // INFO: from https://gist.github.com/LingDong-/7e4c4cae5cbbc44400a05fba65f06f23
  // Convert to integer for easier calculation for this one, because I stole the code.
  float x = binToInt(_x);

  // ASSUMING:
  // - non-denormalized numbers i.e. x > 2^−126
  // - integer is 32 bit. float is IEEE 32 bit.

  // INSPIRED BY:
  // - https://stackoverflow.com/a/44232045
  // - http://mathonweb.com/help_ebook/html/algorithms.htm#ln
  // - https://en.wikipedia.org/wiki/Fast_inverse_square_root

  // FORMULA:
  // x = m * 2^p =>
  //   ln(x) = ln(m) + ln(2)p,

  // first normalize the value to between 1.0 and 2.0
  // assuming normalized IEEE float
  //    sign  exp       frac
  // 0b 0    [00000000] 00000000000000000000000
  // value = (-1)^s * M * 2 ^ (exp-127)
  //
  // exp = 127 for x = 1,
  // so 2^(exp-127) is the multiplier

  // evil floating point bit level hacking
  unsigned int bx = *(unsigned int *)(&x);

  // extract exp, since x>0, sign bit must be 0
  unsigned int ex = bx >> 23;
  signed int t = (signed int)ex - (signed int)127;

  // reinterpret back to float
  //   127 << 23 = 1065353216
  //   0b11111111111111111111111 = 8388607
  bx = 1065353216 | (bx & 8388607);
  x = *(float *)(&bx);

  // use remez algorithm to find approximation between [1,2]
  // - see this answer https://stackoverflow.com/a/44232045
  // - or this usage of C++/boost's remez implementation
  //   https://computingandrecording.wordpress.com/2017/04/24/
  // e.g.
  // boost::math::tools::remez_minimax<double> approx(
  //    [](const double& x) { return log(x); },
  // 4, 0, 1, 2, false, 0, 0, 64);
  //
  // 4th order is:
  // { -1.74178, 2.82117, -1.46994, 0.447178, -0.0565717 }
  //
  // 3rd order is:
  // { -1.49278, 2.11263, -0.729104, 0.10969 }

  return binNew(

      /* less accurate */
    //   -1.49278 + (2.11263 + (-0.729104 + 0.10969 * x) * x) * x

      /* OR more accurate */
      -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x

      /* compensate for the ln(2)s. ln(2)=0.6931471806 */
      + 0.6931471806 * t);
}
