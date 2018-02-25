#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream.h>
#include "LList.h"
#include "Big.cc"
/**
 * This function takes in a linked list and determines if it is sorted, by 
 * having a pointer at the prevous node's data, and comparing it with the 
 * current node's. It then returns true or false.
 * @param myList, which is the Linked List to check
 * @return true if it is sorted, false if it is not
 * */
bool isSorted(LList<Big> & myList) {
   myList.first();
   Big * temp=&myList.getData();
   myList.next();
   while (!myList.end()) {
      if (temp->key > myList.getData().key)
	 return false;
	 temp=&myList.getData();
	 myList.next();
   }
   return true;
}
/**
 * This is the main function that does the sorting. It generates 8 digit random
 * numbers, and places them into a list. It then goes through digit by digit, 
 * and places the node into the specific 'bin' (list). It then concatenates 
 * them all back into the beginning list.
 * @return 0 is we complete successfully
 * */
int main() {
   for (int n=4000; n<=64000; n=n*2) {
      srand48((long) time(NULL));
      LList<Big> totalList;
      LList<Big> bins[10];
      double startTime=clock();
      for (int i = 0; i < n; i++)
	 totalList.append(*new Big(lrand48( ) % 10000000));
      for (int i=1; i<=10000000; i=i*10)  {
	 while(!totalList.isEmpty()) {
	    totalList.first();
	    int slot=(totalList.getData().key/(i))%10;
	    bins[slot].appendFromList(totalList);
	 }		
	 for (int k=0; k<10; k++)
	    totalList.concat(bins[k]);
      }
      double stopTime=clock();
      double totalTime=stopTime-startTime;
      cout<<"Total time to Radix Sort "<<n<<" elements was "<<totalTime
	 <<"."<<endl<<"This time divided by n lg(n) is "
	 <<totalTime/(n*(log(n)/log(2)))<<"."<<endl;
      cout<<"The list has size "<<totalList.size()<<" and it ";
      if (isSorted(totalList)) cout<<"is sorted."<<endl<<endl;
      else cout<<"is not sorted."<<endl<<endl;
   }
   return 0;
}
