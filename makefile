FLAGS=-ggdb -c -o

all: main

main: main.o bmp_func.o
	gcc -ggdb -o main main.o bmp_func.o

main.o: main.c
	gcc $(FLAGS) main.o main.c

bmp_func.o: bmp_func.c
	gcc $(FLAGS) bmp_func.o bmp_func.c

clean:
	rm -f main.o bmp_func.o main
