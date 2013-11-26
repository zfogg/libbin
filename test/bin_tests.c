#include <stdio.h>

#include "../src/16.h"
#include "../src/bin.h"
#include "../src/bitwise.h"
#include "../src/boolean.h"
#include "../src/math.h"


int main(int argc, char* argv[]) {
    (void)(argc); (void)(argv);

    for (int i = 0; i < 4; ++i)
        printf("2 < %d = %d\n", i, binGT(binNew(2), binNew(i)));

    return 0;
}
