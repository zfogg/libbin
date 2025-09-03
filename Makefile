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

RELEASE_FLAGS  := -O3 -DNDEBUG -march=native -funroll-loops -ffast-math
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
TARGET_DEBUG := $(OUT_D)/lib$(T)_debug.so
TARGET_RELEASE := $(OUT_D)/lib$(T)_release.so
TARGET_COVERAGE := $(OUT_D)/lib$(T)_coverage.so
TARGET_ASAN := $(OUT_D)/lib$(T)_asan.so
TARGET_UBSAN := $(OUT_D)/lib$(T)_ubsan.so

TESTS := $(BIN_D)/bin_tests
TESTS_DEBUG := $(BIN_D)/bin_tests_debug
TESTS_COVERAGE := $(BIN_D)/bin_tests_coverage
TESTS_ASAN := $(BIN_D)/bin_tests_asan
TESTS_UBSAN := $(BIN_D)/bin_tests_ubsan
TESTS_RELEASE := $(BIN_D)/bin_tests_release

# Environment
export LD_LIBRARY_PATH = $(OUT_D)

# =============================================================================
# Build Rules
# =============================================================================

# Default target
.PHONY: all default clean debug release tests tests-debug tests-coverage tests-asan tests-ubsan tests-release test test-debug test-coverage test-asan test-ubsan test-release check check-tidy check-cppcheck coverage help
all: default

default: $(TARGET)

# Build modes
debug: $(TARGET_DEBUG)

release: $(TARGET_RELEASE)

# Help target
help:
	@echo "Available targets:"
	@echo "  all/default    - Build the standard library (libbin.so)"
	@echo "  debug         - Build library with debug flags (libbin_debug.so)"
	@echo "  release       - Build library with optimized flags (libbin_release.so)"
	@echo ""
	@echo "Build test binaries:"
	@echo "  tests         - Build test binary with optimized flags"
	@echo "  tests-debug   - Build test binary with debug flags"
	@echo "  tests-coverage - Build test binary with coverage flags"
	@echo "  tests-asan    - Build test binary with AddressSanitizer"
	@echo "  tests-ubsan   - Build test binary with UndefinedBehaviorSanitizer"
	@echo "  tests-release - Build test binary with release flags"
	@echo ""
	@echo "Run tests:"
	@echo "  test          - Build and run tests with optimized flags"
	@echo "  test-debug    - Build and run tests with debug flags"
	@echo "  test-coverage - Build and run tests with coverage reporting"
	@echo "  test-asan     - Build and run tests with AddressSanitizer"
	@echo "  test-ubsan    - Build and run tests with UndefinedBehaviorSanitizer"
	@echo "  test-release  - Build and run tests with release flags"
	@echo ""
	@echo "Analysis:"
	@echo "  check         - Run all static analysis checks"
	@echo "  check-tidy    - Run clang-tidy static analysis"
	@echo "  check-cppcheck - Run cppcheck static analysis"
	@echo "  coverage      - Generate coverage report"
	@echo ""
	@echo "Cleanup:"
	@echo "  clean         - Clean all build artifacts"

# Clean target
clean:
	rm -rf $(OUT_D)/* $(BIN_D)/*
	find . -name "*.gcov" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete

# =============================================================================
# Build Test Targets
# =============================================================================

tests: $(TESTS)

tests-debug: $(TESTS_DEBUG)

tests-coverage: $(TESTS_COVERAGE)

tests-asan: $(TESTS_ASAN)

tests-ubsan: $(TESTS_UBSAN)

tests-release: release $(TESTS_RELEASE)

# =============================================================================
# Run Test Targets
# =============================================================================

test: tests
	./$(TESTS)

test-debug: tests-debug
	./$(TESTS_DEBUG)

test-coverage: tests-coverage
	./$(TESTS_COVERAGE)

test-asan: tests-asan
	./$(TESTS_ASAN)

test-ubsan: tests-ubsan
	./$(TESTS_UBSAN)

test-release: tests-release
	./$(TESTS_RELEASE)

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

$(TARGET_DEBUG): $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-debug.o, $(SOURCES)) | $(OUT_D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(CFLAGS_SHARED) $(LDFLAGS_SHARED) $^ -o $@

$(TARGET_RELEASE): $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-release.o, $(SOURCES)) | $(OUT_D)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(CFLAGS_SHARED) $(LDFLAGS_SHARED) $^ -o $@

$(TARGET_COVERAGE): $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-coverage.o, $(SOURCES)) | $(OUT_D)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(CFLAGS_SHARED) $(LDFLAGS_SHARED) $(LDFLAGS_COVERAGE) $^ -o $@

$(TARGET_ASAN): $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-asan.o, $(SOURCES)) | $(OUT_D)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(CFLAGS_SHARED) $(LDFLAGS_SHARED) $(LDFLAGS_ASAN) $^ -o $@

$(TARGET_UBSAN): $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-ubsan.o, $(SOURCES)) | $(OUT_D)
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) $(CFLAGS_SHARED) $(LDFLAGS_SHARED) $(LDFLAGS_UBSAN) $^ -o $@

# =============================================================================
# Test Executables
# =============================================================================

$(TESTS): $(TEST_OBJECTS) $(TARGET) | $(BIN_D)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $@ $(LDFLAGS_TEST) -l$(T)

$(TESTS_DEBUG): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-debug.o, $(TEST_SOURCES)) $(TARGET_DEBUG) | $(BIN_D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-debug.o, $(TEST_SOURCES)) -o $@ $(LDFLAGS_TEST) $(TARGET_DEBUG)

$(TESTS_COVERAGE): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-coverage.o, $(TEST_SOURCES)) $(TARGET_COVERAGE) | $(BIN_D)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-coverage.o, $(TEST_SOURCES)) -o $@ $(LDFLAGS_TEST) $(LDFLAGS_COVERAGE) $(TARGET_COVERAGE)

$(TESTS_ASAN): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-asan.o, $(TEST_SOURCES)) $(TARGET_ASAN) | $(BIN_D)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-asan.o, $(TEST_SOURCES)) -o $@ $(LDFLAGS_TEST) $(LDFLAGS_ASAN) $(TARGET_ASAN)

$(TESTS_UBSAN): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-ubsan.o, $(TEST_SOURCES)) $(TARGET_UBSAN) | $(BIN_D)
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-ubsan.o, $(TEST_SOURCES)) -o $@ $(LDFLAGS_TEST) $(LDFLAGS_UBSAN) $(TARGET_UBSAN)

$(TESTS_RELEASE): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-release.o, $(TEST_SOURCES)) $(TARGET_RELEASE) | $(BIN_D)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-release.o, $(TEST_SOURCES)) -o $@ $(LDFLAGS_TEST) $(TARGET_RELEASE)

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
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(CFLAGS_SHARED) -c $< -o $@

$(OUT_D)/%-debug.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Coverage object files
$(OUT_D)/%-coverage.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(CFLAGS_SHARED) -c $< -o $@

$(OUT_D)/%-coverage.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# AddressSanitizer object files
$(OUT_D)/%-asan.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(CFLAGS_SHARED) -c $< -o $@

$(OUT_D)/%-asan.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@

# UBSan object files
$(OUT_D)/%-ubsan.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) $(CFLAGS_SHARED) -c $< -o $@

$(OUT_D)/%-ubsan.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(UBSAN_FLAGS) -c $< -o $@

# Release object files
$(OUT_D)/%-release.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(CFLAGS_SHARED) -c $< -o $@

$(OUT_D)/%-release.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -c $< -o $@

