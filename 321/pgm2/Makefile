# Makefile for Hashfile w/ Chaining

CC     = g++
CFLAGS = -Wall -g


all: create insert delete print

create: create.o hash.o
	$(CC) create.o hash.o           -o create
create.o: create.cc typedefs.h hash.h
	$(CC) -c $(CFLAGS) create.cc

insert: insert.o hash.o random.o
	$(CC) insert.o hash.o random.o  -o insert
insert.o: insert.cc typedefs.h hash.h random.h
	$(CC) -c $(CFLAGS) insert.cc

delete: delete.o hash.o random.o
	$(CC) delete.o hash.o random.o  -o delete
delete.o: delete.cc typedefs.h hash.h random.h
	$(CC) -c $(CFLAGS) delete.cc

print: print.o hash.o
	$(CC) print.o  hash.o           -o print
print.o: print.cc hash.h typedefs.h
	$(CC) -c $(CFLAGS) print.cc

hash.o: hash.cc hash.h typedefs.h
	$(CC) -c $(CFLAGS) hash.cc
random.o: random.cc random.h
	$(CC) -c $(CFLAGS) random.cc

clean:
	/bin/rm -f *.bin  *.o
erase:
	/bin/rm -f create insert delete print *.bin *.o
