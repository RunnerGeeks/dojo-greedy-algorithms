# Importing the heapq module for priority queue
import heapq

# Defining a function to find the minimum spanning tree
def prim(graph, start):
  # Initializing the variables
  mst = [] # List to store the edges of the minimum spanning tree
  visited = set() # Set to keep track of the visited nodes
  pq = [] # Priority queue to store the edges with their weights
  # Adding the start node and its adjacent edges to the priority queue
  visited.add(start)
  for dest, weight in graph[start].items():
    heapq.heappush(pq, (weight, start, dest))
  # Looping until the priority queue is empty
  while pq:
    # Popping the edge with the minimum weight
    weight, src, dest = heapq.heappop(pq)
    # Checking if the destination node is already visited
    if dest in visited:
      continue
    # Adding the edge to the minimum spanning tree
    mst.append((src, dest, weight))
    # Marking the destination node as visited
    visited.add(dest)
    # Adding the destination node's adjacent edges to the priority queue
    for next_dest, next_weight in graph[dest].items():
      heapq.heappush(pq, (next_weight, dest, next_dest))
  # Returning the minimum spanning tree
  return mst

# Defining a sample graph as an adjacency list
# The graph is the same as the one shown in [this article](https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/)
graph = {
  "A": {"B": 2, "D": 3},
  "B": {"A": 2, "C": 4, "E": 3},
  "C": {"B": 4, "E": 1, "F": 5},
  "D": {"A": 3, "E": 4, "G": 6},
  "E": {"B": 3, "C": 1, "D": 4, "F": 2, "G": 5},
  "F": {"C": 5, "E": 2, "H": 3},
  "G": {"D": 6, "E": 5, "H": 4},
  "H": {"F": 3, "G": 4}
}

# Calling the prim function with the graph and a start node
mst = prim(graph, "A")

# Printing the minimum spanning tree
print("The minimum spanning tree is:")
for src, dest, weight in mst:
  print(f"{src} - {dest} : {weight}")
