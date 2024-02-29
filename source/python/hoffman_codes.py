import heapq

class Node:
    def __init__(self, char, freq):
        self.char = char # The character
        self.freq = freq # The frequency
        self.left = None # The left child
        self.right = None # The right child

    def __lt__(self, other):
        return self.freq < other.freq

# Define a function to create the frequency table
def create_freq_table(data):
    # Initialize an empty dictionary
    freq_table = {}
    # Loop through the data
    for char in data:
        # If the character is already in the dictionary, increment its frequency
        if char in freq_table:
            freq_table[char] += 1
        # Otherwise, initialize its frequency to 1
        else:
            freq_table[char] = 1
    # Return the frequency table
    return freq_table

# Define a function to create the Huffman tree
def create_huffman_tree(freq_table):
    # Initialize an empty list
    heap = []
    # Loop through the frequency table
    for char, freq in freq_table.items():
        # Create a node for each character and frequency pair
        node = Node(char, freq)
        # Add the node to the heap
        heapq.heappush(heap, node)
    # Loop until there is only one node left in the heap
    while len(heap) > 1:
        # Extract the two nodes with the minimum frequency
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        # Create a new internal node with the sum of their frequencies
        internal = Node(None, left.freq + right.freq)
        # Make the extracted nodes as the children of the new node
        internal.left = left
        internal.right = right
        # Add the new node to the heap
        heapq.heappush(heap, internal)
    # Return the remaining node as the root of the Huffman tree
    return heapq.heappop(heap)

# Define a function to traverse the Huffman tree and assign codes
def assign_codes(node, code, codes):
    # If the node is a leaf node, add the code to the dictionary
    if node.char is not None:
        codes[node.char] = code
    # Otherwise, recursively traverse the left and right subtrees
    else:
        assign_codes(node.left, code + "0", codes) # Append 0 to the code for the left edge
        assign_codes(node.right, code + "1", codes) # Append 1 to the code for the right edge

# Define a function to encode the data
def encode_data(data, codes):
    # Initialize an empty string
    encoded_data = ""
    # Loop through the data
    for char in data:
        # Replace each character with its code
        encoded_data += codes[char]
    # Return the encoded data
    return encoded_data

# Define a function to decode the data
def decode_data(encoded_data, root):
    # Initialize an empty string
    decoded_data = ""
    # Initialize the current node as the root
    current_node = root
    # Loop through the encoded data
    for bit in encoded_data:
        # If the bit is 0, move to the left child
        if bit == "0":
            current_node = current_node.left
        # If the bit is 1, move to the right child
        else:
            current_node = current_node.right
        # If the current node is a leaf node, append its character to the decoded data
        if current_node.char is not None:
            decoded_data += current_node.char
            # Reset the current node to the root
            current_node = root
    # Return the decoded data
    return decoded_data

# Test the functions with some example data
data = "mississippi"

freq_table = create_freq_table(data)

root = create_huffman_tree(freq_table)

codes = {}
assign_codes(root, "", codes)

encoded_data = encode_data(data, codes)

decoded_data = decode_data(encoded_data, root)

print("The original data is:", data)
print("The encoded data is:", encoded_data)
print("The decoded data is:", decoded_data)
