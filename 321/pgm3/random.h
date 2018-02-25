// random.h

#ifndef RANDOM_H_
#define RANDOM_H_


//class Random provides a source of random integers in the range 0..65535

//this is a "really" crummy random number generator
//it is only usable for this assignment and for no other purpose

class Random {

   private:
	    int seed;

   public:

	Random() : seed(17811) {}          //constructor with default seed
	Random( int Seed ) {seed=Seed;}    //constructor with seed = argument

	int  intVal()                      //return a random integer value
	{
	  seed = (25173*seed + 13849) % 65536;
          return seed;
	}

	void setSeed( int Seed ) { seed = Seed; }   //set the seed
	void resetSeed()         { seed = 17811; }  //reset the seed to the default
};

#endif
