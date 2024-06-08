all: compile link

compile:
	g++ -c game_of_life.cpp -I <SFML include path>

link:
	g++ game_of_life.o -o GameOfLife -L <SFML lib path> -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.exe *.o
