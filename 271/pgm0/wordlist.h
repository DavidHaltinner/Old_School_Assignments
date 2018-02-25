/**
* This class creates two new objects, a Node and a WordList which is a 
* linkedlist of nodes. 
* @author Peter Worland, documentation by David Haltinner.
* @date Sep. 20, 2002
* */

/**
* This struct is for a new object Node, which holds a charatcer array, 
* and a pointer to another node; 
* */
struct Node {
   char word[20];
   Node * next;
};
/**
* This its Word List, which is a Linked List of Nodes. It has function 
* definitions for Find, Front, GetData, InsertAfter, IsEmpty, Last, and 
* Next. It also has two pointers to point to the front of the list, and 
* a pointer to point to the the Node we are working on.
* */
class WordList {
public:
   WordList ( )
      { list = new Node; list -> next = 0; current = list; }
   bool Find (char * w);
   void Front ( );
   char * GetData ( );
   void InsertAfter (char * w);
   bool IsEmpty ( ) const;
   bool Last ( ) const;
   void Next ( );
private:
   Node * list, * current;
};
