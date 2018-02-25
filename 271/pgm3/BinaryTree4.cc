//
// File : BinaryTree4.cc
//

#include "BinaryTree4.h"
#include <iostream>


template <class T>
T BNode<T>::getData (BNode<T> * t) const
{// T data type requires copy constructor
   return t -> data;
}

template <class T>
void BNode<T>::setData(BNode<T> * t, T & elm)
{// T data type requires assignment operator
   t -> data = elm;
}

template <class T>
void BinaryTree<T>::makeTree (const T & elm, BinaryTree<T> & left, BinaryTree<T> & right)
{// Combine left, right, and elm to make a new tree.
   root = new BNode<T>(elm);
   root -> leftChild = left.root;
   root -> rightChild = right.root;
   root -> parent = 0;
   left.root -> parent = right.root -> parent = root;
}

template <class T>
void BinaryTree<T>::preorder (void (*Visit)(BNode<T> * u), BNode<T> * t)
{
if (t) {
   Visit(t);
   preorder(Visit, t -> leftChild);
   preorder(Visit, t -> rightChild);
   }
}

template <class T>
void BinaryTree<T>::inorder (void (*Visit)(BNode<T> * u), BNode<T> * t)
{
if (t) {
   inorder(Visit, t -> leftChild);
   Visit(t);
   inorder(Visit, t -> rightChild);
   }
}

template <class T>
void BinaryTree<T>::postorder (void (*Visit)(BNode<T> * u), BNode<T> * t)
{
if (t) {
   postorder (Visit, t -> leftChild);
   postorder (Visit, t -> rightChild);
   Visit(t);
   }
}

template <class T>
bool BinaryTree<T>::Root (T & elm) const
{
if (root) {
   elm = root -> data;
   return true;
   }
else
   return false;                                // no root
}

template <class T>
void BinaryTree<T>::inOutput ( )
{
   inorder (output, root);
   cout << endl;
}

