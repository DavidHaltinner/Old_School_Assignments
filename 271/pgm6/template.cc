/**
 * This file contains the template data for g++ to compile it properly.
 * @author David Haltinner
 * @date Dec 12 2002
 * */
#include "LList.h"
#include "LList.cc"
#include "Big.cc"
template class LList<Big>;
