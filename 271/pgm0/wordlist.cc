/**
* This is the functions of wordlist.h. It has the code of Find (which i wrote), 
* Front, GetData, InsertAfter, IsEmpty, Last, and Next.
* @authors: Peter Worland, David Haltinner
* @date Sep. 20 2002
* */
#include <string.h>
#include "wordlist.h"

/**
* This function takes in a character array and then scans through itself (linked 
* list) to look for a matching word. If it is found it returns true, else false.
* @params: w, which is the character string to match
* @return: true if found, false otherwsie
* */
bool WordList::Find (char * w)
{
   Node * backup = new Node;
   backup = current;
   Front();
   while (!IsEmpty() && !Last())
   {
      if (strcmp(GetData(),w) == 0)
      {
	current = backup;
        return true;
      }
      Next();
   }
   current = backup;
   return false;
}
/**
* This function places the current pointer to point to the first node in the 
* linked list.
* */   
void WordList::Front ( )
{
   current = list;
}
/**
* This function returns a pointer to the 'word' object that is in the linked list
* @return a pointer to the word
* */
char * WordList::GetData ( )
{
   return current -> word;
}
/**
* This function inserts a given character array into the linked list, after the 
* node where the current pointer is pointing
* @params: w, which is the charcater array to add in
* */
void WordList::InsertAfter (char * w)
{
   Node * tmp = new Node;
   strcpy (tmp -> word, w);
   tmp -> next = current -> next;
   current -> next = tmp;
}
/**
* This function checks to see if the linked list is empty by seeing if there is no node after the header. True if it has no other nodes, false otherwise.
* @return true if empty, false otherwise
* */
bool WordList::IsEmpty ( ) const
{
   return (list -> next == 0);
}
/**
* This function checks to see if the current node is the last one in the linked 
* list. If it is it returns true, otherwise false.
* @return truw if its the last node, false otherwise.
* */
bool WordList::Last ( ) const
{
   return (current -> next == 0);
}
/**
* This function moves the current pointer to the next node.
* */
void WordList::Next ( )
{
   current = current -> next;
}
