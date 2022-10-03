CC=gcc
CFLAGS=-I.

all: main.o caltrain.o
	$(CC) -o main main.o caltrain.o