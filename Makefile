all: clean compile link

files := src/Main.cpp src/Sound.cpp src/Projectile.cpp src/Player.cpp src/Game.cpp src/Entity.cpp src/Block.cpp src/Enemy.cpp src/Button.cpp src/Menu.cpp src/NPC.cpp src/tinyxml2.cpp src/InputManager.cpp src/Hud.cpp

libs := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

compile:
	g++ -g $(files) -c
	mv *.o obj
	
link:
	g++ obj/* -o Main.exe $(libs)

clean:
	rm obj/* Main.exe 

