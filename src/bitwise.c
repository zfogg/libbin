#include "bin.h"


// Find the index of the most significant bit.
bin binMSBi(bin x) {
    bin_int_t i = BIN_BITS-1;
    while (!x.bits[i] && i > 0)
        i--;
    return binIncrement(binNew(i));
}

// Find the index of the least significant bit.
bin binLSBi(bin x) {
    bin_int_t i = 0;
    while (!x.bits[i] && i < BIN_BITS-1)
        i++;
    return binIncrement(binNew(i));
}

// Find the most significant bit.
bin binMSB(bin x) {
    if (binEQZero(x))
        return binZERO;
    return binShiftL(binONE, binDecrement(binMSBi(x)));
}

// Calculate the bitwise NOT of a binary number.
bin binNOT(bin x) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        r.bits[i] = !x.bits[i];
    return r;
}

// Shift a binary number left by another binary number.
bin binShiftL(bin x, bin y) {
    return binMultiply(x, binPow(binNew(2), y));
}

// Shift a binary number left by one.
bin binShiftL1(bin x) {
    return binShiftL(x, binONE);
}

// Shift a binary number left until the most significant bit is one.
bin binShiftOutZerosL(bin x) {
    return binShiftL(x, binSubtract(binNew(BIN_BITS), binMSBi(x)));
}

// Shift a binary number right by another binary number.
bin binShiftR(bin x, bin y) {
    if (binEQZero(y))
        return x;

    bin r = binZERO;
    for (bin_int_t i = BIN_BITS-1; i > 0; i--)
        r.bits[i-1] = x.bits[i];

    return binShiftR(r, binDecrement(y));
}

// Shift a binary number right by one.
bin binShiftR1(bin x) {
    return binShiftR(x, binONE);
}

// Shift a binary number right until the least significant bit is one.
bin binShiftOutZerosR(bin x) {
    if (binEQZero(x))
        return binZERO;
    return binShiftR(x, binDecrement(binLSBi(x)));
}

// Calculate the bitwise AND of two binary numbers.
bin binAND(bin x, bin y) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        if (x.bits[i] && y.bits[i])
            r.bits[i] = 1;
    return r;
}

// Calculate the bitwise OR of two binary numbers.
bin binOR(bin x, bin y) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        if (x.bits[i] || y.bits[i])
            r.bits[i] = 1;
    return r;
}

// Calculate the bitwise XOR of two binary numbers.
bin binXOR(bin x, bin y) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++)
        if ((x.bits[i] || y.bits[i])
                && !(x.bits[i] && y.bits[i]))
            r.bits[i] = 1;
    return r;
}
