// create.cc

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct InventoryRecord {
   int  primaryKey;
   int  onHand;
};


int main()
{
  ofstream masterFile;

  InventoryRecord  record;

  masterFile.open( "old.bin" );
  if(masterFile.fail()){cerr<<"\ncreate: could not open old.bin\n\n";return 1;}

  for (int i=1; i<=10; i++) {
     record.primaryKey = i  ;
     record.onHand     = i*5;
     masterFile.write( (char *)&record, sizeof(record) );
  }

  masterFile.close();

  ofstream transFile;
  transFile.open( "tran.txt" );
  if(transFile.fail()){cerr<<"\ncreate: could not open tran.t\n\n";return 1;}

  transFile << 3 << "  " <<  3 <<endl;
  transFile << 3 << "  " <<  3 <<endl;
  transFile << 3 << "  " <<  3 <<endl;
  transFile << 9 << "  " << 15 <<endl;
  transFile << 9 << "  " << 15 <<endl;
  transFile << 9 << "  " << 15 <<endl;
  transFile.close();

  return 0;
}
