FLAGS=-ggdb -c -o

all: main

main: main.o
	gcc -ggdb -o main main.o

main.o: main.c
	gcc $(FLAGS) main.o main.c

clean:
	rm -f main.o main
