CC=g++
FLAGS=--std=c++17

all: main

main: main.o 
	$(CC) main.o $(FLAGS) -o main

main.o: main.cpp serializer.hpp serializer.tpp
	$(CC) $(FLAGS) -c main.cpp

test: main
	./main

clean:
	rm -rf *.o My_Parser