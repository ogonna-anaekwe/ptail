
CC=gcc
FLAGS=-Wall -Werror

all: ptail

clean:
	rm -rf ptail *.o

ptail: main.c ptail.h
	$(CC) -o ptail main.c ptail.c $(FLAGS)