CC = gcc

CFLAGS = -Wall -Wextra

a: string.o
	$(CC) $(CFLAGS) -o main.out main.c string.o

string:
	$(CC) $(CFLAGS) -c string.c