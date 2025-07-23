#pragma once

#include <stdbool.h>
#include "bin.h"


#define boolToString(b) ((b) ? "TRUE" : "FALSE")

#define binMin(a,b) (binLT((a),(b)) ? (a) : (b))
#define binMax(a,b) (binGT((a),(b)) ? (a) : (b))


bool binEQZero(const bin x);

bool binEQOne(const bin x);

bool binEQMax(bin x);

bool binEQ(bin x, bin y);


bool binGT(bin x, bin y);

bool binLT(bin x, bin y);


bool binGTEQ(bin x, bin y);

bool binLTEQ(bin x, bin y);

