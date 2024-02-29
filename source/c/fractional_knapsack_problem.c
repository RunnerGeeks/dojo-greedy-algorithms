#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value; // Value of the item
    int weight; // Weight of the item
    double ratio; // Value-to-weight ratio
} Item;

// Define a function to compare two items by their ratio
int compare_items(const void* a, const void* b) {
    Item* item_a = (Item*) a;
    Item* item_b = (Item*) b;
    // Return a negative, zero, or positive value depending on whether the ratio of a is less than, equal to, or greater than that of b
    return (item_b->ratio - item_a->ratio);
}

// Define a function to solve the fractional knapsack problem
double fractional_knapsack(Item* items, int n, int capacity) {
    // Sort the items by their ratio in descending order
    qsort(items, n, sizeof(Item), compare_items);
    // Initialize the total value and the remaining capacity
    double total_value = 0;
    int remaining_capacity = capacity;
    // Loop through the items
    for (int i = 0; i < n; i++) {
        // If the item can fit entirely, take it and update the value and capacity
        if (items[i].weight <= remaining_capacity) {
            total_value += items[i].value;
            remaining_capacity -= items[i].weight;
            printf("Added %d of item (value=%d, weight=%d) entirely\n", items[i].value, items[i].value, items[i].weight);
        }
        // If the item cannot fit entirely, take a fraction of it and break the loop
        else {
            double fraction = (double) remaining_capacity / items[i].weight;
            total_value += items[i].value * fraction;
            printf("Added %.2f of item (value=%d, weight=%d) partially\n", items[i].value * fraction, items[i].value, items[i].weight);
            break;
        }
    }
    // Return the total value
    return total_value;
}

// Test the function with some example items and capacity
int main(int argc, char** argv) {
    // Create an array of items
    Item items[] = {{60, 10, 6.0}, {100, 20, 5.0}, {120, 30, 4.0}, {80, 15, 5.3}, {40, 5, 8.0}, {50, 10, 5.0}};
    // Get the number of items
    int n = sizeof(items) / sizeof(items[0]);
    // Define the capacity of the knapsack
    int capacity = 50;
    // Call the function and display the result
    printf("The maximum value that can be obtained is %.2f\n", fractional_knapsack(items, n, capacity)); // Output: 280.00

    return 0;
}
