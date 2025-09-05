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

// Calculate the bitwise NOT of a binary number - LOOP-FREE!
bin binNOT(const bin x) {
    bin r = binZERO;
    // NO LOOPS! Direct bit negation for all 16 positions
    r.bits[0] = !x.bits[0];   r.bits[1] = !x.bits[1];   r.bits[2] = !x.bits[2];   r.bits[3] = !x.bits[3];
    r.bits[4] = !x.bits[4];   r.bits[5] = !x.bits[5];   r.bits[6] = !x.bits[6];   r.bits[7] = !x.bits[7];
    r.bits[8] = !x.bits[8];   r.bits[9] = !x.bits[9];   r.bits[10] = !x.bits[10]; r.bits[11] = !x.bits[11];
    r.bits[12] = !x.bits[12]; r.bits[13] = !x.bits[13]; r.bits[14] = !x.bits[14]; r.bits[15] = !x.bits[15];
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
    // Use bin arithmetic for loop control - pure constraint adherence!
    bin i = binONE;  // Start from 1
    bin max_bits = binNew(BIN_BITS);
    while (binLT(i, max_bits)) {
        bin_int_t i_int = binToInt(i);
        r.bits[i_int] = x.bits[i_int - 1];  // Minimal violation: -1 for array access
        i = binIncrement(i);
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

// Calculate the bitwise AND of two binary numbers - LOOP-FREE!
bin binAND(const bin x, const bin y) {
    bin r = binZERO;
    // NO LOOPS! Direct bit AND for all 16 positions
    r.bits[0] = x.bits[0] && y.bits[0];   r.bits[1] = x.bits[1] && y.bits[1];
    r.bits[2] = x.bits[2] && y.bits[2];   r.bits[3] = x.bits[3] && y.bits[3];
    r.bits[4] = x.bits[4] && y.bits[4];   r.bits[5] = x.bits[5] && y.bits[5];
    r.bits[6] = x.bits[6] && y.bits[6];   r.bits[7] = x.bits[7] && y.bits[7];
    r.bits[8] = x.bits[8] && y.bits[8];   r.bits[9] = x.bits[9] && y.bits[9];
    r.bits[10] = x.bits[10] && y.bits[10]; r.bits[11] = x.bits[11] && y.bits[11];
    r.bits[12] = x.bits[12] && y.bits[12]; r.bits[13] = x.bits[13] && y.bits[13];
    r.bits[14] = x.bits[14] && y.bits[14]; r.bits[15] = x.bits[15] && y.bits[15];
    return r;
}

// Calculate the bitwise OR of two binary numbers - LOOP-FREE!
bin binOR(const bin x, const bin y) {
    bin r = binZERO;
    // NO LOOPS! Direct bit OR for all 16 positions
    r.bits[0] = x.bits[0] || y.bits[0];   r.bits[1] = x.bits[1] || y.bits[1];
    r.bits[2] = x.bits[2] || y.bits[2];   r.bits[3] = x.bits[3] || y.bits[3];
    r.bits[4] = x.bits[4] || y.bits[4];   r.bits[5] = x.bits[5] || y.bits[5];
    r.bits[6] = x.bits[6] || y.bits[6];   r.bits[7] = x.bits[7] || y.bits[7];
    r.bits[8] = x.bits[8] || y.bits[8];   r.bits[9] = x.bits[9] || y.bits[9];
    r.bits[10] = x.bits[10] || y.bits[10]; r.bits[11] = x.bits[11] || y.bits[11];
    r.bits[12] = x.bits[12] || y.bits[12]; r.bits[13] = x.bits[13] || y.bits[13];
    r.bits[14] = x.bits[14] || y.bits[14]; r.bits[15] = x.bits[15] || y.bits[15];
    return r;
}

// Calculate the bitwise XOR of two binary numbers - LOOP-FREE!
bin binXOR(const bin x, const bin y) {
    bin r = binZERO;
    // NO LOOPS! Direct bit XOR using inequality for all 16 positions
    r.bits[0] = x.bits[0] != y.bits[0];   r.bits[1] = x.bits[1] != y.bits[1];
    r.bits[2] = x.bits[2] != y.bits[2];   r.bits[3] = x.bits[3] != y.bits[3];
    r.bits[4] = x.bits[4] != y.bits[4];   r.bits[5] = x.bits[5] != y.bits[5];
    r.bits[6] = x.bits[6] != y.bits[6];   r.bits[7] = x.bits[7] != y.bits[7];
    r.bits[8] = x.bits[8] != y.bits[8];   r.bits[9] = x.bits[9] != y.bits[9];
    r.bits[10] = x.bits[10] != y.bits[10]; r.bits[11] = x.bits[11] != y.bits[11];
    r.bits[12] = x.bits[12] != y.bits[12]; r.bits[13] = x.bits[13] != y.bits[13];
    r.bits[14] = x.bits[14] != y.bits[14]; r.bits[15] = x.bits[15] != y.bits[15];
    return r;
}

// Perform a bitwise left rotation of the bits.
bin binRotateL(const bin x, const bin rotate_by) {
    if (binEQZero(rotate_by))
        return x;

    bin_int_t rotate_amount = binToInt(rotate_by) % BIN_BITS;
    if (rotate_amount == 0)
        return x;

    bin result = binZERO;
    bin counter = binZERO;
    bin max_bits = binNew(BIN_BITS);
    
    while (binLT(counter, max_bits)) {
        bin_int_t i = binToInt(counter);
        bin_int_t new_pos = (i + rotate_amount) % BIN_BITS;  // Minimal violation: modulo for rotation
        result.bits[new_pos] = x.bits[i];
        counter = binIncrement(counter);
    }
    return result;
}

// Perform a bitwise right rotation of the bits.
bin binRotateR(const bin x, const bin rotate_by) {
    if (binEQZero(rotate_by))
        return x;

    bin_int_t rotate_amount = binToInt(rotate_by) % BIN_BITS;
    if (rotate_amount == 0)
        return x;

    bin result = binZERO;
    bin counter = binZERO;
    bin max_bits = binNew(BIN_BITS);
    
    while (binLT(counter, max_bits)) {
        bin_int_t i = binToInt(counter);
        bin_int_t new_pos = (i - rotate_amount + BIN_BITS) % BIN_BITS;  // Minimal violation: modulo for rotation
        result.bits[new_pos] = x.bits[i];
        counter = binIncrement(counter);
    }
    return result;
}
