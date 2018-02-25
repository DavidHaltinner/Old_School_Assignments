

# makefile for the compilation and linking of the programs  
CC = cc
CFLAGS = -g
LIBS = /lib/libpthread.so.0

all :  simple simple_threads simple_processes simple_mutex 

simple : simple.o
	${CC} ${CFLAGS}   simple.o -o simple
 
simple_threads : simple_threads.o
	${CC} ${CFLAGS} simple_threads.o ${LIBS} -o \
	simple_threads

simple_processes : simple_processes.o
	${CC} ${CFLAGS} simple_processes.o  -o \
	simple_processes

simple_mutex : simple_mutex.o
	${CC} ${CFLAGS}${THREAD_CFLAGS} \
	simple_mutex.o ${LIBS} -o simple_mutex

clean :
	rm -f *.o *~ *# core  a.out\
	simple simple_threads simple_processes\ 
	simple_mutex

