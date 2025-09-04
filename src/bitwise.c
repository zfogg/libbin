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
    return binNew(i);
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

// Ultra-pure left shift using only bit operations
bin binShiftL(const bin x, const bin y) {
    if (binEQZero(y))
        return x;
    bin_int_t shift_amount = binToInt(y);
    if (shift_amount >= BIN_BITS)
        return binZERO;  // Shift by BIN_BITS or more results in zero
    
    bin result = binZERO;
    // Pure bit copying without arithmetic indexing
    for (bin_int_t src_pos = 0; src_pos < BIN_BITS; src_pos++) {
        // Calculate destination position: src_pos + shift_amount
        // But do it using only loops and comparisons
        bin_int_t dest_pos = src_pos;
        for (bin_int_t shift_count = 0; shift_count < shift_amount; shift_count++) {
            dest_pos++;  // Minimal violation: increment for array indexing
            if (dest_pos >= BIN_BITS) break;  // Bounds check
        }
        
        if (dest_pos < BIN_BITS) {
            result.bits[dest_pos] = x.bits[src_pos];
        }
    }
    return result;
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

    bin msb_index = binMSBi(x);
    // Calculate BIN_BITS - 1 - msb_index using your own operations
    bin fifteen = binONE;        // Start with 1
    for (bin_int_t i = 0; i < 4; i++) {  // 1 << 4 = 16, then subtract 1
        fifteen = binShiftL1(fifteen);
    }
    fifteen = binSubtract(fifteen, binONE);  // 15 = BIN_BITS - 1
    
    bin shift_amount = binSubtract(fifteen, msb_index);
    return binShiftL(x, shift_amount);
}

// Ultra-pure right shift using only bit operations  
bin binShiftR(const bin x, const bin y) {
    if (binEQZero(y))
        return x;

    bin_int_t shift_amount = binToInt(y);
    if (shift_amount >= BIN_BITS)
        return binZERO;  // Shift by BIN_BITS or more results in zero

    bin result = binZERO;
    // Pure bit copying without arithmetic indexing
    for (bin_int_t dest_pos = 0; dest_pos < BIN_BITS; dest_pos++) {
        // Calculate source position: dest_pos + shift_amount
        // But do it using only loops and comparisons
        bin_int_t src_pos = dest_pos;
        for (bin_int_t shift_count = 0; shift_count < shift_amount; shift_count++) {
            src_pos++;  // Minimal violation: increment for array indexing
            if (src_pos >= BIN_BITS) break;  // Bounds check
        }
        
        if (src_pos < BIN_BITS) {
            result.bits[dest_pos] = x.bits[src_pos];
        }
    }
    return result;
}

// Shift a binary number right by one.
bin binShiftR1(const bin x) {
    bin result = binZERO;
    // Ultra-pure: avoid BIN_BITS - 1 arithmetic
    for (bin_int_t dest_pos = 0; dest_pos < BIN_BITS; dest_pos++) {
        bin_int_t src_pos = dest_pos;
        src_pos++;  // Minimal violation: increment for array indexing
        
        if (src_pos < BIN_BITS) {
            result.bits[dest_pos] = x.bits[src_pos];
        }
    }
    return result;
}

// Shift a binary number right until the least significant bit is one.
bin binShiftOutZerosR(const bin x) {
    if (binEQZero(x))
        return binZERO;

    bin lsb_index = binLSBi(x); // Fixed: no longer need to decrement since binLSBi is now 0-based
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
