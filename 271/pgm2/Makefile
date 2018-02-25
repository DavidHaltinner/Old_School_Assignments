pgm2: template.o
	g++ -o pgm2 template.o
template.o: template.cc LList.cc LList.h PrintQ.cc
	g++ -g -c template.cc
clean:
	rm -rf *.o
	rm -rf core
	rm -rf pgm2
