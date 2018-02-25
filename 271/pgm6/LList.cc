//
// File : LList.cc     LList<T> template class member functions 
//

#include <iostream.h>
#include <string.h>
#include "LList.h"
template <class T>
LList<T>::LList( )
{ 
   head = new Node<T>; 
   head -> next = head; 
   cur = head; 
   tail=head; //last node is the head!
}
template <class T>
LList<T>::~LList( )
{
   purge( );
   if (head) delete head;
   head=tail=cur=0; //Set everything to null
}

template <class T>
void LList<T>::purge( )
{
   Node<T> * p, * q;
   p = head -> next;
   while(p != head) {
      q = p;
      p = p -> next;
      delete q;
   }
   head -> next = head;             //  repair empty list
}

template <class T>
LList<T>::LList(const LList<T> & list) : head (new Node<T>)
{
   Node<T> * p;
   head -> next = head;
   cur = head;
   for (p = list.head -> next; p != list.head; p = p -> next) {
   	insert(*(p -> data));
    	cur = cur -> next;
   }
   tail=cur;
}

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs)
{
   Node<T> * p;
   if(this != &rhs) {
      head = new Node<T>;
      head -> next = head;
      cur = head;
      for (p = rhs.head -> next; p != rhs.head; p = p -> next) {
	 insert(*(p -> data));
         cur = cur -> next;
      }
   }
   return *this;
}

template <class T>
void LList<T>::previous( )
{
   Node<T> * tmp = head;
   if (head -> next == head) 
      cur = head;
   else {
      while (tmp -> next != cur) 
	 tmp = tmp -> next;
	 cur = tmp;
   }
}

template <class T>
bool LList<T>::end ( ) const
{
   return (head == cur);
}

template <class T>
void LList<T>::extractPosition( )
{
   Node<T> * temp;
   if (cur == head) return;
   temp = cur;
   previous( );
   cur -> next = temp -> next;
   if (tail==temp) tail=cur->next; //In case we remove the last Node
   delete temp;
}

template <class T>
bool LList<T>::find ( const T & x )
{
   cur = head -> next;
   while ( (cur != head) && (*(cur -> data) != x) )
      cur = cur -> next; 
   if ( cur == head ) return false; else return true;
}
 
template <class T>
void LList<T>::first( ) 
{
   cur = head -> next;
}

template <class T>
void LList<T>::front( )
{
   cur = head;
}

template <class T>
T& LList<T>::getData( ) const
{
   return *(cur -> data);
}

template <class T>
void LList<T>::insert(const T & x)
{
   Node<T> * tmp = new Node<T>;
   if(!tmp) {
      cout << "Out of memory" << endl;
      exit(1);
   }
   tmp -> data = new T(x);
   tmp -> next = cur -> next;
   cur -> next = tmp;
}

template <class T>
bool LList<T>::isEmpty( ) const
{
   return (head -> next == head);
}

template <class T>
void LList<T>::last( )
{
   cur = tail; //already have a pointer to the last node, so cur should be tail
}

template <class T>
void LList<T>::next( )
{
   cur = cur -> next;
}

template <class T>
int LList<T>::size ( ) const
{
   int count = 0;
   Node<T> * tmp = head -> next;
   while (tmp != head) {
      count++;
      tmp = tmp -> next;
   }
   return count;
}

template <class T>
void LList<T>::setData ( const T & x )
{
   *(cur -> data) = x;
}

template <class T>
void LList<T>::append (const T & x)
{
   last( );
   insert(x);
   tail=tail->next; //Tail needs to be moved one to the new end.
}

/**
 * This is the new function that takes the first node out of the given list, 
 * and adds it to the end of this list. It does this by moving pointers around 
 * only.
 * @param B, which is the list to take the node from
 * */
template <class T>
void LList<T>::appendFromList(LList<T> & B)
{
   if (B.isEmpty()) return;
   Node<T> * temp=B.head->next;
   B.cur=temp->next;
   B.head->next=B.cur;
   tail->next=temp;
   temp->next=head;
   tail=temp;
   if (B.size()==0) B.cur=B.tail=B.head;
}
/**
 * This function takes all of the nodes out of the given list, and places them 
 * into the end of this list. It does this by changing the pointers in this 
 * list to point to the other list's first node, and then adjusting the tail 
 * pointers.
 * @param B, which is the list to take the nodes from.
 * */
template <class T>
void LList<T>::concat(LList<T> & B)
{
   if (B.isEmpty()) return;
   Node<T> * temp=B.head->next;
   B.cur=B.head;
   B.head->next=B.head;
   tail->next=temp;
   tail=B.tail;
   B.tail=B.head;
   tail->next=head;
}
