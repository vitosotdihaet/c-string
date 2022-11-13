CC = gcc

CFLAGS  = -g -Wall

# the build target executable:

a:
	$(CC) $(CFLAGS) -o main.out main.c string.c
	./main.out
