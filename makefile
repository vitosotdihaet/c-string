CC = gcc

CFLAGS  = -g -Wall

# the build target executable:

a:
	$(CC) $(CFLAGS) -o main main.c string.c
	./main
