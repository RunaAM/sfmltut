compile: main.cpp
	g++ -c main.cpp
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

shooter: shooter.cpp
	g++ -c shooter.cpp
	g++ shooter.o -o shooter -lsfml-graphics -lsfml-window -lsfml-system
	./shooter

dodger: dodger.cpp Textures/cat.png Textures/doge.png
	g++ -c dodger.cpp
	g++ dodger.o -o dodger -lsfml-graphics -lsfml-window -lsfml-system -I/Textures/cat.png -I/Textures/doge.png
	./dodger

360: 360shooter/360shooter.cpp 
	g++ -c 360shooter/360shooter.cpp
	g++ 360shooter/360shooter.o -o 360shooter/360shooter -lsfml-graphics -lsfml-window -lsfml-system 
	360shooter/./360shooter