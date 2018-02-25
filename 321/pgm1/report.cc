// report.cc

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct InventoryRecord {
   int  primaryKey;
   int  onHand;
};


int main( int argc, char **argv )
{
  if (argc!=2) {
    cerr << "\nusage: % report old.bin\n\n";
    return 1;
  }

  ifstream        fin;
  InventoryRecord record;

  fin.open( argv[1] );
  if(fin.fail()){
    cerr<<"\nreport: could not open " <<argv[1] <<"\n\n";
    return 1;
  }

  cout << "key  onHand" << endl;
  fin.read( (char *)&record, sizeof(record) );

  while ( !fin.eof() ) {
     cout << setw(3)<<record.primaryKey << " "
          << setw(7)<<record.onHand     << endl;
     fin.read( (char *)&record, sizeof(record) );
  }

  fin.close();
  return 0;
}
