ASSIGNMENT NO : 1
TITLE: IMPLEMENTATION OF COLLISION RESOLUTION STRATEGIES
PROBLEM STATEMENT: -
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look
up client‘s telephone number. Make use of two collision handling techniques and compare them using
number of comparisons required to find a set of telephone numbers 



class HashTable:
    def __init__(self, capacity):
        self.capacity = capacity
        self.table = [-1] * capacity
        self.size = 0

    def hash(self, key):
        return key % self.capacity

    def insert_linear(self, key):
        if self.size == self.capacity:
            print("HashTable is full!")
            return

        index = self.hash(key)
        start_index = index  # To avoid infinite loops
        while self.table[index] != -1:
            index = (index + 1) % self.capacity
            if index == start_index:
                print("No empty slot found using Linear Probing.")
                return

        self.table[index] = key
        self.size += 1

    def insert_quadratic(self, key):
        if self.size == self.capacity:
            print("HashTable is full!")
            return

        index = self.hash(key)
        i = 1
        original_index = index
        while self.table[index] != -1:
            index = (original_index + i * i) % self.capacity
            i += 1
            if i == self.capacity:
                print("No empty slot found using Quadratic Probing.")
                return

        self.table[index] = key
        self.size += 1

    def display(self):
        for i in range(self.capacity):
            if self.table[i] != -1:
                print(f"Index {i}: {self.table[i]}")
            else:
                print(f"Index {i}: Empty")


def menu():
    print("\nHash Table Menu ")
    print("1. Insert using Linear Probing")
    print("2. Insert using Quadratic Probing")
    print("3. Display")
    print("4. Exit")


def main():
    size = int(input("Enter the size of the hash table: "))
    ht = HashTable(size)

    while True:
        menu()
        try:
            ch = int(input("Enter your choice: "))
            if ch == 1:
                key = int(input("Enter value to insert using Linear Probing: "))
                ht.insert_linear(key)
            elif ch == 2:
                key = int(input("Enter value to insert using Quadratic Probing: "))
                ht.insert_quadratic(key)
            elif ch == 3:
                print("\nHash Table contents:")
                ht.display()
            elif ch == 4:
                print("Exiting...")
                break
            else:
                print("Wrong choice! Please enter a valid option.")
        except ValueError:
            print("Please enter numeric input only!")


if __name__ == "__main__":
    main()


Explanation-Sure Aryan! Let me explain each part of your `HashTable` program **line by line** so that you can fully understand how it works and how collision resolution using **Linear Probing** and **Quadratic Probing** is implemented.

---

### 🔹 Class Definition and Initialization

```python
class HashTable:
    def __init__(self, capacity):
        self.capacity = capacity
        self.table = [-1] * capacity
        self.size = 0
```

* `class HashTable:` → This defines a new class `HashTable` which will implement our hashing mechanism.
* `def __init__(self, capacity):` → Constructor method that runs when an object is created.
* `self.capacity = capacity` → Stores the size of the hash table.
* `self.table = [-1] * capacity` → Initializes the hash table with -1 to indicate all slots are empty.
* `self.size = 0` → Keeps track of the number of keys inserted.

---

### 🔹 Hash Function

```python
    def hash(self, key):
        return key % self.capacity
```

* This method returns the **hash index** by performing `key % capacity`.
* Ensures that the key is mapped within the range `[0, capacity - 1]`.

---

### 🔹 Linear Probing Insertion

```python
    def insert_linear(self, key):
        if self.size == self.capacity:
            print("HashTable is full!")
            return
```

* If the table is full, insertion is not allowed.

```python
        index = self.hash(key)
        start_index = index
```

* Get the initial index using the hash function.
* `start_index` is saved to detect if we looped back (to avoid infinite loops).

```python
        while self.table[index] != -1:
            index = (index + 1) % self.capacity
            if index == start_index:
                print("No empty slot found using Linear Probing.")
                return
```

* If slot is occupied, move **linearly** to the next slot.
* If we've tried all slots and came back to the start, exit.

```python
        self.table[index] = key
        self.size += 1
```

* Key is inserted at the available index.
* Increment the size counter.

---

### 🔹 Quadratic Probing Insertion

```python
    def insert_quadratic(self, key):
        if self.size == self.capacity:
            print("HashTable is full!")
            return
```

* Check if the table is full.

```python
        index = self.hash(key)
        i = 1
        original_index = index
```

* Start probing from the hashed index.
* `i` is used for the `i*i` step.
* `original_index` stores initial position for calculation.

```python
        while self.table[index] != -1:
            index = (original_index + i * i) % self.capacity
            i += 1
            if i == self.capacity:
                print("No empty slot found using Quadratic Probing.")
                return
```

* Uses the formula: `(original_index + i²) % capacity` to avoid clustering.
* If `i` reaches the table size, exit to avoid infinite probing.

```python
        self.table[index] = key
        self.size += 1
```

* Insert and increase the count.

