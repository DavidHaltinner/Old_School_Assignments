// typedefs.h

#ifndef TYPEDEFS_H
#define TYPEDEFS_H 1

const int NUMBEROFSLOTS   =   5;
const int NUMBEROFBUCKETS = 119;

const int NIL       = 0;
const int EMPTYKEY  = 0;  // valid primary key is >= 1
const int FREESPACE = 0;  // cell0 of OverflowFile

struct slotType {
	int  key    ;  // primary key
	char junk[4];  // logical record information
};

struct bucketType {
	slotType slot[NUMBEROFSLOTS];
	int      fill               ;  // trick: make od readable
	int      next               ;
};

struct nodeType {
	union variant {
	    struct Cell0 { int high; } cell0;
	    slotType                   data ;
	}
	    var ;
	int fill;  // trick: make od readable
	int next;
};

#endif
