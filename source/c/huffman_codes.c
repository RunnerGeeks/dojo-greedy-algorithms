#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the nodes of the Huffman tree
typedef struct node {
    char character; // The character
    int frequency; // The frequency
    struct node *left; // The left child
    struct node *right; // The right child
} node;

// Define a function to create a new node
node *create_node(char character, int frequency) {
    // Allocate memory for the node
    node *new_node = (node *)malloc(sizeof(node));
    // Assign the character and frequency
    new_node -> character = character;
    new_node -> frequency = frequency;
    // Initialize the left and right children as NULL
    new_node -> left = NULL;
    new_node -> right = NULL;
    // Return the node
    return new_node;
}

// Define a function to compare two nodes by their frequency
int compare_nodes(const void *a, const void *b) {
    // Cast the pointers to node pointers
    node *node_a = *(node **)a;
    node *node_b = *(node **)b;
    // Return the difference of their frequencies
    return node_a -> frequency - node_b -> frequency;
}

// Define a function to create the frequency table
int *create_freq_table(char *data) {
    // Initialize an array of size 256 to store the frequencies of each ASCII character
    int *freq_table = (int *)calloc(256, sizeof(int));
    // Loop through the data
    for (int i = 0; data[i] != '\0'; i++) {
        // Increment the frequency of the current character
        freq_table[(unsigned char)data[i]]++;
    }
    // Return the frequency table
    return freq_table;
}

// Define a function to create the Huffman tree
node *create_huffman_tree(int *freq_table) {
    // Initialize an array of node pointers to store the nodes of the Huffman tree
    node **nodes = (node **)malloc(256 * sizeof(node *));
    // Initialize a variable to store the number of nodes
    int node_count = 0;
    // Loop through the frequency table
    for (int i = 0; i < 256; i++) {
        // If the frequency of the current character is positive
        if (freq_table[i] > 0) {
            // Create a node for the character and frequency pair
            node *new_node = create_node(i, freq_table[i]);
            // Add the node to the array
            nodes[node_count] = new_node;
            // Increment the node count
            node_count++;
        }
    }
    // Loop until there is only one node left in the array
    while (node_count > 1) {
        // Sort the array by the frequency of the nodes
        qsort(nodes, node_count, sizeof(node *), compare_nodes);
        // Extract the two nodes with the minimum frequency
        node *left = nodes[0];
        node *right = nodes[1];
        // Create a new internal node with the sum of their frequencies
        node *internal = create_node('\0', left -> frequency + right -> frequency);
        // Make the extracted nodes as the children of the new node
        internal -> left = left;
        internal -> right = right;
        // Remove the two nodes from the array
        nodes[0] = nodes[node_count - 1];
        nodes[1] = nodes[node_count - 2];
        // Replace the last node with the new node
        nodes[node_count - 2] = internal;
        // Decrement the node count
        node_count--;
    }
    // Return the remaining node as the root of the Huffman tree
    return nodes[0];
}

// Define a function to traverse the Huffman tree and assign codes
void assign_codes(node *root, char *code, char **codes) {
    // If the node is a leaf node
    if (root -> character != '\0') {
        // Copy the code to the codes array
        codes[(unsigned char)root -> character] = code;
    }
    // Otherwise
    else {
        // Allocate memory for the left and right codes
        char *left_code = (char *)malloc(strlen(code) + 2);
        char *right_code = (char *)malloc(strlen(code) + 2);
        // Copy the code to the left and right codes
        strcpy(left_code, code);
        strcpy(right_code, code);
        // Append 0 to the left code and 1 to the right code
        strcat(left_code, "0");
        strcat(right_code, "1");
        // Recursively traverse the left and right subtrees
        assign_codes(root -> left, left_code, codes);
        assign_codes(root -> right, right_code, codes);
    }
}

// Define a function to encode the data
char *encode_data(char *data, char **codes) {
    // Initialize an empty string
    char *encoded_data = (char *)malloc(1);
    encoded_data[0] = '\0';
    // Loop through the data
    for (int i = 0; data[i] != '\0'; i++) {
        // Replace each character with its code
        encoded_data = (char *)realloc(encoded_data, strlen(encoded_data) + strlen(codes[(unsigned char)data[i]]) + 1);
        strcat(encoded_data, codes[(unsigned char)data[i]]);
    }
    // Return the encoded data
    return encoded_data;
}

// Define a function to decode the data
char *decode_data(char *encoded_data, node *root) {
    // Initialize an empty string
    char *decoded_data = (char *)malloc(1);
    decoded_data[0] = '\0';
    // Initialize the current node as the root
    node *current_node = root;
    // Loop through the encoded data
    for (int i = 0; encoded_data[i] != '\0'; i++) {
        // If the bit is 0, move to the left child
        if (encoded_data[i] == '0') {
            current_node = current_node -> left;
        }
        // If the bit is 1, move to the right child
        else {
            current_node = current_node -> right;
        }
        // If the current node is a leaf node
        if (current_node-> character != '\0') {
            // Append its character to the decoded data
            decoded_data = (char *)realloc(decoded_data, strlen(decoded_data) + 2);
            decoded_data[strlen(decoded_data) + 1] = '\0';
            decoded_data[strlen(decoded_data)] = current_node -> character;
            // Reset the current node to the root
            current_node = root;
        }
    }
    // Return the decoded data
    return decoded_data;
}

// Test the functions with some example data
int main(int argc, char** argv) {
    char *data = "mississippi";

    int *freq_table = create_freq_table(data);

    node *root = create_huffman_tree(freq_table);

    char **codes = (char **)calloc(256, sizeof(char *));
    assign_codes(root, "", codes);

    char *encoded_data = encode_data(data, codes);

    char *decoded_data = decode_data(encoded_data, root);

    printf("The original data is: %s\n", data);
    printf("The encoded data is: %s\n", encoded_data);
    printf("The decoded data is: %s\n", decoded_data);

    return 0;
}
