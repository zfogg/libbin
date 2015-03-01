#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bin_tests.h"
#include "bin_tests_debug.h"


int bin_testResults = 1;

int main(int argc, char* argv[]) {
    (void)(argc); (void)(argv);
    srand(time(NULL));

    puts("");
    binMSBi_test            ();
    binMSB_test             ();
    binNOT_test             ();
    binShiftL_test          ();
    binShiftL1_test         ();
    binShiftOutZerosL_test  ();
    binShiftR_test          ();
    binShiftR1_test         ();
    binShiftOutZerosR_test  ();
    binAND_test             ();
    binOR_test              ();
    binXOR_test             ();

    puts("");
    binAdd_test             ();
    binIncrement_test       ();
    binSubtract_test        ();
    binDecrement_test       ();
    binMultiply_test        ();
    binDivide_test          ();
    binModulus_test         ();
    binPow_test             ();

    puts("");
    binEQZero_test          ();
    binEQOne_test           ();
    binEQ_test              ();
    binGT_test              ();
    binLT_test              ();
    binGTEQ_test            ();
    binLTEQ_test            ();

    puts("");
    processTestResults("Pass ALL the tests", bin_testResults);

    return 0;
}

