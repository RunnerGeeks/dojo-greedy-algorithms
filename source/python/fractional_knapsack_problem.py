# Define a class to store the items
class Item:
    def __init__(self, value, weight):
        self.value = value
        self.weight = weight
        self.ratio = value / weight # Calculate the value-to-weight ratio
        
    def __repr__(self):
        return f"Item(value={self.value}, weight={self.weight})"

# Define a function to solve the fractional knapsack problem
def fractional_knapsack(items, capacity):
    # Sort the items by their ratio in descending order
    items.sort(key=lambda x: x.ratio, reverse=True)
    # Initialize the total value and the remaining capacity
    total_value = 0
    remaining_capacity = capacity
    # Loop through the items
    for item in items:
        # If the item can fit entirely, take it and update the value and capacity
        if item.weight <= remaining_capacity:      
            total_value += item.value
            remaining_capacity -= item.weight
            print(f"Added {item.value} of item {item} entirely")
        # If the item cannot fit entirely, take a fraction of it and break the loop
        else:
            fraction = remaining_capacity / item.weight            
            total_value += item.value * fraction
            print(f"Added {item.value * fraction} of item {item} partially")
            break
    # Return the total value
    return total_value

# Test the function with some example items and capacity
items = [Item(60, 10), Item(100, 20), Item(120, 30), Item(80, 15), Item(40, 5), Item(50, 10)]
capacity = 50
print(fractional_knapsack(items, capacity)) # Output: 280.0