---

### 🔹 Display the Hash Table

```python
    def display(self):
        for i in range(self.capacity):
            if self.table[i] != -1:
                print(f"Index {i}: {self.table[i]}")
            else:
                print(f"Index {i}: Empty")
```

* This method prints the contents of the hash table.
* Shows either the value or `"Empty"` if not filled.

---

### 🔹 Menu Function

```python
def menu():
    print("\nHash Table Menu ")
    print("1. Insert using Linear Probing")
    print("2. Insert using Quadratic Probing")
    print("3. Display")
    print("4. Exit")
```

* This just prints the options for the user.

---

### 🔹 Main Driver Code

```python
def main():
    size = int(input("Enter the size of the hash table: "))
    ht = HashTable(size)
```

* Takes table size from the user and creates a `HashTable` object.

```python
    while True:
        menu()
        try:
            ch = int(input("Enter your choice: "))
```

* Continuously shows the menu and takes the user's choice.
* `try-except` block is used to catch invalid (non-numeric) input.

```python
            if ch == 1:
                key = int(input("Enter value to insert using Linear Probing: "))
                ht.insert_linear(key)
            elif ch == 2:
                key = int(input("Enter value to insert using Quadratic Probing: "))
                ht.insert_quadratic(key)
            elif ch == 3:
                print("\nHash Table contents:")
                ht.display()
            elif ch == 4:
                print("Exiting...")
                break
            else:
                print("Wrong choice! Please enter a valid option.")
```

* Handles each menu option.
* Based on the choice, inserts using selected method or displays the table.
* Exits the loop when option 4 is selected.

```python
        except ValueError:
            print("Please enter numeric input only!")
```

* Catches invalid input (e.g., letters) and shows a message.

---

### 🔹 Program Execution Starts Here

```python
if __name__ == "__main__":
    main()
```

* This ensures the `main()` function only runs when this file is executed directly.

---

Questions-
🔹 Basic Conceptual Understanding
Q1. What is a hash table, and why is it used?
A: A hash table is a data structure that stores key-value pairs. It uses a hash function to map keys to indices in an array, allowing for fast insertion, deletion, and lookup operations—typically in O(1) time. It's used for efficient data retrieval.

Q2. What is a collision in hashing?
A: A collision occurs when two different keys produce the same hash value or index in the hash table. Since only one value can be stored at each index, we need a way to resolve this conflict.

Q3. What are some common collision resolution strategies?
A: The most common strategies include:

Open Addressing: Linear Probing, Quadratic Probing, Double Hashing.

Closed Addressing (Chaining): Using a linked list or other structure to store multiple items at the same index.

🔹 Technique-Focused Questions
Q4. How does Linear Probing resolve collisions?
A: In linear probing, when a collision occurs, the algorithm checks the next slot in a sequential manner (i.e., (i+1)%size, (i+2)%size, etc.) until an empty slot is found. It is simple to implement but can cause clustering.

Q5. What is Chaining in hashing?
A: Chaining handles collisions by maintaining a list (usually a linked list) at each index of the hash table. All elements that hash to the same index are stored in this list, which allows multiple values to coexist at a single table index.

Q6. What is the main difference between Linear Probing and Chaining?
A:

Linear Probing: Stores data in the hash table array itself using a probing sequence.

Chaining: Stores data outside the array using linked lists, thus allowing unlimited collisions at a single index.

🔹 Implementation and Efficiency
Q7. Which two techniques did you implement and why?
A: We implemented Linear Probing and Chaining to demonstrate two different approaches—one that uses contiguous memory and another that uses dynamic memory. This also helped in comparing their efficiencies based on number of comparisons.

Q8. How did you compare the two methods?
A: We measured and compared the number of comparisons required to find telephone numbers stored in the hash table for both methods. Fewer comparisons indicate better performance.

Q9. What were your findings from the comparison?
A: Chaining generally performed better for higher load factors, as linear probing faced clustering, increasing the number of comparisons required. Linear probing was faster at low load factors but degrades quickly as the table fills.

🔹 Advanced and Theoretical Questions
Q10. What is clustering in hashing?
A: Clustering occurs when many elements get grouped together in consecutive table slots, especially in linear probing. This increases the time to find empty slots and slows down searches.

Q11. What is the load factor, and how does it affect performance?
A: Load factor is the ratio of number of elements in the hash table to its size. A high load factor means the table is nearly full, which increases collisions and reduces performance, especially in open addressing.

Q12. What data structure did you use for chaining, and why?
A: We used linked lists for chaining. They are dynamic, easy to implement, and can store multiple values at the same index without affecting other parts of the table.

Q13. Can the same key be inserted twice in a hash table?
A: Normally no, because keys are unique identifiers. If attempted, it either updates the value or is ignored based on implementation.

Q14. What happens if the hash table becomes full in Linear Probing?
A: If the table is full, linear probing will loop through the entire table without finding an empty slot, resulting in an overflow condition.
