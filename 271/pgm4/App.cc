#include <stdlib.h>
#include <time.h>
#include <math.h>
/**
 * This is the new class Hdata which allows me to use a primitive type as a 
 * 'key'ed class. So i can use the HashTb objects to hold longs.
 * @author David Haltinner
 * @date Nov 14, 2002
 * */
class Hdata
{
   public:
      long data;
      long key() { return data; }
      Hdata & operator =(const Hdata & temp)
      {
         data=temp.data;
      }
      bool operator !=(const Hdata & temp)
      {
         return (data != temp.data);
      }   
      friend ostream & operator<<(ostream & out, const Hdata & temp)
      {
         out<<temp.data;
         return out;
      }
};
/**
 * This is the main function that creates random numbers and stores them into 
 * two different types of Hash tables (Double Hashing, and Seperate Chaining). 
 * It then outputs the time to find the elemtents under different load factors.
 * I also labeled each section with the assignment #'s to follow easier.
 * @return 0 no matter what. Unless it seg faults!
 * */
int main()
{
   const int N=1021;
   const int B=101;
   HashTb<Hdata,long> * Table;
   HashDouble<Hdata,long> DoubleTable(N);
   HashChain<Hdata,long> ChainTable(B);
   for (int i=0; i<2; i++)
   {
      //WHICH TABLE TYPE THIS TIME?	  
      if (i>0) 
      {
         Table=&DoubleTable;
         cout<<"\n\n******Double Hashing with B="<<N<<"******"<<endl;
      }
      else 
      {
         Table=&ChainTable;
         cout<<"\n******Seperate Chaining with B="<<B<<"******"<<endl;
      }
      long pkey, skey[N];
      //NUMBER 1
      srand48((long) time(NULL));
      //NUMBER 2
      for (int i = 0; i < N; i++)
         skey[i] = lrand48( ) % 1000000;
      //NUMBER 3
      for (double LF = 0.5; LF < 1; LF += 0.05)
      {
         //STEP 3 A   
         for (int i = 0; i < floor(LF * N); i++)
         {
            Hdata temp;
            temp.data=skey[i];
            Table->insert(temp);
         }
         //STEP 3 B
         Hdata  element;
         bool found;
         int last = int( floor(LF * N) ) - 1;
         double start_time = clock( );
         for (int c = 0; c < 100; c++) 
         {
            pkey = skey[last - c];
            for (int spin = 1; spin <= 1000; spin++)
               found = Table->search(pkey, element);
            if (! found )
               cout << "Error, not found: " << pkey << endl;   
         }
         double end_time = clock( );
         //STEP 3 C
         cout << "Successful search load factor: " << LF << " clocks: " 
              << (end_time - start_time) << endl;
         //STEP 3 D
         for (int i = 0; i < int(.5 * floor(LF * N)); i++)
            Table->erase(skey[i]);      
         //STEP 3 E
         start_time = clock( );
         for (int c = 0; c < 100; c++) 
         {
            pkey = skey[last - c];
            for (int spin = 1; spin <= 1000; spin++)
               found = Table->search(pkey, element);
            if (! found )
               cout << "Error, not found: " << pkey << endl;
         }
         end_time = clock( );
         //STEP 3 F
         cout << "After deletion, successful search load factor: " << LF 
              << " clocks: " << (end_time - start_time) << endl;
         //STEP 3 G
         for (int i = 0; i < int(.5 * floor(LF * N)); i++)
            Table->erase(skey[i+(N/2)]);      
      }
   }
   return 0;
}
