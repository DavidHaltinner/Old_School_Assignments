# Makefile for B+tree Assignment

CC     = g++
CFLAGS = -Wall -g

default:
	-@echo "default disabled"

all:  create insert payroll

create: create.o btree.o disk.o
	$(CC) create.o btree.o disk.o   -o create
insert: insert.o btree.o disk.o
	$(CC) insert.o btree.o disk.o   -o insert
payroll: payroll.o btree.o disk.o
	$(CC) payroll.o btree.o disk.o -o payroll

create.o: create.cc   typedefs.h  btree.h
	$(CC) -c $(CFLAGS)  create.cc
insert.o: insert.cc   typedefs.h  btree.h
	$(CC) -c $(CFLAGS)  insert.cc
payroll.o: payroll.cc typedefs.h  btree.h
	$(CC) -c $(CFLAGS)  payroll.cc

btree.o: btree.cc     typedefs.h  btree.h
	$(CC) -c $(CFLAGS)  btree.cc
disk.o: disk.cc       typedefs.h  btree.h
	$(CC) -c $(CFLAGS)  disk.cc
bt.o: bt.cc           typedefs.h  btree.h
	$(CC) -c $(CFLAGS)  bt.cc

test: create insert payroll
	@echo "Program  3: Indexed Sequential File"  >tree.250
	@echo "Written by: David Haltinner"            >>tree.250
	@echo ""                >>tree.250
	./create
	./insert 250           >>tree.250
	./treeprint  btree.bin >>tree.250
	./payroll               >keys.250
	-diff tree.250 /home/perrie/321/public/Programs/pgm3/TREE.250
	-diff keys.250 /home/perrie/321/public/Programs/pgm3/KEYS.250

# =============================================================

# report.t is your "report" about the status of your assignment
# does your program work?  if not, what are the problems/errors
listings:
	enscript -2r report.t btree.cc disk.cc tree.250 keys.250


# Caution: do not delete treeprint or bt.obj or TREE.250 or KEYS.250
clean:
	/bin/rm -f *.bin tree*.250 keys*.250
	/bin/rm -f create.o insert.o payroll.o btree.o disk.o bt.o 
erase:
	/bin/rm -f *.bin tree*.250 keys*.250 create insert payroll
	/bin/rm -f create.o insert.o payroll.o btree.o disk.o bt.o
