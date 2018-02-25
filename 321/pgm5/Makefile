# Makefile for program 5

CC     = g++
CFLAGS = -Wall -g


all: viewZip szip Szip

szip: szip.cc
	$(CC) $(CFLAGS) szip.cc     -o szip
Szip: Szip.cc
	$(CC) $(CFLAGS) Szip.cc	    -o Szip
viewZip: viewZip.cc
	$(CC) $(CFLAGS) viewZip.cc  -o viewZip

run_s: szip viewZip
	cat L.txt | ./szip | ./viewZip
run_S: Szip viewZip
	cat L.txt | ./Szip | ./viewZip
clean:
	/bin/rm -f szip viewZip Szip

listings: 
	enscript -2r report.t szip.cc Makefile
