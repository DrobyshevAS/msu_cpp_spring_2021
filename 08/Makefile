CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra

all: pool
pool: main.o
		$(CC) main.o -pthread -o pool 
main.o: main.cpp
		$(CC) main.cpp -c 
clean:
		rm -rf *.o pool
test:
		./pool