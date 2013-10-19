#include "../bin/bin.h"
#include "../math/math.h"
#include "../bitwise/bitwise.h"
#include "../boolean/boolean.h"
#include "../architectures/16.c"


bin binMSBi(bin x) {
  int i = BIN_BITS-1;
  while (!x.bits[i] && i > 0)
    i--;
  return binIncrement(binNew(i));
}

bin binMSB(bin x) {
  if (binEQZero(x))
    return binZERO;
  return binShiftL(binONE, binDecrement(binMSBi(x)));
}


bin binNOT(bin x) {
  bin r = binZERO;
  for (int i = 0; i < BIN_BITS; i++) {
    r.bits[i] = !x.bits[i];
  }
  return r;
}


bin binShiftL(bin x, bin y) {
  return binMultiply(x, binPow(binNew(2), y));
}

bin binShiftL1(bin x) {
  return binShiftL(x, binONE);
}

bin binShiftOutZerosL(bin x) {
  return binShiftL(x, binSubtract(binNew(BIN_BITS), binMSBi(x)));
}

bin binShiftR(bin x, bin y) {
  if (binEQZero(y))
    return x;

  bin r = binZERO;
  int i;
  for (i = BIN_BITS-1; i > 0; i--)
    r.bits[i-1] = x.bits[i];

  return binShiftR(r, binDecrement(y));
}

bin binShiftR1(bin x) {
  return binShiftR(x, binONE);
}

bin binShiftOutZerosR(bin x) {
  if (binEQZero(x))
    return binZERO;
  return binShiftR(x, binDecrement(binMSBi(x)));
}


bin binAND(bin x, bin y) {
  bin r = binZERO;
  for (int i = 0; i < BIN_BITS; i++)
    if (x.bits[i] && y.bits[i])
      r.bits[i] = 1;
  return r;
}

bin binOR(bin x, bin y) {
  bin r = binZERO;
  for (int i = 0; i < BIN_BITS; i++)
    if (x.bits[i] || y.bits[i])
      r.bits[i] = 1;
  return r;
}

bin binXOR(bin x, bin y) {
  bin r = binZERO;
  for (int i = 0; i < BIN_BITS; i++)
    if ((x.bits[i] || y.bits[i])
    && !(x.bits[i] && y.bits[i]))
      r.bits[i] = 1;
  return r;
}
