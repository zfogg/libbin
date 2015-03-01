#pragma once

#include "16.h"


#define WHITE_CC "\e[0m"
#define GREEN_CC "\e[32m"
#define RED_CC   "\e[31m"


bin binNew(BIN_INT n);

BIN_INT binToInt(bin x);

void binPrint(bin x);

