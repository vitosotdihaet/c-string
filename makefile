CC = gcc

CFLAGS = -Wall -Wextra

main: string.h
	$(CC) $(CFLAGS) -o main.out main.c