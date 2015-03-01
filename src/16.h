#pragma once


#define BIN_INT int
#define BIN_BITS (int)sizeof(BIN_INT)*4


#define RAND(min, max) (rand() % (max+1-min))+min


typedef struct bin {
    BIN_INT bits[BIN_BITS];
} bin;


static const bin binZERO = {
    .bits = {
        0, 0, 0, 0,
        0, 0, 0, 0,

        0, 0, 0, 0,
        0, 0, 0, 0
    }
};

static const bin binONE = {
    .bits = {
        1, 0, 0, 0,
        0, 0, 0, 0,

        0, 0, 0, 0,
        0, 0, 0, 0
    }
};

static const bin binMAX = {
    .bits = {
        1, 1, 1, 1,
        1, 1, 1, 1,

        1, 1, 1, 1,
        1, 1, 1, 1
    }
};

