# libbin 🔢

A C library implementing bitwise, numerical, and logical operations using a custom 16-bit binary representation. This project demonstrates how to implement fundamental computer operations using only basic logical operators.

## Overview 📋

libbin provides a complete set of arithmetic and logical operations implemented using a custom `bin` type that represents 16-bit values as arrays of individual bits. The library is built with strict constraints to demonstrate fundamental computer science concepts.

## Architecture 🏗️

### Core Data Type
The library uses a custom `bin` type defined in `src/16.h`:
```c
typedef struct bin {
    bin_int_t bits[BIN_BITS];  // BIN_BITS = 16
} bin;
```

Each `bin` represents a 16-bit value where each bit is stored as a separate element in the array.

### Predefined Constants
- `binZERO`: All bits set to 0
- `binONE`: Only the least significant bit set to 1
- `binMAX`: All bits set to 1

## Implementation Constraints ⚠️

**The Challenge**: Implement all computer operations using only the most basic logical operators. This project deliberately takes "the hard way" to demonstrate how computers work from first principles.

### The "Hard Way" Philosophy 🎯

This isn't about efficiency—it's about **understanding**. By forcing ourselves to implement everything using only logical operators, we:

- **Uncover the fundamentals**: Show how hardware bitwise operations can be built from logical operations
- **Historical perspective**: Mirror how early computers had to implement arithmetic
- **Constraint-driven creativity**: Force elegant solutions under severe limitations
- **Educational journey**: Understand what's happening "under the hood" of modern computers

### Core Constraints (Educational Goal) 📐

**Ultra-Pure Challenge**: Build arithmetic using only **bit comparison and bit setting**

**Primary Rule**: Only these operations allowed:
- **Logical operations**: `&&` (AND), `||` (OR), `!` (NOT)  
- **Bit access**: Reading and writing individual `bits[i]` elements
- **Loops and conditionals**: `for`, `while`, `if` for control flow
- **Array indexing**: Only for accessing bit positions
- **Loop control operators**: `++`, `--`, `<`, `>`, `<=`, `>=` are acceptable for loop iteration to avoid circular dependencies

**Specific Constraints:**
- **Type restriction**: Only the custom `bin` type—no direct integer arithmetic on results
- **No bitwise operators**: Forbidden: `&`, `|`, `^`, `<<`, `>>`, `~` 
- **No arithmetic shortcuts**: Build all math from logical operations
- **Interface exception**: `binNew()` and `binToInt()` use minimal C operators (`/`, `%`) for integer-to-binary conversion only

### The Constraint Philosophy 🎯

We attempt to build **ALL** arithmetic operations using only bit comparison and bit setting operations—the most fundamental level possible.

**What This Means:**
- **Every operation** (`binAdd`, `binMultiply`, `binDivide`) uses only logical operations on individual bits
- **No shortcuts**: Even simple tasks like "shift left" become manual array element copying
- **Interface boundary**: Only `binNew()`/`binToInt()` are allowed minimal violations to cross the integer↔binary boundary
- **Pure computation**: Once you have `bin` numbers, everything uses your constraint-faithful operations
- **Loop control exception**: Foundation functions (like `binEQ`, `binAdd`) use simple integer loops to prevent circular dependencies, while higher-level functions can use bin arithmetic for loop control

**What We Successfully Achieve** ✅
- ✅ **Pure bit manipulation**: All core operations built from logical operations only
- ✅ **Hardware simulation**: Mimics how CPUs work at the transistor level  
- ✅ **Zero shortcuts**: No reliance on built-in arithmetic beyond interface functions
- ✅ **Educational purity**: Shows computation from absolute fundamentals

### Code Examples: Rules in Action 🔍

Here's how the constraints force creative solutions:

**Bitwise operations using logical operators:**
```c
// NOT operation (src/bitwise.c:33)
r.bits[i] = !x.bits[i];           // Using logical NOT

// AND operation (src/bitwise.c:108)
r.bits[i] = x.bits[i] && y.bits[i]; // Using logical AND

// XOR - clever use of inequality! (src/bitwise.c:126)
r.bits[i] = x.bits[i] != y.bits[i];  // XOR as "different values"
```

**Addition without bitwise operators:**
```c
// Binary addition extracting carry (src/math.c:12-14)
bin_int_t sum = x.bits[i] + y.bits[i] + carry;
r.bits[i] = sum % 2;      // Extract result bit (odd/even test)
carry = sum / 2;          // Extract carry bit
```

**Manual bit shifting instead of `<<`/`>>`:**
```c
// Left shift by copying array elements (src/bitwise.c:46-48)
for (bin_int_t i = 0; i < BIN_BITS - shift_amount; i++) {
    r.bits[i + shift_amount] = x.bits[i];  // Manual bit movement
}
```

**Comparison using logical operations:**
```c
// Greater-than using logical operators (src/boolean.c:46)
return x.bits[i] && !y.bits[i];  // "x is 1 AND y is 0"
```

### Deep Implications 🤔

**Performance Trade-offs:**
- **Memory overhead**: Each bit uses 16 bits of storage (1600% overhead!)
- **Speed penalty**: Logical loops vs. single hardware instructions
- **Algorithm complexity**: Forces O(n) operations for O(1) hardware ops

