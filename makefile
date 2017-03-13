CPP = g++
CPPFLAGS = -Wall -std=c++11 -pedantic -g
BIN = .
SRC = src
CPP_FILES = $(SRC)/entity/entity.cpp $(SRC)/entity/monster.cpp \
	$(SRC)/entity/player.cpp $(SRC)/game.cpp $(SRC)/location.cpp \
	$(SRC)/main.cpp $(SRC)/world.cpp

all:
	$(CPP) $(CPPFLAGS) $(CPP_FILES) -o $(BIN)/SlimeRPG
