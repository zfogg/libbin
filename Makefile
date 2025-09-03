#!/bin/make -f

# =============================================================================
# Configuration
# =============================================================================

# Compiler
CC := clang

# Directories
SRC_D := src
OUT_D := build
BIN_D := bin
TEST_D := test

# Library name
T := bin

# =============================================================================
# Compiler Flags
# =============================================================================

CSTD ?= c23

# Base flags
override CFLAGS += -Wall -Wextra -std=$(CSTD)

# Static analysis tools
CLANG_TIDY := clang-tidy
CPPCHECK := cppcheck

# =============================================================================
# Link Flags
# =============================================================================

LDFLAGS          := -lm
LDFLAGS_SHARED   := $(LDFLAGS) -shared
LDFLAGS_TEST     := $(LDFLAGS) -L$(OUT_D)
LDFLAGS_COVERAGE := $(LDFLAGS) --coverage
LDFLAGS_ASAN     := $(LDFLAGS) -fsanitize=address
LDFLAGS_UBSAN    := $(LDFLAGS) -fsanitize=undefined

# =============================================================================
# Build Mode Flags
# =============================================================================

DEBUG_FLAGS    := -O0 -g3 -DDEBUG -Wpedantic -Wconversion -Wshadow \
                  -Wformat-security -Wstrict-prototypes -Wmissing-prototypes \
                  -Wundef -Wcast-align -Wwrite-strings -Wredundant-decls \
                  -Wnested-externs -Winline -Wvla -fstack-protector-strong \
                  -D_FORTIFY_SOURCE=2 -fno-omit-frame-pointer

RELEASE_FLAGS  := -O3 -DNDEBUG -march=native -flto -funroll-loops -ffast-math
COVERAGE_FLAGS := $(DEBUG_FLAGS) --coverage
ASAN_FLAGS     := $(DEBUG_FLAGS) -fsanitize=address -fno-omit-frame-pointer
UBSAN_FLAGS    := $(DEBUG_FLAGS) -fsanitize=undefined -fno-omit-frame-pointer

# Shared library flags
CFLAGS_SHARED := -fpic

# =============================================================================
# File Discovery
# =============================================================================

