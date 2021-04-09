CC=g++
FLAGS=--std=c++17 -Wall -Wextra

all: main

main: main.o matrix.o
	$(CC) main.o matrix.o $(FLAGS) -o main

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

My_Parser.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) -c matrix.cpp

test: main
	./main

clean:
	rm -rf *.o matrix