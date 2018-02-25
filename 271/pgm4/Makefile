pgm4: template.o
	g++ -o pgm4 template.o
template.o: template.cc LList.cc LList.h App.cc Chain.cc Chain.h HashTb.h Double.h Double.cc
	g++ -g -c template.cc
clean:
	rm -rf *.o
	rm -rf core
	rm -rf pgm4
