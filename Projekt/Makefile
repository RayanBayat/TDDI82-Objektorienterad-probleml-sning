FLAGS := -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -g
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Run processes in parallel
NPROCS = $(shell grep -c 'processor' /proc/cpuinfo)
MAKEFLAGS += -j$(NPROCS)

all: main.o game.o game_state.o menu_state.o graphics.o
	g++ $(FLAGS) main.o game.o game_state.o menu_state.o graphics.o -o game $(LIBS)

main.o: src/main.cc
	g++ $(FLAGS) src/main.cc -c -o main.o

game.o: src/game.cc
	g++ $(FLAGS) src/game.cc -c -o game.o

menu_state.o: src/menu_state.cc
	g++ $(FLAGS) src/menu_state.cc -c -o menu_state.o

game_state.o: src/game_state.cc
	g++ $(FLAGS) src/game_state.cc -c -o game_state.o

graphics.o: src/graphics.cc
	g++ $(FLAGS) src/graphics.cc -c -o graphics.o


.PHONY: clean
clean:
	rm *.o game

.PHONY: run
run:
	make; ./game
