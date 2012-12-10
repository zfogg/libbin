#include <stdlib.h>


bin binNOT(bin x) {
  bin r = binNew(0);
  int i;
  for (i = 0; i < BIN_BITS; i++) {
    r.bits[i] = !x.bits[i];
  }
  return r;
}


bin binShiftL(bin x, bin y) {
  return binMultiply(x, binPow(binNew(2), y));
}

bin binShiftR(bin x, bin y) {
  if (binEQZero(y))
    return x;

  bin r = binNew(0);
  int i;
  for (i = BIN_BITS-1; i > 0; i--)
    r.bits[i-1] = x.bits[i];

  return binShiftR(r, binSubtract(y, binNew(1)));
}


bin binAND(bin x, bin y) {
  int i;
  bin r = binNew(0);
  for (i = 0; i < BIN_BITS; i++)
    if (x.bits[i] && y.bits[i])
      r.bits[i] = 1;
  return r;
}

bin binOR(bin x, bin y) {
  int i;
  bin r = binNew(0);
  for (i = 0; i < BIN_BITS; i++)
    if (x.bits[i] || y.bits[i])
      r.bits[i] = 1;
  return r;
}

bin binXOR(bin x, bin y) {
  int i;
  bin r = binNew(0);
  for (i = 0; i < BIN_BITS; i++)
    if ((x.bits[i] || y.bits[i])
    && !(x.bits[i] && y.bits[i]))
      r.bits[i] = 1;
  return r;
}
