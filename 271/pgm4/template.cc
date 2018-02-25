/**
 * This file contains the template data for g++ to compile properly.
 * @author David Haltinner
 * @date Nov 14 2002
 * */
#include "Chain.h"
#include "Chain.cc"
#include "Double.h"
#include "Double.cc"
#include "LList.h"
#include "LList.cc"
#include "HashTb.h"
#include "App.cc"
template class LList<Hdata>;
template class HashTb<Hdata, long>;
template class HashChain<Hdata, long>;
template class HashDouble<Hdata, long>;
