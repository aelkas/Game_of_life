all: compile link

compile:
	g++ -c game_of_life.cpp -I "C:/SFML-2.5.1/include"

link:
	g++ game_of_life.o -o GameOfLife -L "C:/SFML-2.5.1/lib" -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.exe *.o