#include <stdlib.h>
#include <stdio.h>

#include "bin.h"
#include "math.h"
#include "bitwise.h"
#include "boolean.h"

#include "bin.c"
#include "math.c"
#include "bitwise.c"
#include "boolean.c"


int main(int argc, char* argv[]) {

  printf("\n%d\n", binLTEQ(binNew(2), binNew(1)));

  return 0;
}
