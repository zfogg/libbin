#include "bin.h"


// Find the index of the most significant bit.
bin binMSBi(const bin x) {
    bin_int_t i = BIN_BITS-1;
    while (!x.bits[i] && i > 0) {
        i--;
    }
    return binNew(i);
}

// Find the index of the least significant bit.
bin binLSBi(const bin x) {
    bin_int_t i = 0;
    while (!x.bits[i] && i < BIN_BITS-1) {
        i++;
    }
    return binIncrement(binNew(i));
}

// Find the most significant bit.
bin binMSB(const bin x) {
    if (binEQZero(x))
        return binZERO;
    return binShiftL(binONE, binMSBi(x));
}

// Calculate the bitwise NOT of a binary number.
bin binNOT(const bin x) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        r.bits[i] = !x.bits[i];
    }
    return r;
}

// Shift a binary number left by another binary number.
bin binShiftL(const bin x, const bin y) {
    if (binEQZero(y))
        return x;
    bin_int_t shift_amount = binToInt(y);
    if (shift_amount >= BIN_BITS)
        return binZERO;  // Shift by BIN_BITS or more results in zero
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS - shift_amount; i++) {
        r.bits[i + shift_amount] = x.bits[i];
    }
    return r;
}

// Shift a binary number left by one.
bin binShiftL1(const bin x) {
    bin r = binZERO;
    for (bin_int_t i = 1; i < BIN_BITS; i++) {
        r.bits[i] = x.bits[i-1];
    }
    return r;
}

// Shift a binary number left until the most significant bit is one.
bin binShiftOutZerosL(const bin x) {
    if (binEQZero(x))
        return binZERO;
    
    bin_int_t msb_index = binToInt(binMSBi(x));
    return binShiftL(x, binNew(BIN_BITS - 1 - msb_index));
}

// Shift a binary number right by another binary number.
bin binShiftR(const bin x, const bin y) {
    if (binEQZero(y))
        return x;
    
    bin_int_t shift_amount = binToInt(y);
    if (shift_amount >= BIN_BITS)
        return binZERO;  // Shift by BIN_BITS or more results in zero
    
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS - shift_amount; i++) {
        r.bits[i] = x.bits[i + shift_amount];
    }
    return r;
}

// Shift a binary number right by one.
bin binShiftR1(const bin x) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS - 1; i++) {
        r.bits[i] = x.bits[i + 1];
    }
    return r;
}

// Shift a binary number right until the least significant bit is one.
bin binShiftOutZerosR(const bin x) {
    if (binEQZero(x))
        return binZERO;
    
    bin lsb_index = binDecrement(binLSBi(x));
    return binShiftR(x, lsb_index);
}

// Calculate the bitwise AND of two binary numbers.
bin binAND(const bin x, const bin y) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        r.bits[i] = x.bits[i] && y.bits[i];
    }
    return r;
}

// Calculate the bitwise OR of two binary numbers.
bin binOR(const bin x, const bin y) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        r.bits[i] = x.bits[i] || y.bits[i];
    }
    return r;
}

// Calculate the bitwise XOR of two binary numbers.
bin binXOR(const bin x, const bin y) {
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        r.bits[i] = x.bits[i] != y.bits[i];
    }
    return r;
}

// Perform a bitwise left rotation of the bits.
bin binRotateL(const bin x, const bin rotate_by) {
    if (binEQZero(rotate_by))
        return x;
    
    bin_int_t rotate_amount = binToInt(rotate_by) % BIN_BITS;
    if (rotate_amount == 0)
        return x;
    
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        bin_int_t new_pos = (i + rotate_amount) % BIN_BITS;
        r.bits[new_pos] = x.bits[i];
    }
    return r;
}

// Perform a bitwise right rotation of the bits.
bin binRotateR(const bin x, const bin rotate_by) {
    if (binEQZero(rotate_by))
        return x;
    
    bin_int_t rotate_amount = binToInt(rotate_by) % BIN_BITS;
    if (rotate_amount == 0)
        return x;
    
    bin r = binZERO;
    for (bin_int_t i = 0; i < BIN_BITS; i++) {
        bin_int_t new_pos = (i - rotate_amount + BIN_BITS) % BIN_BITS;
        r.bits[new_pos] = x.bits[i];
    }
    return r;
}
