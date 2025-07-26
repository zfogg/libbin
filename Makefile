#!/bin/make -f

# Directories
SRC_D = src
OUT_D = build
BIN_D = bin
TEST_D = test

# Compiler and flags
CC = clang
CFLAGS = -std=c2x -Wextra -Wall -O2 -g 
CFLAGS_DEBUG = -std=c2x -Wextra -Wall -Wpedantic -Wconversion -Wshadow -O0 -g3 -DDEBUG
CFLAGS_COVERAGE = $(CFLAGS_DEBUG) --coverage
CFLAGS_ASAN = $(CFLAGS_DEBUG) -fsanitize=address -fno-omit-frame-pointer
CFLAGS_SHARED = -fpic

LDFLAGS          = -lm
LDFLAGS_SHARED   = $(LDFLAGS) -shared
LDFLAGS_TEST     = $(LDFLAGS) -L$(OUT_D)
LDFLAGS_COVERAGE = $(LDFLAGS) --coverage
LDFLAGS_ASAN     = $(LDFLAGS) -fsanitize=address

# Static analysis tools
CLANG_TIDY = /opt/homebrew/opt/llvm/bin/clang-tidy
CPPCHECK = cppcheck

# Library name
T = bin

# Source files
SOURCES = $(wildcard $(SRC_D)/*.c)
TEST_SOURCES = $(wildcard $(TEST_D)/*.c)

# Object files
OBJECTS = $(patsubst $(SRC_D)/%.c, $(OUT_D)/%.o, $(SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_D)/%.c, $(OUT_D)/%.o, $(TEST_SOURCES))

# Header files
HEADERS = $(wildcard $(SRC_D)/*.h)
TEST_HEADERS = $(wildcard $(TEST_D)/*.h)

# Targets
TARGET = $(OUT_D)/lib$(T).so
TESTS = $(BIN_D)/bin_tests
TESTS_DEBUG = $(BIN_D)/bin_tests_debug
TESTS_COVERAGE = $(BIN_D)/bin_tests_coverage
TESTS_ASAN = $(BIN_D)/bin_tests_asan

# Environment
export LD_LIBRARY_PATH = $(OUT_D)

# Default target
.PHONY: all default clean test test-debug test-coverage test-asan check check-tidy check-cppcheck coverage help
all: default

default: $(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all/default    - Build the library (default)"
	@echo "  test          - Run tests with optimized build"
	@echo "  test-debug    - Run tests with debug build"
	@echo "  test-coverage - Run tests with coverage reporting"
	@echo "  test-asan     - Run tests with AddressSanitizer"
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

# Test targets
test: all $(TESTS)
	./$(TESTS)

test-debug: $(TESTS_DEBUG)
	./$(TESTS_DEBUG)

test-coverage: $(TESTS_COVERAGE)
	./$(TESTS_COVERAGE)

test-asan: $(TESTS_ASAN)
	./$(TESTS_ASAN)

# Static analysis targets
check: check-cppcheck check-tidy

check-tidy:
	@echo "Running clang-tidy static analysis..."
	$(CLANG_TIDY) $(SOURCES) -- $(CFLAGS) -I$(SRC_D)

check-cppcheck:
	@echo "Running cppcheck static analysis..."
	$(CPPCHECK) --enable=all --std=c2x --inline-suppr --suppress=missingIncludeSystem $(SRC_D)/

# Coverage report
coverage: test-coverage
	@echo "Generating coverage report..."
	llvm-cov gcov -r build/*-coverage.gcno || gcov -r $(OUT_D)/*-coverage.gcno
	@echo "Coverage files generated in build/ directory."
	@echo "Summary:"
	@grep -h "Lines executed" $(OUT_D)/*.gcov | grep -v "test" || true

# Create output directories
$(OUT_D):
	mkdir -p $(OUT_D)

$(BIN_D):
	mkdir -p $(BIN_D)

# Library target
$(TARGET): $(OBJECTS) | $(OUT_D)
	$(CC) $(CFLAGS) $(LDFLAGS_SHARED) $^ -o $@

# Test executables
$(TESTS): $(TEST_OBJECTS) $(OBJECTS) | $(BIN_D)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS_TEST)

$(TESTS_DEBUG): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-debug.o, $(TEST_SOURCES)) $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-debug.o, $(SOURCES)) | $(BIN_D)
	$(CC) $(CFLAGS_DEBUG) $^ -o $@ $(LDFLAGS)

$(TESTS_COVERAGE): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-coverage.o, $(TEST_SOURCES)) $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-coverage.o, $(SOURCES)) | $(BIN_D)
	$(CC) $(CFLAGS_COVERAGE) $^ -o $@ $(LDFLAGS_COVERAGE)

$(TESTS_ASAN): $(patsubst $(TEST_D)/%.c, $(OUT_D)/%-asan.o, $(TEST_SOURCES)) $(patsubst $(SRC_D)/%.c, $(OUT_D)/%-asan.o, $(SOURCES)) | $(BIN_D)
	$(CC) $(CFLAGS_ASAN) $^ -o $@ $(LDFLAGS_ASAN)

# Object files for library
$(OBJECTS): $(OUT_D)/%.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(CFLAGS_SHARED) -c $< -o $@

# Object files for tests
$(TEST_OBJECTS): $(OUT_D)/%.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(CFLAGS_SHARED) -c $< -o $@

# Debug object files
$(OUT_D)/%-debug.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

$(OUT_D)/%-debug.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

# Coverage object files
$(OUT_D)/%-coverage.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS_COVERAGE) -c $< -o $@

$(OUT_D)/%-coverage.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS_COVERAGE) -c $< -o $@

# AddressSanitizer object files
$(OUT_D)/%-asan.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS_ASAN) -c $< -o $@

$(OUT_D)/%-asan.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS_ASAN) -c $< -o $@

