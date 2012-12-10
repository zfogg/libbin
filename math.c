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

bin binPlusOne(bin x) {
  return binAdd(x, binNew(1));
}

bin binSubtract(bin x, bin y) {
  return binAdd(x, binAdd(binNOT(y), binNew(1)));
}

bin binMinusOne(bin x) {
  return binSubtract(x, binNew(1));
}


bin binMultiply(bin x, bin y) {
  if (binEQ(y, binNew(1)))
    return x;
  return binAdd(x, binMultiply(x, binSubtract(y, binNew(1))));
}

bin binDivide(bin x, bin y) {
  //FIXME: implement this.
  return binNew(0);
}


bin binPow(bin x, bin y) {
  if (binEQZero(y))
    return binNew(1);
  return binMultiply(x, binPow(x, binSubtract(y, binNew(1))));
}
