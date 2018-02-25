pgm1: pgm1.o template.o
	g++ -o pgm1 pgm1.o template.o
pgm1.o: pgm1.cc AStack.h
	g++ -g -c pgm1.cc
template.o: template.cc AStack.cc AStack.h
	g++ -g -c template.cc
clean:
	rm -rf *.o
	rm -rf core
	rm -rf pgm1