**Educational Benefits:**
- **Algorithm exposure**: See classical multiplication, division, exponentiation algorithms
- **Bit-level understanding**: Understand how `+` really works under the hood
- **Historical appreciation**: Experience early computer limitations
- **Constraint thinking**: Learn to solve problems within tight boundaries

**Algorithmic Consequences:**
The constraints force us to use classical algorithms instead of shortcuts:

- **Multiplication**: Shift-and-add algorithm instead of `*` operator
- **Division**: Long division bit-by-bit instead of `/` operator
- **Exponentiation**: Binary exponentiation (square-and-multiply)
- **Square root**: Newton-Raphson method with integer arithmetic
- **Shifting**: Manual array copying instead of bit shift operators

**Why:**
This project proves you can build a complete arithmetic system using binary
operations. Computers already have hardware for math and we have standard
library functions for it too but this project recreates it as though they don't
even exist, except for the most basic ones. We can do all sorts of boolean logic
if we can just do extremely simple things, like comparing individual bits in
if statements and for loops.

## Features ✨

### ✅ Implemented Operations

#### Bitwise Operations (`src/bitwise.h`) 🔧
- **NOT** (`binNOT`): Bitwise negation
- **AND** (`binAND`): Bitwise AND
- **OR** (`binOR`): Bitwise OR
- **XOR** (`binXOR`): Bitwise XOR
- **Most Significant Bit** (`binMSB`, `binMSBi`): Get MSB value or index
- **Least Significant Bit** (`binLSBi`): Get LSB index
- **Shift Operations**:
  - Left shift (`binShiftL`, `binShiftL1`)
  - Right shift (`binShiftR`, `binShiftR1`)
  - Shift out zeros (`binShiftOutZerosL`, `binShiftOutZerosR`)
- **Rotate operations** (`binRotateL`, `binRotateR`): Rotate a numbers bits
around left and right.

#### Mathematical Operations (`src/math.h`) 🧮
- **Addition** (`binAdd`, `binIncrement`)
- **Subtraction** (`binSubtract`, `binDecrement`)
- **Multiplication** (`binMultiply`)
- **Division** (`binDivide`)
- **Modulus** (`binModulus`)
- **Exponentiation** (`binPow`)

#### Boolean Operations (`src/boolean.h`) 🔀
- **Equality** (`binEQ`, `binEQZero`, `binEQOne`, `binEQMax`)
- **Comparison** (`binGT`, `binLT`, `binGTEQ`, `binLTEQ`)
- **Utility macros**: `binMin`, `binMax`

#### Core Utilities (`src/bin.h`) 🛠️
- **Creation**: `binNew()` - Create bin from integer
- **Conversion**: `binToInt()` - Convert bin to integer
- **Display**: `binPrint()`, `binIntPrint()` - Pretty printing
- **Random**: `binRand()`, `binRandr()` - Random number generation

### ❌ Not Yet Implemented 🚧
- Bitwise
    - Bit counting: binPopCount() - Count set bits (population count)
    - Bit scanning: binFindFirstSet(), binFindLastSet() - Find first/last set bit
- Math
    - Logarithm functions: binLog2(), binLog10() - Binary and decimal logarithms
    - Square root: binSqrt() - Integer square root
    - Factorial: binFactorial() - For small numbers (up to 8)
    - GCD/LCM: binGCD(), binLCM() - Greatest common divisor, least common multiple
    - Prime checking: binIsPrime() - Test if number is prime
    - Next/Previous prime: binNextPrime(), binPrevPrime()


## Building and Testing 🔨

### Prerequisites
- Clang compiler
- Make

### Build Commands
```bash
# Build the library
make
ls build/libbin.so

# Run all tests
make test

# Clean build artifacts
make clean
```

### Test Coverage 🧪
The project includes comprehensive unit tests:
- `bin_tests.c` - Core functionality tests
- `bitwise_tests.c` - Bitwise operation tests
- `math_tests.c` - Mathematical operation tests
- `boolean_tests.c` - Boolean logic tests

## Usage Example 💡

```c
#include "src/bin.h"
#include "src/bitwise.h"
#include "src/math.h"
#include "src/boolean.h"

int main() {
    // Create binary numbers
    bin a = binNew(5);   // 0000000000000101
    bin b = binNew(3);   // 0000000000000011

    // Perform operations
    bin sum = binAdd(a, b);           // 8
    bin product = binMultiply(a, b);  // 15
    bin xored = binXOR(a, b);         // 6

    // Display results
    binPrint(a);
    binPrint(b);
    binPrint(sum);

    return 0;
}
```

## Project Structure 📁

```
libbin/
├── src/                    # Source files
│   ├── 16.h              # Core type definitions
│   ├── bin.h             # Core utilities
│   ├── bitwise.h         # Bitwise operations
│   ├── math.h            # Mathematical operations
│   └── boolean.h         # Boolean logic
├── test/                  # Unit tests
├── build/                 # Build artifacts
├── bin/                   # Executables
└── Makefile              # Build configuration
```

## Educational Value 🎓

This project demonstrates:
- How computers perform arithmetic using only logical operations
- Implementation of fundamental algorithms from first principles
- Clean separation of concerns in library design
- Comprehensive testing practices
- Constraint-based programming challenges

## Contributing 🤝

When adding new features:
1. Follow the implementation constraints strictly
2. Write unit tests for all new functionality
3. Update this README to reflect new capabilities
4. Ensure all tests pass before submitting

