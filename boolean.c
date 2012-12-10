bool binEQZero(bin x) {
  int i;
  for (i = 0; i < BIN_BITS; i++)
    if (x.bits[i])
      return FALSE;
  return TRUE;
}

bool binEQ(bin x, bin y) {
  return binEQZero(binSubtract(x, y));
}


bool binGT(bin x, bin y) {
  if (binEQ(x, y))
    return FALSE;

  bin msb;
  int i;
  for (i = 0; i < BIN_BITS; i++)
    if (x.bits[i] || y.bits[i])
      msb = binNew(i+1);

  x = binShiftL(x, binSubtract(binNew(BIN_BITS), msb));
  y = binShiftL(y, binSubtract(binNew(BIN_BITS), msb));

  if (x.bits[BIN_BITS-1] && !y.bits[BIN_BITS-1]) {
    return TRUE;
  } else if (!x.bits[BIN_BITS-1] && y.bits[BIN_BITS-1]) {
    return FALSE;
  } else {
    x.bits[BIN_BITS-1] = 0;
    y.bits[BIN_BITS-1] = 0;
    return binGT(x, y);
  }
}

bool binLT(bin x, bin y) {
  if (!binEQZero(y))
    y = binSubtract(y, binNew(1));
  return !binGT(x, y);
}


bool binGTEQ(bin x, bin y) {
  return !binLT(x, y);
}

bool binLTEQ(bin x, bin y) {
  return !binGT(x, y);
}
