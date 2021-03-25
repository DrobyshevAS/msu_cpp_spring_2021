CC=g++
FLAGS=--std=c++17

all: main

main: main.o allocator.o
	$(CC) main.o allocator.o $(FLAGS) -o main

allocator.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) -c allocator.cpp

test: main
	./main

clean:
	rm -f *.o my_allocator