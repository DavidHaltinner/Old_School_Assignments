pgm5: pgm5.o Graph.o Edge.o
	g++ -o pgm5 pgm5.o Graph.o Edge.o
pgm5.o: pgm5.cc
	g++ -g -c pgm5.cc
Graph.o: Graph.cc
	g++ -g -c Graph.cc
Edge.o: Edge.cc
	g++ -g -c Edge.cc
clean:
	rm -rf *.o
	rm -rf core
	rm -rf pgm5
