# Simple cross-platform Makefile (POSIX shells).
# Windows users without make can use build.ps1.

CC ?= cc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude
SRC_BASE = $(wildcard src/*.c)
SRC_EX   = $(wildcard src/examples/*.c)
OBJ      = $(SRC_BASE:.c=.o) $(SRC_EX:.c=.o)
BIN      = bin/learnc

all: $(BIN)

$(BIN): $(SRC_BASE) $(SRC_EX)
	$(CC) $(CFLAGS) $(SRC_BASE) $(SRC_EX) -o $(BIN)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
