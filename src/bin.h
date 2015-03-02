#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "16.h"

#include "boolean.h"
#include "math.h"
#include "bitwise.h"


#define CC_RESET "\x1B[0m"
#define CC_RED   "\x1B[31m"
#define CC_GREEN "\x1B[32m"


bin binNew(bin_int_t n);


bin_int_t binToInt(bin x);


void binPrint(bin x);

void binIntPrint(bin_int_t x);

void binIntPrint2(bin_int_t bi1, bin_int_t bi2);


bin_int_t randr(bin_int_t min, bin_int_t max);

