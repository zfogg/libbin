#pragma once

#include "../src/bin.h"

#include "bin_tests_debug.h"


// bitwise
void binMSBi_test           ();

void binLSBi_test           ();

void binMSB_test            ();

void binNOT_test            ();

void binShiftL_test         ();

void binShiftL1_test        ();

void binShiftOutZerosL_test ();

void binShiftR_test         ();

void binShiftR1_test        ();

void binShiftOutZerosR_test ();

void binAND_test            ();

void binOR_test             ();

void binXOR_test            ();

void binRotateL_test       ();

void binRotateR_test       ();


// math
void binAdd_test            ();

void binIncrement_test      ();

void binSubtract_test       ();

void binDecrement_test      ();

void binMultiply_test       ();

void binDivide_test         ();

void binModulus_test        ();

void binPow_test            ();

void binSqrt_test           ();

void binLog2Test            ();

void binLog10Test           ();

void binLogTest             ();


// boolean
void binEQZero_test         ();

void binEQOne_test          ();

void binEQMax_test          ();

void binEQ_test             ();

void binGT_test             ();

void binLT_test             ();

void binGTEQ_test           ();

void binLTEQ_test           ();

// Edge case tests
void binRandr_edge_cases_test();
void binNew_binToInt_edge_cases_test();

