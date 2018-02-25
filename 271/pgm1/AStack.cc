/**
 * This file holds the functions defined in AStack.h. It manipulates an array 
 * as a Stack, popping data off, returning the top, checking to see if its 
 * empty, pushing data on the stack, and adding to the capacity when needed. 
 * It holds data of type T.
 * @authors Peter Worland, and David Haltinner
 * @date OCt 4 2002
 * */

#include "AStack.h"
/**
 * This function checks to see if the stack is empty by looking where the top 
 * of the stack is.
 * @return true if it is empty, false if its not
 * */
template <class T>
bool AStack<T>::IsEmpty( ) const { return top == 0; }
/**
 * This function returns the top piece of data, and then decreases the top of 
 * it, to sort of delete it (get written over).
 * @return T; which is the data in the slot we are removing
 * */
template <class T>
T AStack<T>::Pop( )
{
   if( IsEmpty( ) )
      Error( "The stack is empty." );
   else
      return data[top--];
}
/**
 * This function returns the top value, but does not delete it.
 * @return T; the top piece of data
 * */
template <class T>
T AStack<T>::Top( ) const
{
   if( IsEmpty( ) )
      Error( "The stack is empty." );
   else
      return data[top];
}
/**
 * This function adds another piece of data to the top of the array/stack. It 
 * will see if the stack is full first. If it is it will call the AddCapacity 
 * function to increase it.
 * @params item; the data to add to the stack
 * */
template <class T>
void AStack<T>::Push( const T & item )
{
   if (top == capacity-1) 
      AddCapacity(capacity + 4);  
   data[++top] = item;
}
/**
 * This function increases the capacity of a stack by making a newer/larger 
 * one, and copying the data over to it. Then deleteing the old one.
 * @params num; by how much should we increase it.
 * */
template <class T>
void AStack<T>::AddCapacity( int num ) 
{
   T * tempdata = new T[capacity+num];
   for (int i=0; i<capacity; i++)
      tempdata[i] = data[i];
   capacity += num;
   delete [ ] data;
   data = tempdata;
}
