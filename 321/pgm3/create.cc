// create.cc

/*
 *  Description
 *  create an empty indexed-sequential file
 *  files btree.bin and bfile.bin are created
 *
 *  usage
 *  % create
 *
 *  Input
 *  none
 *
 *  Written by
 *  Gordie Howe and Wayne Gretzky
 */


#include <iostream>

#include "btree.h"
using namespace std;


int main()
{
  btreeType bt("create", "btree.bin", "bfile.bin" );

  cout<<endl;
  bt.printIndexFilePage0(); cout<<endl;
  bt.printDataFilePage0() ; cout<<endl;

  return 0;
}
