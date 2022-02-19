CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: comp valgrind_run clear

comp:
	$(CC) Queue.c main.c $(CFLAGS) -o que.out

run:
	./que.out

valgrind_run:
	valgrind -s ./que.out

clear:
	rm -rf *.out