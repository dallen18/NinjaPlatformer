all: compile link

compile:
	g++ -g src/Main.cpp -c Main.o
	mv Main.o obj
	
link:
	g++ obj/Main.o -o Main.exe -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm obj/Main.o Main.exe

