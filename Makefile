CXX ?= g++

LIBS =-lSDL2 -lSDL2_gfx -lSDL2main
FLAGS=-std=c++11

EXE=tictactoe

tictactoe: main.cpp Tictactoe.cpp Tictactoe.hpp
	$(CXX) $(LIBS) $(FLAGS) main.cpp Tictactoe.cpp -o $(EXE)

clean:
	rm -f $(EXE)
