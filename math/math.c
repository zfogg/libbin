#include <stdlib.h>


bin binAdd(bin x, bin y) {
  int i, carry;
  bin r = binZERO;
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
  return binAdd(x, binONE);
}

bin binSubtract(bin x, bin y) {
  return binAdd(x, binIncrement(binNOT(y)));
}

bin binDecrement(bin x) {
  return binSubtract(x, binONE);
}


bin binMultiply(bin x, bin y) {
  if (binEQZero(y))
    return binZERO;
  else if (binEQOne(y))
    return x;
  return binAdd(x, binMultiply(x, binDecrement(y)));
}

bin binDivide(bin x, bin y) {
  if (binLT(x, y))
    return binZERO;

  bin xMinusY = binSubtract(x, y),
      xMY_MSB = binMSBi(xMinusY);

  if (binEQZero(xMinusY))
    return binONE;
  else if (binGT(xMY_MSB, binMSBi(x)) || binGT(xMY_MSB, binMSBi(y)))
    return binZERO;
  else
    return binAdd(binONE, binDivide(xMinusY, y));
}

bin binModulus(bin x, bin y) {
  if (binLT(x, y))
    return x;
  return binSubtract(x, binMultiply(y, binDivide(x, y)));
}


bin binPow(bin x, bin y) {
  if (binEQZero(y))
    return binONE;
  return binMultiply(x, binPow(x, binDecrement(y)));
}
