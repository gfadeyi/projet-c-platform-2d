CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -Iinclude $(shell sdl-config --cflags)
LDFLAGS = $(filter-out -mwindows,$(shell sdl-config --libs))

ifeq ($(OS),Windows_NT)
    EXE = platformer.exe
else
    EXE = platformer
endif

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -rf build $(EXE)

.PHONY: all run clean
