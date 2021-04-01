CC=g++
FLAGS=--std=c++17

all: main

main: main.o My_Parser.o
	$(CC) main.o My_Parser.o $(FLAGS) -o main

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

My_Parser.o: My_Parser.cpp My_Parser.hpp
	$(CC) $(FLAGS) -c My_Parser.cpp

test: main
	./main

clean:
	rm -rf *.o My_Parser