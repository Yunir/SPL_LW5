FLAGS=-ggdb -c -Wall -Werror -Wextra -std=c89 -ansi -pedantic

all: main

main: main.o bmp_func.o
	gcc -ggdb -o main main.o bmp_func.o

main.o: main.c
	gcc $(FLAGS) -o main.o main.c

bmp_func.o: bmp_func.c
	gcc $(FLAGS) -o bmp_func.o bmp_func.c

clean:
	rm -f main *.o ./images/rp.bmp
