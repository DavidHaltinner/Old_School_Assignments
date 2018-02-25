/**
 * This file contains the template data for g++ to compile it properly.
 * @author David Haltinner
 * @date Oct 31 2002
 * */
#include "LList.h"
#include "LList.cc"
#include "BST4.h"
#include "BST4.cc"
#include "BinaryTree4.h"
#include "BinaryTree4.cc"
#include "Reg.cc"

template class LList<int>;
template class BST<sData, int>;
template class BST<cData, int>;
