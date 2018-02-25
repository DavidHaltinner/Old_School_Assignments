/**
* This is an application that takes two files as input, reads the words out of 
* the files, placing those words into seperate linked lists. It then combines 
* those two linked lists into one, and outputs all three of the lists. It has 
* methods that cleanup words, print words to the screen, builds a linked list 
* out of a given file, and a function that turns two lists into one.
* @author David Haltinner
* @date Sep. 20, 2002
* */
#include <iostream.h>
#include <ctype.h>
#include <fstream.h>
#include <string.h>
#include "wordlist.h"

/**
* This function takes in a character array that is a word. It then takes this 
* word and makes it entirely lowercase, removes punctuation, and removes any 
* 's'es at the end of the word, if the word is more then 4 letters long.
* @params: w, which is the charatacter array holding the word
* */
void cleanup (char * w)
{
   int i;
   for (i=0; i<strlen(w); i++)
   {
      if (!isalnum(w[i])) w[i] = '\0';
      w[i] = tolower(w[i]);
   }
   if (strlen(w)>4 && (w[strlen(w)-1] == 's'))
	  w[strlen(w)-1] = '\0';
}
/**
* This function takes in a linked word list, and print's its contents to cout.
* @params: wlist, which is the linked list holding words
* */
void printList (WordList & wlist)
{
   wlist.Front();
   bool done = false;
   do
   {  
      cout<<wlist.GetData()<<endl;
      if (wlist.Last()) done=true;
      if (!done) wlist.Next();
   } while (!done);
}
/**
* This function takes in three linked lists, which are two full word lists, and 
* one empty one. It then copies the data from the two full lists, and mixes them
*  together into the empty list.
* @params: allwords (empty list), list1 and list2 (the full lists)
* */
void intersect (WordList & allwords, WordList & list1, WordList & list2)
{
   list1.Front();
   list2.Front();
   bool onedone = false;
   bool twodone = false;
   do
   {
      if (!onedone && !allwords.Find(list1.GetData()) && (strlen(list1.GetData())!=0))
         allwords.InsertAfter(list1.GetData());
      if (!twodone && !allwords.Find(list2.GetData()) && (strlen(list2.GetData())!=0))
         allwords.InsertAfter(list2.GetData());
      if (list1.Last()) onedone=true;
      if (list2.Last()) twodone=true;
      if (!onedone) list1.Next();
      if (!twodone) list2.Next();
   } while(!onedone || !twodone);	   
}
/**
* This function takes in an empty linked word list and a file input stream. It 
* then inputs words from the file, and places them into the linked word list.
* @params: words (the empty linked list), win (the input stream)
* */
void buildList (WordList & words, ifstream & win)
{ 
   char temp[25];	
   while(win.getline(temp, 25, ' '))
   {
      cleanup(temp);
      if ((strlen(temp) != 0) && (!words.Find(temp)))
         words.InsertAfter(temp); 
   }   
   win.close();
}
/**
* This is the main function, which takes in two file names as parameters. It
* then opens the two files, and calls on buildlist to turn those file's data
* into linked lists of words. It then calls on to printlist to have the words
* displayed.
* @params: argc (number of arguments), argv[] (the arguments from the user)
* */
int main(int argc, char *argv[])
{
   if (argc != 3)
   {
      cout<<"You need two files as arguments"<<endl;
      return 0;
   }
   WordList wordlistone;
   WordList wordlisttwo; 
   ifstream one;
   one.open(argv[1]);
   if (!one) {
      cout<<"open failed on file one"<<endl;
      return 1;
   }
   buildList(wordlistone, one);
   ifstream two;
   two.open(argv[2]);
   if (!two) {
      cout<<"open failed on file two"<<endl;
      return 1;
   }
   buildList(wordlisttwo, two);
   WordList combined;
   intersect(combined, wordlistone, wordlisttwo);
   cout<<"Combined List:"<<endl;
   printList(combined);
   cout<<"\nList one:"<<endl;
   printList(wordlistone);
   cout<<"\nList two:"<<endl;
   printList(wordlisttwo);
   return 0;
}
