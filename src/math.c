#include <stdlib.h>
#include <stdio.h>
#include "bin.h"
#include "math.h"
#include "bitwise.h"
#include "boolean.h"


bin binAdd(bin x, bin y) {
    bin r = binZERO;
    for (int i = 0, carry = 0; i < BIN_BITS; i++) {
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
    return binAdd(x, binONE);
}

bin binSubtract(bin x, bin y) {
    return binAdd(x, binIncrement(binNOT(y)));
}

bin binDecrement(bin x) {
    return binSubtract(x, binONE);
}


bin binMultiply(bin x, bin y) {
    if (binEQZero(y))
        return binZERO;
    else if (binEQOne(y))
        return x;
    return binAdd(x, binMultiply(x, binDecrement(y)));
}

bin binDivide(bin x, bin y) {
    if (binEQZero(y)) {
        printf("Division by zero is undefined.\n");
        exit(1);
    }

    if (binEQZero(x))
        return binZERO;
    else if (binEQZero(binSubtract(x, y)))
        return binONE;

    bin q = binZERO,
        r = binZERO;

    for (int i = BIN_BITS-1; i >= 0; i--) {
        r = binShiftL1(r);
        r.bits[0] = x.bits[i];

        if (binGTEQ(r, y)) {
            r = binSubtract(r, y);
            q.bits[i] = 1;
        }
    }

    return q;
}

bin binModulus(bin x, bin y) {
    if (binLT(x, y))
        return x;
    return binSubtract(x, binMultiply(y, binDivide(x, y)));
}


bin binPow(bin x, bin y) {
    if (binEQZero(y))
        return binONE;
    return binMultiply(x, binPow(x, binDecrement(y)));
}

