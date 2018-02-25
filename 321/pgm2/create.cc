// create.cc

/*
 *  Description
 *  create an empty hash file
 *  
 *  usage
 *  % create
 *  
 *  Input
 *  none
 *  
 *  Written by
 *  a. perrie  sep 1998
 */


#include <iostream>
#include <iomanip>
#include "typedefs.h"
#include "hash.h"
using namespace std;


int main()
{
  cerr << "create: formatting hash file\n";
  cerr << "bucket size: " << sizeof(bucketType) << endl;
  cerr << "node   size: " << sizeof(nodeType)   << endl;

  //this constructor will format an empty hash file
  HashFile hf( "format", "primary.bin", "overflow.bin" );

  cerr << "create: formatting completed"<<endl;
  return 0;
}
