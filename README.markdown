# libbin

A C library implementing bitwise, numerical, and logical operations using a custom 16-bit binary representation. This project demonstrates how to implement fundamental computer operations using only basic logical operators.

## Overview

libbin provides a complete set of arithmetic and logical operations implemented using a custom `bin` type that represents 16-bit values as arrays of individual bits. The library is built with strict constraints to demonstrate fundamental computer science concepts.

## Architecture

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

## Implementation Constraints

The library follows strict implementation rules:
- **Allowed operators**: Only `&&`, `||`, and `!` from C
- **Type restriction**: Use only the `bin` type as defined in `./src/16.h`
- **No base conversion**: Cannot convert between number bases
- **Array indexing**: May use `+` and `-` for array indexing only
- **Minor exceptions**: Simple loops are allowed

## Features

### ✅ Implemented Operations

#### Bitwise Operations (`src/bitwise.h`)
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

#### Mathematical Operations (`src/math.h`)
- **Addition** (`binAdd`, `binIncrement`)
- **Subtraction** (`binSubtract`, `binDecrement`)
- **Multiplication** (`binMultiply`)
- **Division** (`binDivide`)
- **Modulus** (`binModulus`)
- **Exponentiation** (`binPow`)

#### Boolean Operations (`src/boolean.h`)
- **Equality** (`binEQ`, `binEQZero`, `binEQOne`, `binEQMax`)
- **Comparison** (`binGT`, `binLT`, `binGTEQ`, `binLTEQ`)
- **Utility macros**: `binMin`, `binMax`

#### Core Utilities (`src/bin.h`)
- **Creation**: `binNew()` - Create bin from integer
- **Conversion**: `binToInt()` - Convert bin to integer
- **Display**: `binPrint()`, `binIntPrint()` - Pretty printing
- **Random**: `binRand()`, `binRandr()` - Random number generation

### ❌ Not Yet Implemented
- Rotate left/right operations
- Logarithm functions
- Additional boolean operations

## Building and Testing

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

### Test Coverage
The project includes comprehensive unit tests:
- `bin_tests.c` - Core functionality tests
- `bitwise_tests.c` - Bitwise operation tests  
- `math_tests.c` - Mathematical operation tests
- `boolean_tests.c` - Boolean logic tests

## Usage Example

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

## Project Structure

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

## Educational Value

This project demonstrates:
- How computers perform arithmetic using only logical operations
- Implementation of fundamental algorithms from first principles
- Clean separation of concerns in library design
- Comprehensive testing practices
- Constraint-based programming challenges

## Contributing

When adding new features:
1. Follow the implementation constraints strictly
2. Write unit tests for all new functionality
3. Update this README to reflect new capabilities
4. Ensure all tests pass before submitting

