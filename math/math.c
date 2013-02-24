#include <stdlib.h>


bin binAdd(bin x, bin y) {
  int i, carry;
  bin r = binNew(0);
  for (i = 0, carry = 0; i < BIN_BITS; i++) {
    if (!carry && ((x.bits[i] && !y.bits[i])
                || (!x.bits[i] && y.bits[i]))) {
      r.bits[i] = 1;
    } else if (!carry && x.bits[i] && y.bits[i]) {
      carry = 1;
    } else if (carry && !x.bits[i] && !y.bits[i]) {
      carry = 0;
      r.bits[i] = 1;
    } else if (carry && x.bits[i] && y.bits[i]) {
      r.bits[i] = 1;
    }
  }
  return r;
}

bin binIncrement(bin x) {
  return binAdd(x, binNew(1));
}

bin binSubtract(bin x, bin y) {
  return binAdd(x, binIncrement(binNOT(y)));
}

bin binDecrement(bin x) {
  return binSubtract(x, binNew(1));
}


bin binMultiply(bin x, bin y) {
  if (binEQZero(y))
    return binNew(0);
  else if (binEQOne(y))
    return x;
  return binAdd(x, binMultiply(x, binDecrement(y)));
}

bin binDivide(bin x, bin y) {
  if (binLT(x, y))
    return binNew(0);

  bin xMinusY = binSubtract(x, y),
      xMY_MSB = binMSBi(xMinusY);

  if (binEQZero(xMinusY))
    return binNew(1);
  else if (binGT(xMY_MSB, binMSBi(x)) || binGT(xMY_MSB, binMSBi(y)))
    return binNew(0);
  else
    return binAdd(binNew(1), binDivide(xMinusY, y));
}

bin binModulus(bin x, bin y) {
  if (binLT(x, y))
    return x;
  return binSubtract(x, binMultiply(y, binDivide(x, y)));
}


bin binPow(bin x, bin y) {
  if (binEQZero(y))
    return binNew(1);
  return binMultiply(x, binPow(x, binDecrement(y)));
}
