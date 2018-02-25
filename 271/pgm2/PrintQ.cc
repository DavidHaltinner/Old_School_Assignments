#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include "LList.h"
/**
 * This class Data holds a fake print job. It has private members that hold
 * a job number, the name of the file, the size of the job, and the priority
 * of the job. It also overloads the != operator for LLists's find to work,
 * and has a constructor and destructor.
 * @author David Haltinner
 * @date 10-16-02
 * */
class Data
{
   public:
      char * file;
      int job;
      char priority;
      long size;
      // The empty constructor for Data
      Data() {};
      // The destructor for Data
      ~Data() {}
      /**
       * This overloads the != operator, comapring the job numbers.
       * @params temp, which is another Data object to compare with
       * @return true if they arent the same, false if they are.
       * */
      bool operator !=(Data temp) { return !(job == temp.job); }
};
/**
 * This class holds the PrintQueue. It is basically two Linked List Queues, 
 * that hold Data objects. It has members functions that add new Datas to
 * the queues (sorted in one queue), one that removes a specified Data object,
 * one that swaps a specified Data with its predecesor, and a function that 
 * 'prints' the Data object (cout'ing the job number and filename.
 * @author David Haltinner
 * @date 10-16-02
 * */
class PrintQueue
{
   private:
      LList<Data> * HiQueue;
      LList<Data> * LoQueue;
   public:
      // The constructor: allocates memory for two LLists
      PrintQueue()
      {
         HiQueue = new LList<Data>;
         LoQueue = new LList<Data>;
      };
      // The destructor, deletes the two LLists
      ~PrintQueue(){ delete HiQueue; delete LoQueue; };
      /**
       * This function takes in a job number and looks for it in the two 
       * queues (High first) and the removes it once it is found.
       * @params in, the input stream to grab the job number from
       * */
      void Kill(ifstream & in)
      {
         Data * d=new Data;
         in>>d->job; //Only job number needs to be equal between Datas
         if (HiQueue->find(*(d)))
            HiQueue->extractPosition();
         else if (LoQueue->find(*(d)))
            LoQueue->extractPosition();        
      };
      /**
       * This function takes the first Data object out of the HiQueue (if 
       * it's empty, then it takes the first one out of the LoQueue) and 
       * 'prints' it; displays the job number and filename onto the screen.
       * */
      void Print()
      {
         if (!HiQueue->isEmpty())
         {
            HiQueue->first();
            Data d=(HiQueue->getData());
            cout<<"Job number "<<d.job<<" for file "<<d.file
                <<" is now printing"<<endl;
            HiQueue->extractPosition();
         } else if (!LoQueue->isEmpty())
         {
            LoQueue->first();
            Data d=(LoQueue->getData());
            cout<<"Job number "<<d.job<<" for file "<<d.file
                <<" is now printing"<<endl;
            LoQueue->extractPosition();
         }   
      };
      /**
       * This function creates a new Data object and puts it into the 
       * corresponding LList. If it goes into the High queue it will sort it 
       * by size, ascending.
       * @params in, which is the input stream to grab the data from
       * */
      void Request(ifstream & in)
      {
         Data * d=new Data;
         in>>d->job;
         in>>d->priority;
         in>>d->size;
         char temp[50];
	 in>>temp;
	 d->file=new char[strlen(temp)];
	 strcpy(d->file, temp);
         if (d->priority == 'L') LoQueue->append(*(d));
         else
         {	 
	    HiQueue->first();
            while (!HiQueue->end() && HiQueue->getData().size <= d->size)
               HiQueue->next(); //I could have also overloaded <=
            if (HiQueue->end()) HiQueue->append(*(d));
            else 
	    {
		    HiQueue->previous();
		    HiQueue->insert(*(d));
	    }
         }
      };
      /**
       * This function finds a specified print job, and swaps it with the job 
       * infront of it in the queue. We only needed to write this for the 
       * LoQueue you said in class. The HiQueue would just be a copy and paste 
       * of the LoQueue if it wasnt sorted.
       * @params in, which is the input stream to grab the job number from
       * */
      void Swap(ifstream & in)
      {
         Data * d=new Data;
         in>>d->job; //Only job number needs to be equal between Datas
         if (LoQueue->find(*(d))) //told us LoQueue only!
         {   //Dont have access to Nodes! So brut-force it!
            Data * temp=&(LoQueue->getData());
            d->size=temp->size;
            d->priority=temp->priority;
            d->file=new char[strlen(temp->file)];
            strcpy(d->file, temp->file);
            LoQueue->previous();
            LoQueue->previous();
            LoQueue->insert(*(d));
            for (int i=0; i<3; i++)
            LoQueue->next();
            LoQueue->extractPosition();
         }
      };
};
/**
 * This is the main function of the application. It takes in a parameter when 
 * called; the file to get the input from. It makes a new PrintQueue, then It 
 * grabs the first character of every line in the file and calls the 
 * corresponding function of PrintQueue.
 * @param argc (number of arguments), and argv which points to an array 
 *    holding the arguments.
 * @return 1 if the file cant be opened, 0 otherwise.
 * */
int main (int argc, char * argv[])
{   
   if (argc !=2)
   {
      cout<<"Please give one file as an argument"<<endl;
      return 0;
   }
   ifstream in;
   in.open(argv[1]);
   if (!in) 
   {
      cout<<"Open failed on the file you gave me"<<endl;
      return 1;
   } 
   PrintQueue PrintStuff;
   char input;
   while (in>>input)
   {
      if (input == 'R') PrintStuff.Request(in);
      else if (input == 'K') PrintStuff.Kill(in);
      else if (input == 'P') PrintStuff.Print();
      else if (input == 'S') PrintStuff.Swap(in);
   }
   return 0;
}      
