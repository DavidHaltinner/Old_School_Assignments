# Makefile for program 1

CC     = g++
CFLAGS = -Wall -g


all: create update report

create: create.cc
	$(CC) $(CFLAGS) create.cc     -o create
update: update.cc
	$(CC) $(CFLAGS) update.cc     -o update
report: report.cc
	$(CC) $(CFLAGS) report.cc     -o report

run: create update report
	./create old.bin tran.txt
	./update old.bin tran.txt
	./report old.bin >old.txt
	./report new.bin >new.txt

clean:
	/bin/rm -f *.bin *.txt create update report

