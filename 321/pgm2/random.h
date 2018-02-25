// random.h

#ifndef RANDOM_H_
#define RANDOM_H_ 1


//class Random provides a source of random integers in the range 1..2147483646

class Random {

   private:
	    int seed;

   public:

	//a valid seed is a value in the range 1<=seed<=2147483646

	Random();            //constructor with default seed
	Random( int Seed );  //constructor with seed specified via the argument

	int  intVal();            //return a random integer value
	void setSeed( int Seed ); //set(reset) the seed
};

#endif
