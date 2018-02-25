pgm0: wordlist.o pgm0.o
	g++ -g -o pgm0 wordlist.o pgm0.o
wordlist.o: wordlist.cc wordlist.h
	g++ -g -c wordlist.cc
pgm0.o:
	g++ -g -c pgm0.cc
clean:
	rm -f *.o
	rm -f pgm0
	rm -f core