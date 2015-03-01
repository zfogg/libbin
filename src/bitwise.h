#pragma once

#include "bin.h"


/*
 * returns the value of the index of the most significant bit
 * */
bin binMSBi(bin x);

/*
 * returns the value of the most significant bit
 * */
bin binMSB(bin x);


/*
 * negates a value
 * */
bin binNOT(bin x);


/*
 * left bit shift 
 * */
bin binShiftL(bin x, bin y);

/*
 * left bit shift by one
 * */
bin binShiftL1(bin x);

/*
 * left bit shift until all the highest bit is set
 * */
bin binShiftOutZerosL(bin x);

/*
 * right bit shift 
 * */
bin binShiftR(bin x, bin y);

/*
 * right bit shift  by one
 * */
bin binShiftR1(bin x);

/*
 * right bit shift until all the lowest bit is set
 * */
bin binShiftOutZerosR(bin x);


/*
 * AND logic gate
 * */
bin binAND(bin x, bin y);

/*
 * OR logic gate
 * */
bin binOR(bin x, bin y);

/*
 * XOR logic gate
 * */
bin binXOR(bin x, bin y);

