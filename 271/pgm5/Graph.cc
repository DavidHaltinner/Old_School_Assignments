#ifndef GRAPH_H
#define GRAPH_H
/**
 * This is the Graph class. It uses an adjancency matrix to hold the weights 
 * for the edges. There are functions to add a weight, remove a weight, get 
 * the number of vertices and edges, and also get first and next edges by a 
 * given one.
 * @author David Haltinner
 * @date 11-26-02
 * */
class Graph
{
   private:
      int numVertices;
      int numEdges;
      int ** adjMatrix;
   public:
      /**
       * Construtor making the adjacency Matrix out of the given size.
       * */
      Graph(int numV)
      {
         numVertices=numV;
         numEdges=0;
         adjMatrix = (int**)new int * [numVertices];
         for (int i=0; i<numVertices; i++)
            adjMatrix[i]=new int[numVertices];
         for (int i=0; i<numVertices; i++)
            for (int j=0; j<numVertices; j++)
               adjMatrix[i][j]=9999;
      }
      /**
       * Destructor deleting everything from the matrix
       * */
      ~Graph()
      {
         for (int i=0; i<numVertices; i++)
            delete [] adjMatrix[i];
         delete [] adjMatrix;
      }
      /**
       * This function returns the number of vertices in the graph
       * @return the number of vertices
       * */
      int numberVertices() 
      { 
         return numVertices; 
      }
      /**
       * This function returns the number of edges in the graph. I thought 
       * I might use it, but ended up not.
       * @return the number of edges.
       * */
      int numberEdges() 
      { 
         return numEdges; 
      }
      /**
       * This function returns the first vertex of an edge that a gived vertex 
       * share. It has also gone unused.
       * @param tmp, which is the vertex to find an edge with
       * @return the vertex with an edge, or one past the size if doesnt exist
       * */
      int first(int tmp)
      {
         for (int i=0; i<numVertices; i++)
            if (adjMatrix[tmp-1][i] != 0) return i;
         return numVertices+1;
      }
      /**
       * This is similar to first() but it finds the next edge after the two 
       * given verties. It also went unsed.
       * @param temp one, one of the vertices
       * @param temp2, the other vertice
       * @return the new vertice with an edge.
       * */
      int next(int temp1, int temp2)
      {
         for (int i=temp2; i<numVertices; i++)
            if (adjMatrix[temp1-1][i]!=0) return i;
         return numVertices;
      }
      /**
       * This sets the weight of an edge between two given vertices.
       * @param temp1, which is on vertex
       * @param temp2, the second vertex
       * @param weight, which is the weight between the two
       * */
      void setEdge(int temp1, int temp2, int weight)
      {
         if (weight<0) return;
         if (adjMatrix[temp1-1][temp2-1] == 0) numEdges++;
         adjMatrix[temp1-1][temp2-1]=weight;
	 adjMatrix[temp2-1][temp1-1]=weight;
      }
      /**
       * This deletes the weight of the edge between two given vertices. It 
       * has gone unused.
       * @param temp1, which is one of the vertices
       * @param temp, which is the other vertice
       * */
      void delEdge(int temp1, int temp2)
      {
         if (adjMatrix[temp1-1][temp2-1]!=0) numEdges--;
         adjMatrix[temp1-1][temp2-1]=0;
	 adjMatrix[temp2-1][temp1-1]=0;
      }
      /**
       * This function returns the edge weight between two given vertices.
       * @param temp1 which is one of the vertices.
       * @param temp2 which is the second vertice.
       * @return the weight of the edge
       * */
      int weight(int temp1, int temp2)
      {
         return adjMatrix[temp1-1][temp2-1];
      }
};   
#endif
