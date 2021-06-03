CC=g++
FLAGS=--std=c++17

all: main

main: main.o BigInt.o
	$(CC) main.o BigInt.o $(FLAGS) -o main

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

BigInt.o: BigInt.cpp BigInt.hpp
	$(CC) $(FLAGS) -c BigInt.cpp

test: main
	./main

clean:
	rm -rf *.o BigInt