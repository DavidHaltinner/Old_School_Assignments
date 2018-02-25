pgm6: template.o pgm6.o
	g++ -o pgm6 template.o pgm6.o
pgm6.o: pgm6.cc
	g++ -g -c pgm6.cc
template.o: template.cc LList.cc LList.h Big.cc
	g++ -g -c template.cc
clean:
	rm -rf *.o
	rm -rf core
	rm -rf pgm6
