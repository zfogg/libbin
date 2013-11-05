#!/bin/make -f


SRC_DIR = src

OUT_DIR = build

BIN_DIR = bin


CLANG = clang -std=c99 -Wextra -O2


OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

HEADERS = $(wildcard $(SRC_DIR)/*.h)


TARGET = $(OUT_DIR)/libbin.so

TESTS = $(BIN_DIR)/bin_tests


export LD_LIBRARY_PATH=$(OUT_DIR)

.PHONY: default all clean


default: $(TARGET)

all: default

clean:
	-rm -rf tags
	-rm -rf $(OUT_DIR)/* $(BIN_DIR)/*

test: $(TESTS)
	$(TESTS)

tags:
	ctags -R --sort=yes .


$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CLANG) -c -fpic $< -o $@

$(OUT_DIR)/%.so: $(OUT_DIR)/%.o
	$(CLANG) -shared -o $(OUT_DIR)/$(*F).so $<

$(TESTS): all
	$(CLANG) ./test/bin_tests.c -o $(TESTS) -L$(OUT_DIR) -lbin
