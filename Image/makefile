all: main

main: main.o Image.o Timer.o
	g++ main.o Image.o Timer.o -lSDL -lSDL_image -o main

main.o: main.cpp
	g++ -c main.cpp

Image.o: Image.cpp
	g++ -c Image.cpp

Timer.o: Timer.cpp
	g++ -c Timer.cpp

clean: 
	rm -f *.o main
