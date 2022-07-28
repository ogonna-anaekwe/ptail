
CC=gcc

all: ptail

clean:
	rm -rf ptail *.o

ptail: main.c ptail.*
	$(CC) -o ptail main.c ptail.c -Wall -Werror	