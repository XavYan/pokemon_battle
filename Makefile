CC=g++
CFLAGS=-g -Wall -Wextra -std=c++17 -I$(INCLUDE)

SRC=src
BIN=bin
INCLUDE=include

EXECUTABLE=pokemonBattle.out

all: main.cpp $(BIN)/battle.o $(BIN)/movement.o $(BIN)/pokemon.o datasets/*.cpp $(BIN)/basicStructures.o $(BIN)/languageManager.o $(BIN)/common.o
	$(CC) $(CFLAGS) main.cpp $(BIN)/battle.o $(BIN)/movement.o $(BIN)/pokemon.o $(BIN)/basicStructures.o $(BIN)/languageManager.o $(BIN)/common.o datasets/*.cpp -o $(EXECUTABLE)

$(BIN)/basicStructures.o: $(INCLUDE)/basicStructures.hpp $(SRC)/basicStructures.cpp
	$(CC) $(CFLAGS) $(SRC)/basicStructures.cpp -c -o $(BIN)/basicStructures.o

$(BIN)/battle.o: $(INCLUDE)/battle.hpp $(SRC)/battle.cpp
	$(CC) $(CFLAGS) $(SRC)/battle.cpp -c -o $(BIN)/battle.o

$(BIN)/movement.o: $(INCLUDE)/movement.hpp $(SRC)/movement.cpp
	$(CC) $(CFLAGS) $(SRC)/movement.cpp -c -o $(BIN)/movement.o

$(BIN)/pokemon.o: $(INCLUDE)/pokemon.hpp $(SRC)/pokemon.cpp
	$(CC) $(CFLAGS) $(SRC)/pokemon.cpp -c -o $(BIN)/pokemon.o

$(BIN)/languageManager.o: $(INCLUDE)/languageManager.hpp $(SRC)/languageManager.cpp
	$(CC) $(CFLAGS) $(SRC)/languageManager.cpp -c -o $(BIN)/languageManager.o

$(BIN)/common.o: $(INCLUDE)/common.hpp $(SRC)/common.cpp
	$(CC) $(CFLAGS) $(SRC)/common.cpp -c -o $(BIN)/common.o

.PHONY: clean all

clean:
	rm -rf ./$(BIN)/*.o ./$(EXECUTABLE)