# Usage:
#   make TARGET=linux
#   make TARGET=windows
#   make TARGET=windows CC=x86_64-w64-mingw32-gcc

TARGET ?= linux
CC     ?= gcc
CFLAGS ?= -Wall -Wextra -O2
INC     = -Iinclude

ifeq ($(TARGET),linux)
  SRC   = src/main.c src/net_posix.c src/shell_posix.c
  OUT   = build/rshell-linux
  LIBS  =
endif

ifeq ($(TARGET),windows)
  # Cross-compile from Linux with: sudo apt install mingw-w64
  CC    = x86_64-w64-mingw32-gcc
  SRC   = src/main.c src/net_win.c src/shell_win.c
  OUT   = build/rshell.exe
  LIBS  = -lws2_32
endif

all: $(OUT)

$(OUT): $(SRC) | build
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(OUT) $(LIBS)

build:
	mkdir -p build

clean:
	rm -rf build

.PHONY: all clean