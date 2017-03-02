CPPFLAGS = -Wall -std=c++11 -pedantic -g
BIN = .
SRC = src
ALL_SRCS = $(wildcard $(SRC)/*.cpp)

all: $(ALL_SRCS)
	g++ $(CPPFLAGS) $(ALL_SRCS) -o $(BIN)/SlimeRPG
