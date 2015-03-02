#pragma once

#include <stdint.h>
#include <inttypes.h>


#define BIN_BITS       16

#define bin_int_t      uint16_t
#define BIN_INT_MAX    UINT16_MAX

#define PRINTF_BIN_INT PRIu16


typedef struct bin {
    bin_int_t bits[BIN_BITS];
} bin;


static const bin binZERO = {
    .bits = {
        0, 0, 0, 0,
        0, 0, 0, 0,

        0, 0, 0, 0,
        0, 0, 0, 0,
    }
};

static const bin binONE = {
    .bits = {
        1, 0, 0, 0,
        0, 0, 0, 0,

        0, 0, 0, 0,
        0, 0, 0, 0,
    }
};

static const bin binMAX = {
    .bits = {
        1, 1, 1, 1,
        1, 1, 1, 1,

        1, 1, 1, 1,
        1, 1, 1, 1,
    }
};

