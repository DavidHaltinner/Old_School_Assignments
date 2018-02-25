// random.cc

#include <iostream>
#include "random.h"
using namespace std;
// ======================================
//		Random
// ======================================
// constructor

Random::Random()
{
  seed = 888777;
}

// ======================================
//		Random
// ======================================
// constructor

Random::Random( int Seed )
{
  if (Seed<1 || Seed==2147483647) {
    cerr<<"Random::Random: invalid seed "<<Seed<<endl;
    cerr<<"                seed set to 1"<<endl;
    seed = 1;
    return;
  }

  seed = Seed;
}

// ======================================
//		IntVal
// ======================================
// return a random integer value in the
// range 1 <= IntVal <= 2147483646

int Random::intVal ()
{
  const int M = 2147483647;
  const int A =      16807;
  const int Q =     127773;
  const int R =       2836;

  int low, high, test;

  high = seed / Q;
  low  = seed % Q;
  test = A*low - R*high;
  if (test>0) seed = test; else seed = test+M;

  return seed;
}

// ======================================
//		setSeed
// ======================================
// set(reset) the random number seed

void Random::setSeed( int Seed )
{
  seed = Seed;
}
