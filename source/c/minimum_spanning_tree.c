// Importing the stdio.h and limits.h libraries for input/output and constants
#include <stdio.h>
#include <limits.h>

// Defining a constant for the number of vertices in the graph
#define V 5

// Defining a function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[])
{
  // Initializing the minimum value and index
  int min = INT_MAX, min_index;
  // Looping through all the vertices
  for (int v = 0; v < V; v++)
    // If the vertex is not in the MST set and has a smaller key value than the current minimum
    if (mstSet[v] == 0 && key[v] < min)
      // Update the minimum value and index
      min = key[v], min_index = v;
  // Return the minimum index
  return min_index;
}

// Defining a function to print the MST and the edge weights
void printMST(int parent[], int graph[V][V])
{
  // Printing the header
  printf("Edge \tWeight\n");
  // Looping through all the vertices except the first one
  for (int i = 1; i < V; i++)
    // Printing the edge and the weight
    printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Defining a function to find the minimum spanning tree using Prim's algorithm
void primMST(int graph[V][V])
{
  // Initializing the arrays to store the key values, the MST set, and the parent vertices
  int key[V];
  int mstSet[V];
  int parent[V];
  // Assigning infinite values to all the key values and false values to all the MST set
  for (int i = 0; i < V; i++)
    key[i] = INT_MAX, mstSet[i] = 0;
  // Setting the key value of the first vertex to zero and the parent to -1
  key[0] = 0;
  parent[0] = -1;
  // Looping until all the vertices are included in the MST set
  for (int count = 0; count < V - 1; count++)
  {
    // Finding the vertex with the minimum key value
    int u = minKey(key, mstSet);
    // Adding the vertex to the MST set
    mstSet[u] = 1;
    // Updating the key values and parent vertices of the adjacent vertices
    for (int v = 0; v < V; v++)
      // If there is an edge between u and v, v is not in the MST set, and the weight of the edge is smaller than the current key value of v
      if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
        // Update the key value and the parent vertex of v
        parent[v] = u, key[v] = graph[u][v];
  }
  // Printing the MST and the edge weights
  printMST(parent, graph);
}

// Defining the main function
int main(int argc, char** argv)
{
  // Defining a sample graph as an adjacency matrix
  // The graph is the same as the one shown in [this article](https://www.programiz.com/dsa/prim-algorithm)
  int graph[V][V] = {{0, 2, 0, 6, 0},
                     {2, 0, 3, 8, 5},
                     {0, 3, 0, 0, 7},
                     {6, 8, 0, 0, 9},
                     {0, 5, 7, 9, 0}};
  // Calling the primMST function with the graph
  primMST(graph);
  // Returning zero to indicate successful termination
  return 0;
}
