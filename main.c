#include <stdlib.h>

#include "main.h"

#include "architectures/16.c"
#include "bin/bin.c"
#include "math/math.c"
#include "bitwise/bitwise.c"
#include "boolean/boolean.c"


int main(int argc, char* argv[]) {
    for (int i = 0; i < 10; ++i)
        printf("5 < %d = %d\n", i, binLT(binNew(5), binNew(i)));
    return 0;
}
