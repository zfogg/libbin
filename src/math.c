#include "bin.h"
#include <assert.h>


// Add two binary numbers.
bin binAdd(bin x, bin y) {
    bin r = binZERO;
    for (bin_int_t i = 0, carry = 0; i < BIN_BITS; i++) {
        if (!carry && ((x.bits[i] && !y.bits[i])
                    || (!x.bits[i] && y.bits[i]))) {
            r.bits[i] = 1;
        } else if (!carry && x.bits[i] && y.bits[i]) {
            carry = 1;
        } else if (carry && !x.bits[i] && !y.bits[i]) {
            carry = 0;
            r.bits[i] = 1;
        } else if (carry && x.bits[i] && y.bits[i]) {
            r.bits[i] = 1;
        }
    }
    return r;
}


// Increment a binary number. Do not increment the maximum value.
bin binIncrement(bin x) {
    // FIXME: this assertion should pass, but it doesn't. Check binMSB.
    // assert(!binEQMax(x));
    return binAdd(x, binONE);
}


// Subtract two binary numbers.
bin binSubtract(bin x, bin y) {
    return binAdd(x, binIncrement(binNOT(y)));
}


// Decrement a binary number. Do not decrement zero.
bin binDecrement(bin x) {
    assert(!binEQ(x, binZERO));
    return binSubtract(x, binONE);
}


// Multiply two binary numbers.
bin binMultiply(bin x, bin y) {
    if (binEQZero(y))
        return binZERO;
    else if (binEQOne(y))
        return x;
    return binAdd(x, binMultiply(x, binDecrement(y)));
}


// Divide two binary numbers. Do not divide by zero.
bin binDivide(bin numerator, bin denominator) {
    assert(!binEQZero(denominator));

    bin quotient  = binZERO,
        remainder = binZERO;

    for (bin_int_t i = BIN_BITS-1; i != (bin_int_t)(-1); --i) {
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
bin binModulus(bin x, bin y) {
    assert(!binEQZero(y));
    if (binLT(x, y))
        return x;
    return binSubtract(x, binMultiply(y, binDivide(x, y)));
}


// Calculate the power of two binary numbers.
bin binPow(bin x, bin y) {
    if (binEQZero(y))
        return binONE;
    return binMultiply(x, binPow(x, binDecrement(y)));
}

