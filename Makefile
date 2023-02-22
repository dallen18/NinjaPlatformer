all: clean compile link

compile:
	g++ -g src/Main.cpp -c Main.o
	g++ -g src/Player.cpp -c Player.o
	g++ -g src/Game.cpp -c Game.o
	mv Main.o obj
	mv Player.o obj
	mv Game.o obj
	
link:
	g++ obj/Main.o obj/Player.o obj/Game.o -o Main.exe -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm obj/Main.o obj/Player.o obj/Game.o Main.exe 

