CC = gcc

CFLAGS  = -g -Wall -Wextra

a:
	$(CC) $(CFLAGS) -o main.out main.c string.c
	./main.out
