# Makefile for Buffer Pool Assignment

CC     = g++
CFLAGS = -Wall -g
OBJ    = main.o pool.o showHex.obj

bman:  $(OBJ)
	$(CC) $(OBJ) -o bman
main.o: main.cc
	$(CC) -c $(CFLAGS)  main.cc
pool.o: pool.cc
	$(CC) -c $(CFLAGS)  pool.cc
clean:
	/bin/rm -f *.o
erase:
	/bin/rm -f *.o bman After*.bin
