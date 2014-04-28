all: main

main: main.o background.o Timer.o sprite.o player.o scoreCounter.o menuScreen.o
	g++ main.o Timer.o background.o sprite.o player.o scoreCounter.o menuScreen.o -lSDL -lSDL_image -lSDL_mixer -o main

main.o: main.cpp
	g++ -c main.cpp

background.o: background.cpp
	g++ -c background.cpp

Timer.o: Timer.cpp
	g++ -c Timer.cpp

sprite.o: sprite.cpp
	g++ -c sprite.cpp

player.o: player.cpp
	g++ -c player.cpp

scoreCounter.o: scoreCounter.cpp
	g++ -c scoreCounter.cpp

menuScreen.o: menuScreen.cpp
	g++ -c menuScreen.cpp

clean: 
	rm -f *.o main
