#!/bin/make -f

# Directories
SRC_D = src
OUT_D = build
BIN_D = bin
TEST_D = test

# Compiler and flags
CC = clang
CFLAGS = -std=c99 -Wextra -Wall -O2 -g
CFLAGS_SHARED = -fpic
LDFLAGS = 
LDFLAGS_SHARED = -shared
LDFLAGS_TEST = -L$(OUT_D)

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

# Environment
export LD_LIBRARY_PATH = $(OUT_D)

# Default target
.PHONY: all default clean test
all: default

default: $(TARGET)

# Clean target
clean:
	rm -rf $(OUT_D)/* $(BIN_D)/*

# Test target
test: all $(TESTS)
	./$(TESTS)

# Create output directories
$(OUT_D):
	mkdir -p $(OUT_D)

$(BIN_D):
	mkdir -p $(BIN_D)

# Library target
$(TARGET): $(OBJECTS) | $(OUT_D)
	$(CC) $(CFLAGS) $(LDFLAGS_SHARED) $^ -o $@

# Test executable
$(TESTS): $(TEST_OBJECTS) $(OBJECTS) | $(BIN_D)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS_TEST) -l$(T)

# Object files for library
$(OBJECTS): $(OUT_D)/%.o: $(SRC_D)/%.c $(HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(CFLAGS_SHARED) -c $< -o $@

# Object files for tests
$(TEST_OBJECTS): $(OUT_D)/%.o: $(TEST_D)/%.c $(TEST_HEADERS) | $(OUT_D)
	$(CC) $(CFLAGS) $(CFLAGS_SHARED) -c $< -o $@