# Source files
SOURCES := $(wildcard $(SRC_D)/*.c)
TEST_SOURCES := $(wildcard $(TEST_D)/*.c)

# Object files
OBJECTS := $(patsubst $(SRC_D)/%.c, $(OUT_D)/%.o, $(SOURCES))
TEST_OBJECTS := $(patsubst $(TEST_D)/%.c, $(OUT_D)/%.o, $(TEST_SOURCES))

# Header files
HEADERS := $(wildcard $(SRC_D)/*.h)
TEST_HEADERS := $(wildcard $(TEST_D)/*.h)

# =============================================================================
# Targets
# =============================================================================

TARGET := $(OUT_D)/lib$(T).so
TESTS := $(BIN_D)/bin_tests
TESTS_DEBUG := $(BIN_D)/bin_tests_debug
TESTS_COVERAGE := $(BIN_D)/bin_tests_coverage
TESTS_ASAN := $(BIN_D)/bin_tests_asan
TESTS_UBSAN := $(BIN_D)/bin_tests_ubsan

# Environment
export LD_LIBRARY_PATH = $(OUT_D)

# =============================================================================
# Build Rules
# =============================================================================

# Default target
.PHONY: all default clean debug release test test-debug test-coverage test-asan test-ubsan test-release check check-tidy check-cppcheck coverage help
all: default

default: $(TARGET)

# Build modes
debug:
	$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" $(TARGET)

release:
	$(MAKE) CFLAGS="$(CFLAGS) $(RELEASE_FLAGS)" $(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all/default    - Build the library (default)"
	@echo "  debug         - Build library with debug flags"
	@echo "  release       - Build library with optimized flags"
	@echo "  test          - Run tests with optimized build"
	@echo "  test-debug    - Run tests with debug build"
	@echo "  test-coverage - Run tests with coverage reporting"
	@echo "  test-asan     - Run tests with AddressSanitizer"
	@echo "  test-ubsan    - Run tests with UndefinedBehaviorSanitizer"
	@echo "  test-release  - Run tests with release build (alias for test)"
	@echo "  check         - Run all static analysis checks"
	@echo "  check-tidy    - Run clang-tidy static analysis"
	@echo "  check-cppcheck - Run cppcheck static analysis"
	@echo "  coverage      - Generate coverage report"
	@echo "  clean         - Clean all build artifacts"

# Clean target
clean:
	rm -rf $(OUT_D)/* $(BIN_D)/*
	find . -name "*.gcov" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete

# =============================================================================
# Test Targets
# =============================================================================

test: all $(TESTS)
	./$(TESTS)

test-debug: $(TESTS_DEBUG)
	./$(TESTS_DEBUG)

test-coverage: $(TESTS_COVERAGE)
	./$(TESTS_COVERAGE)

test-asan: $(TESTS_ASAN)
	./$(TESTS_ASAN)

test-ubsan: $(TESTS_UBSAN)
	./$(TESTS_UBSAN)

test-release: release
	$(MAKE) CFLAGS="$(CFLAGS) $(RELEASE_FLAGS)" $(TESTS)
	./$(TESTS)

# =============================================================================
# Static Analysis Targets
# =============================================================================

check: check-cppcheck check-tidy

check-tidy:
	@echo "Running clang-tidy static analysis..."
	$(CLANG_TIDY) $(SOURCES) -- $(CFLAGS) -I$(SRC_D)

check-cppcheck:
	@echo "Running cppcheck static analysis..."
	$(CPPCHECK) --enable=all --std=$(CSTD) --inline-suppr --suppress=missingIncludeSystem $(SRC_D)/

# Coverage report
coverage: test-coverage
	@echo "Generating coverage report..."
	llvm-cov gcov -r build/*-coverage.gcno || gcov -r $(OUT_D)/*-coverage.gcno
	@echo "Coverage files generated in build/ directory."
	@echo "Summary:"
	@grep -h "Lines executed" $(OUT_D)/*.gcov | grep -v "test" || true

# =============================================================================
# Directory Creation
# =============================================================================

$(OUT_D):
	mkdir -p $(OUT_D)

$(BIN_D):
	mkdir -p $(BIN_D)

# =============================================================================
# Library Target
# =============================================================================

$(TARGET): $(OBJECTS) | $(OUT_D)
	$(CC) $(CFLAGS) $(LDFLAGS_SHARED) $^ -o $@

# =============================================================================
# Test Executables
# =============================================================================

$(TESTS): $(TEST_OBJECTS) $(OBJECTS) | $(BIN_D)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS_TEST)

$(TESTS_DEBUG): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-debug.o, $(TEST_SOURCES)) $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-debug.o, $(SOURCES)) | $(BIN_D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@ $(LDFLAGS)

$(TESTS_COVERAGE): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-coverage.o, $(TEST_SOURCES)) $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-coverage.o, $(SOURCES)) | $(BIN_D)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ -o $@ $(LDFLAGS_COVERAGE)

$(TESTS_ASAN): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-asan.o, $(TEST_SOURCES)) $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-asan.o, $(SOURCES)) | $(BIN_D)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $^ -o $@ $(LDFLAGS_ASAN)

$(TESTS_UBSAN): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-ubsan.o, $(TEST_SOURCES)) $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-ubsan.o, $(SOURCES)) | $(BIN_D)
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) $^ -o $@ $(LDFLAGS_UBSAN)

# =============================================================================
# Object File Rules
# =============================================================================

# Object files for library
$(OBJECTS): $(OUT_D)/%.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(CFLAGS_SHARED) -c $< -o $@

# Object files for tests
$(TEST_OBJECTS): $(OUT_D)/%.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(CFLAGS_SHARED) -c $< -o $@

# Debug object files
$(OUT_D)/%-debug.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(OUT_D)/%-debug.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Coverage object files
$(OUT_D)/%-coverage.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

$(OUT_D)/%-coverage.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# AddressSanitizer object files
$(OUT_D)/%-asan.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

$(OUT_D)/%-asan.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

# UBSan object files
$(OUT_D)/%-ubsan.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) -c $< -o $@

$(OUT_D)/%-ubsan.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) -c $< -o $@

