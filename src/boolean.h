#pragma once

#include "bin.h"


typedef bin_int_t bool;


#define TRUE  0x01
#define FALSE 0x00

#define boolToString(b) ((b) ? "TRUE" : "FALSE")

#define binMin(a,b) (binLT((a),(b)) ? (a) : (b))
#define binMax(a,b) (binGT((a),(b)) ? (a) : (b))


bool binEQZero(bin x);

bool binEQOne(bin x);

bool binEQMax(bin x);

bool binEQ(bin x, bin y);


bool binGT(bin x, bin y);

bool binLT(bin x, bin y);


bool binGTEQ(bin x, bin y);

bool binLTEQ(bin x, bin y);

