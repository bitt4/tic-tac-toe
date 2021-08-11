CXX ?= g++

ifeq ($(OS),Windows_NT)
	LIBS +=-lmingw32
	RFLAGS+=-mwindows
endif

LIBS +=-lSDL2main -lSDL2_gfx -lSDL2
FLAGS+=-std=c++11 -O3 -Wall -pedantic

EXE=tictactoe

tictactoe: src/main.cpp src/Tictactoe.cpp include/Tictactoe.hpp
	$(CXX) src/main.cpp src/Tictactoe.cpp $(LIBS) -o $(EXE) $(FLAGS)

clean:
ifeq ($(OS),Windows_NT)
	del $(EXE).exe
else
	rm -f $(EXE)
endif
