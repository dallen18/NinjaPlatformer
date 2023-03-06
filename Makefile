all: clean compile link

compile:
	g++ -g src/Main.cpp -c Main.o
	g++ -g src/Player.cpp -c Player.o
	g++ -g src/Game.cpp -c Game.o
	g++ -g src/Entity.cpp -c Entity.o
	g++ -g src/Enemy.cpp -c Game.o
	g++ -g src/Block.cpp -c Block.o
	g++ -g src/Button.cpp -c Button.o
	g++ -g src/Menu.cpp -c Menu.o
	mv Main.o obj
	mv Player.o obj
	mv Game.o obj
	mv Entity.o obj
	mv Enemy.o obj
	mv Block.o obj
	mv Button.o obj
	mv Menu.o obj
	
link:
	g++ obj/Main.o obj/Player.o obj/Game.o obj/Entity.o obj/Enemy.o obj/Block.o obj/Button.o obj/Menu.o -o Main.exe -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm obj/Main.o obj/Player.o obj/Game.o obj/Entity.o obj/Enemy.o obj/Block.o obj/Button.o obj/Menu.o Main.exe 

