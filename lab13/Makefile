.PHONY: clean

CC = gcc

all: main

main: main.o sneakers.o
	$(CC) main.o sneakers.o -o main

lib/libmylib.a: main.o sneakers.o
	mkdir -p lib
	ar rcs lib/libmylib.a main.o sneakers.o

main.o: src/main.c
	$(CC) -c src/main.c -o main.o -I ./include

sneakers.o: src/sneakers.c
	$(CC) -c src/sneakers.c -o sneakers.o -I ./include

clean:
	rm -f *.o main
	rm -rf lib