CC=g++
FLAGS=--std=c++17 -Wall

all: main

main: main.o 
	$(CC) main.o $(FLAGS) -o main

main.o: main.cpp vector.hpp iterator.hpp allocator.hpp
	$(CC) $(FLAGS) -c main.cpp

test: main
	./main

clean:
	rm -rf *.o main