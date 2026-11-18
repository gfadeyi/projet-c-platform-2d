# Makefile - Projet C Platform 2D
# Fonctionne sous Ubuntu (gcc + libsdl1.2-dev) et sous Windows (MSYS2 UCRT64).
#
#   make        compile le jeu
#   make run    compile puis lance le jeu
#   make clean  supprime les fichiers générés

# Compilateur et options
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g -Iinclude $(shell sdl-config --cflags)
# -mwindows cacherait la console sous Windows : on l'enlève pour voir les printf
LDFLAGS = $(filter-out -mwindows,$(shell sdl-config --libs))

# Nom de l'exécutable (.exe sous Windows)
ifeq ($(OS),Windows_NT)
    EXE = platformer.exe
else
    EXE = platformer
endif

# Tous les .c de src/ et les .o correspondants dans build/
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

# Cible par défaut
all: $(EXE)

# Édition des liens : assembler les .o et SDL en un exécutable
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compilation : chaque src/x.c donne build/x.o
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -rf build $(EXE)

# Ces cibles ne sont pas des fichiers
.PHONY: all run clean
