#include "bin.h"
#include <assert.h>


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

bin binIncrement(bin x) {
    // FIXME: this assertion should pass, but it doesn't. Check binMSB.
    // assert(!binEQMax(x));
    return binAdd(x, binONE);
}

bin binSubtract(bin x, bin y) {
    return binAdd(x, binIncrement(binNOT(y)));
}

bin binDecrement(bin x) {
    assert(!binEQ(x, binZERO));
    return binSubtract(x, binONE);
}


bin binMultiply(bin x, bin y) {
    if (binEQZero(y))
        return binZERO;
    else if (binEQOne(y))
        return x;
    return binAdd(x, binMultiply(x, binDecrement(y)));
}


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


bin binModulus(bin x, bin y) {
    assert(!binEQZero(y));
    if (binLT(x, y))
        return x;
    return binSubtract(x, binMultiply(y, binDivide(x, y)));
}


bin binPow(bin x, bin y) {
    if (binEQZero(y))
        return binONE;
    return binMultiply(x, binPow(x, binDecrement(y)));
}

