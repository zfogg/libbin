#include <stdio.h>

#include "bin_tests.h"
#include "../src/libbin.h"


int main(int argc, char* argv[]) {
    (void)(argc); (void)(argv);

    for (int i = 0; i < 4; ++i)
        printf("2 < %d = %d\n", i, binGT(binNew(2), binNew(i)));

    return 0;
}
