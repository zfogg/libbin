#!/bin/make -f


SRC_D = src

OUT_D = build

BIN_D = bin


CC = clang -std=c99 -Wextra -O2


OBJECTS = $(patsubst $(SRC_D)/%.c, $(OUT_D)/%.o, $(wildcard $(SRC_D)/*.c))

HEADERS = $(wildcard $(SRC_D)/*.h)


TARGET = $(OUT_D)/libbin.so

TESTS = $(BIN_D)/bin_tests


export LD_LIBRARY_PATH=$(OUT_D)

.PHONY: default all clean


default: $(TARGET)

all: default

clean:
	-rm -rf tags
	-rm -rf $(OUT_D)/* $(BIN_D)/*

test: $(TESTS)
	$(TESTS)

tags:
	ctags -R --sort=yes .


$(OBJECTS): $(OUT_D)/%.o: $(SRC_D)/%.c
	$(CC) -c -fpic $< -o $@

$(OUT_D)/%.so: $(OBJECTS)
	$(CC) -shared $(OBJECTS) -o $(OUT_D)/$(*F).so

$(TESTS): all
	$(CC) ./test/bin_tests.c -o $(TESTS) -L$(OUT_D) -lbin
