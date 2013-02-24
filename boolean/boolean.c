bool binEQZero(bin x) {
  int i;
  for (i = 0; i < BIN_BITS; i++)
    if (x.bits[i])
      return FALSE;
  return TRUE;
}
bool binEQOne(bin x) {
  return binEQZero(binDecrement(x));
}

bool binEQ(bin x, bin y) {
  return binEQZero(binSubtract(x, y));
}


bool binGT(bin x, bin y) {
  if (binEQ(x, y))
    return FALSE;
  else if (binEQZero(x) || binEQZero(y))
    return binEQZero(y);

  bin msbi = binMSBi(binOR(x, y));

  x = binShiftL(x, binSubtract(binNew(BIN_BITS), msbi));
  y = binShiftL(y, binSubtract(binNew(BIN_BITS), msbi));

  if (x.bits[BIN_BITS-1] && !y.bits[BIN_BITS-1])
    return TRUE;
  else if (!x.bits[BIN_BITS-1] && y.bits[BIN_BITS-1])
    return FALSE;
  else
    return binGT(binShiftL1(x), binShiftL1(y));
}

bool binLT(bin x, bin y) {
  if (binEQ(x, y))
    return FALSE;
  return !binGT(x, y);
}


bool binGTEQ(bin x, bin y) {
  return !binLT(x, y);
}

bool binLTEQ(bin x, bin y) {
  return !binGT(x, y);
}
