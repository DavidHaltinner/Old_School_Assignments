//
// File : BST4.cc  
//

#include "BST4.h"

template <class E, class K>
bool BST<E, K>::search ( const K & k, E & e) const
{// Search for element that matches k.
BNode<E> * p = root;

while (p)  // examine p -> data
   if (k < p -> data.key( )) p = p -> leftChild;
   else if (k > p -> data.key( )) p = p -> rightChild;
   else {// found element
         e = p -> data;
         return true; }
   return false;
}

template <class E, class K>
BST<E, K> & BST<E, K>::insert ( const E & e )
{// Insert e if not duplcate
BNode<E> * p = root,                // search pointer
         * pp = 0;                  // parent of p

// Find place to insert
while (p) {// examine p -> data
   pp = p;
   // move p to a child
   if (e.key( ) < p -> data.key( )) p = p -> leftChild;
   else if (e.key( ) > p -> data.key( )) p = p -> rightChild;
   else error("Duplicate entry.");  // duplicate
   }

// Get a node for e and attach it to pp
BNode<E> * r = new BNode<E>(e);
if (root) {// tree is not empty
   if (e.key( ) < pp -> data.key( )) pp -> leftChild = r;
   else pp -> rightChild = r; }
else // insertion into empty tree
   root = r;

return *this;
}

template <class E, class K>
BST<E, K> & BST<E, K>::erase(const K & k, E & e)
{// Delete element with key k and put it in e.
 // set p to point to node with key  k
BNode<E> * p = root,                       // search pointer
         * pp = 0;                         // parent of p

while ( p && p -> data.key( ) != k ) {// move to a child of p
   pp = p;
   if ( k < p -> data.key( )) p = p -> leftChild;
   else p = p -> rightChild;
   }

if (!p) error("No element with this key.");
e = p -> data;  // save element to delete

// restructure the tree
// case: p has two children
if (p -> leftChild && p -> rightChild) {// two children
   // find largest element in left subtree of p
   BNode<E> * s = p -> leftChild,
            * ps = p;
   while (s -> rightChild) {// move to larger element
      ps = s;
      s = s -> rightChild;
      }
   // move largest from s to p
   p -> data = s -> data;
   p = s;
   pp = ps;
}

// p has at most one child
// save child pointer in c
BNode<E> * c;
if (p -> leftChild) c = p -> leftChild;
else c = p -> rightChild;
// delete p
if (p == root) root = c;
else {// is p left or right child of pp?
   if ( p == pp -> leftChild)
      pp -> leftChild = c;
   else pp -> rightChild = c;
   }
delete p;
return *this;
}

template <class E, class K>
bool BST<E, K>::maximum (E & e)
{
BNode<E> * p = root;

if(!p) return false;
else {
   while (p -> rightChild)
      p = p -> rightChild;
   e = p -> data;
   return true;
   }
}

template <class E, class K>
bool BST<E, K>::minimum (E & e)
{
BNode<E> * p = root;

if(!p) return false;
else {
   while (p -> leftChild)
      p = p -> leftChild;
   e = p -> data;
   return true;
   }
}

template <class E, class K>
void BST<E, K>::aPrint( )
{
   inOutput( );
}

