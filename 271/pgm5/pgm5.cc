#include "Graph.cc"
#include "Edge.cc"
#include <multiset.h>
#include <algorithm>
#include <list>
#include <time.h>
#include <fstream>
#include <iostream>
#include <iomanip>
/**
 * This function runs Prim's algorithm 10000 times on lists containing the 
 * edges and vertices. It displays the time and the edges of the minimum cost
 * spanning tree.
 * @param myGraph, which is the graph to build the tree from
 * */
void listPrim(Graph &myGraph)
{
   double starttime=clock();
   list<Edge> T;
   for (int time=0; time<10000; time++)
   {
      T.clear();
      list<int> U; //V is built into Graph, so is useless out here.
      int n=myGraph.numberVertices();
      U.push_back(1);
      for (int i=1; i<=n; i++) //while (U!=V)
      {
         int u;     //your 'v' is part of my temp edge.
         int min=9999;
         Edge temp;
         for (int j=1; j<=n; j++)
         {
            list<int>::iterator itr=find(U.begin(), U.end(), j);
            if (itr!=U.end())
               for (int k=1; k<=n; k++)
               {
                  list<int>::iterator itr2=find(U.begin(), U.end(), k);
                  if (itr2==U.end() && myGraph.weight(j,k)<min)
                  {
                     u=k;
                     temp.firstedge=j;
                     temp.secondedge=k;
                     min=myGraph.weight(j,k);
                     temp.edgelength=min;
                  }
               }
         }
         U.push_back(u);
         T.push_back(temp);
      }
   }
   double stoptime=clock();
   cout<<"Total time for 10,000 Prim tree creations with lists was "
       <<(stoptime-starttime)<<endl;
   T.unique();
   int total=0;
   while (!T.empty())
   {
      cout<<T.front();
      total=total+T.front().edgelength;
      T.pop_front();
   }
   cout<<"All that with a total cost of "<<total<<endl;
}
/**
 * This function runs Prim's algorithm 10000 times on sets containing the 
 * edges and vertices. It displays the time and the edges of the minimum cost
 * spanning tree.
 * @param myGraph, which is the graph to build the tree from
 * */
void setPrim(Graph &myGraph)
{
   double starttime=clock();
   multiset<Edge> T;
   for (int time=0; time<10000; time++)
   {
      T.clear();
      multiset<int> U;
      int n=myGraph.numberVertices();
      U.insert(1);
      for (int i=1; i<=n; i++)
      {
         int u;  
	 int min=9999;
         Edge temp;
         for (int j=1; j<=n; j++)
         {
            multiset<int>::iterator itr=find(U.begin(), U.end(), j);
            if (itr!=U.end())
               for (int k=1; k<=n; k++)
               {
                  multiset<int>::iterator itr2=find(U.begin(), U.end(), k);
                  if (itr2==U.end() && myGraph.weight(j,k)<min)
                  {
                     u=k;
                     temp.firstedge=j;
                     temp.secondedge=k;
                     min=myGraph.weight(j,k);
                     temp.edgelength=min;
                  }
               }
         }
         U.insert(u);
         T.insert(temp);
      }
   }
   double stoptime=clock();
   cout<<"Total time for 10,000 Prim tree creations with sets was "
       <<(stoptime-starttime)<<endl;
   multiset<Edge>::iterator itr;
   int total=0;
   for (int i=0; i<myGraph.numberVertices()-1; i++)
   {
      itr=T.begin();
      cout<<*itr;
      total=total+(*itr).edgelength;
      T.erase(itr);
   }
   cout<<"All that with a total cost of "<<total<<endl; 
}
/**
 * This is the main function. It grabs a file name as a parameter, builds a 
 * graph out of the data from it, and then calls the two Prim functions above 
 * to have them timed.
 * @param argc, which is the number of arguments
 * @param argv which holds the binary's name and the arguments
 * */
int main (int argc, char * argv[])
{   
   if (argc !=2){
      cout<<"Please give a file name as an argument"<<endl; 
      return 1; 
   }
   ifstream in(argv[1]);
   if (!in) { 
      cout<<"Open failed on file "<<argv[1]<<"!"<<endl; 
      return 1; 
   }
   int size;
   in>>size;
   Graph myGraph(size);
   int v1, v2, e;
   while(in)
   {
      in>>v1;
      in>>v2;
      in>>e;
      myGraph.setEdge(v1,v2,e);
   }
   cout.setf(ios::fixed);
   cout.precision(2);
   listPrim(myGraph);
   cout<<endl;
   setPrim(myGraph);
   return 0;
}
