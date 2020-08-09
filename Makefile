CXX ?= g++

LIBS =-lSDL2 -lSDL2_gfx -lSDL2main
FLAGS=-std=c++11

EXE=tictactoe

tictactoe: main.cpp Tictactoe.cpp Tictactoe.hpp
	$(CXX) main.cpp Tictactoe.cpp $(LIBS) -o $(EXE) $(FLAGS)

clean:
	rm -f $(EXE)
