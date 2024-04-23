# Compiler and linker definitions
CFLAGS = -I src/include -L src/lib
LIBS = -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
SRC := $(wildcard *.c)
CC = gcc

# Specify building directory
BUILD_DIR = build

# Default target
all: $(BUILD_DIR)/main

# Build target for app
$(BUILD_DIR)/main: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)