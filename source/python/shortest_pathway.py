import heapq

# Define a function that takes a graph and a source node as arguments
def dijkstra(graph, source):
  # Initialize a dictionary to store the distance of each node from the source
  distance = {}
  # Set the distance of the source node to zero
  distance[source] = 0
  # Initialize a set to keep track of the visited nodes
  visited = set()
  # Initialize a priority queue to store the nodes with their distance values
  queue = [(0, source)]
  # Loop until the queue is empty
  while queue:
    # Pop the node with the smallest distance value
    dist, node = heapq.heappop(queue)
    # Mark the node as visited
    visited.add(node)
    # Loop through the neighbors of the node
    for neighbor in graph[node]:
      # If the neighbor is not visited
      if neighbor not in visited:
        # Calculate the distance of the neighbor from the source
        new_dist = dist + graph[node][neighbor]
        # If the distance is smaller than the current distance value of the neighbor
        if new_dist < distance.get(neighbor, float('inf')):
          # Update the distance value of the neighbor
          distance[neighbor] = new_dist
          # Push the neighbor and its distance value to the queue
          heapq.heappush(queue, (new_dist, neighbor))
  # Return the distance dictionary
  return distance

# Define a graph as a dictionary of dictionaries
# Each key is a node and each value is another dictionary
# The inner dictionary maps the neighbors of the node to the edge weights
graph = {
  'A': {'B': 4, 'C': 2},
  'B': {'A': 4, 'C': 1, 'D': 5},
  'C': {'A': 2, 'B': 1, 'D': 8, 'E': 10},
  'D': {'B': 5, 'C': 8, 'E': 2, 'F': 6},
  'E': {'C': 10, 'D': 2, 'F': 9},
  'F': {'D': 6, 'E': 9}
}

# Call the dijkstra function with the graph and the source node
distance = dijkstra(graph, 'A')
# Print the distance dictionary
print(distance)