#include <iostream.h>
/**
 * This is Edge class used in creating the Minimum Cost Spanning Tree.
 * It has constructors (copy, empty, and with given data), <, ==, << 
 * operators.
 * @author David Haltinner
 * @date 11-26-02
 * */
class Edge
{
   public:
      int firstedge;
      int secondedge;
      int edgelength;
      //Empty Constructor
      Edge() { };
      //Constructor that takes in the edges and weight
      Edge (int f, int s, int l)
      {
         firstedge=f;
         secondedge=s;
         edgelength=l;
      }
      //Copy Constructor
      Edge(const Edge & temp)
      {
         firstedge=temp.firstedge;
         secondedge=temp.secondedge;
         edgelength=temp.edgelength;
      }
      //Empty Destructor
      ~Edge() {}
      /**
       * Overloaded assignment operator. Thought i might end up using it.
       * @param temp, which is the Edge to copy
       * @return the new edge
       * */      
      Edge & operator = (const Edge & temp)
      {
         firstedge=temp.firstedge;
         secondedge=temp.secondedge;
         edgelength=temp.edgelength;
         return *this;
      }
      /**
       * Overloaded less than operator. Set needs this since he sorts the 
       * data when inserted. 
       * @param temp, which is the Edge to compare with
       * @return true if the weight is less, false if it is larger
       * */
      bool operator < (const Edge & temp) const
      {
         return edgelength<temp.edgelength;
      }
      /**
       * This function is the overloaded == operator. I orignally wrote this
       * thinking i may need it, but I never did. So i just left it.
       * @param temp, which is the edge to compare with
       * @return true if they are equal, flase otherwise
       * */
      bool operator == (const Edge & temp)
      {
         return ((firstedge==temp.firstedge || firstedge==temp.secondedge) 
               && (secondedge==temp.secondedge || secondedge==temp.firstedge) 
               && edgelength==temp.edgelength);
      }
      /**
       * Overladed output operator for easy displaying.
       * @param os, which is the ouput stream
       * @param temp which is the Edge to output
       * */
      friend ostream & operator << (ostream & os, const Edge & temp) 
      {
         os<<"Edge ("<<temp.firstedge<<","<<temp.secondedge<<") with weight "
           <<temp.edgelength<<"."<<endl;
         return os;
      }
};
