ASSIGNMENT NO: 2
TITLE: CREATE ADT THAT IMPLEMENT THE "SET" CONCEPT.
PROBLEM STATEMENT: -
Create ADT that implements the "set" concept and perform following operations:
1. Add (new Element) -Place a value into the set,
2. Remove (element) Remove the value
3. Contains (element) Return true if element is in collection,
4. Size () Return number of values in collection Iterator () Return an iterator used to loop over collection,
5. Intersection of two sets,
6. Union of two sets,
7. Difference between two sets,
8. Subset 



class Set:
    def __init__(self):
        """Initialize the set as an empty list."""
        self.elements = []

    def add(self, element):
        """Add a new element to the set if it's not already present."""
        if element not in self.elements:
            self.elements.append(element)

    def remove(self, element):
        """Remove an element from the set if it exists."""
        if element in self.elements:
            self.elements.remove(element)

    def contains(self, element):
        """Return True if the element is in the set, otherwise False."""
        return element in self.elements

    def size(self):
        """Return the number of elements in the set."""
        return len(self.elements)

    def __iter__(self):
        """Return an iterator for the set."""
        return iter(self.elements)

    def intersection(self, other_set):
        """Return a new set that is the intersection of this set and another set."""
        result = Set()
        for element in self.elements:
            if other_set.contains(element):
                result.add(element)
        return result

    def union(self, other_set):
        """Return a new set that is the union of this set and another set."""
        result = Set()
        for element in self.elements:
            result.add(element)
        for element in other_set.elements:
            result.add(element)
        return result

    def difference(self, other_set):
        """Return a new set that is the difference of this set and another set."""
        result = Set()
        for element in self.elements:
            if not other_set.contains(element):
                result.add(element)
        return result

    def subset(self, other_set):
        """Return True if this set is a subset of another set."""
        for element in self.elements:
            if not other_set.contains(element):
                return False
        return True


def menu():
    """Display the menu for user operations."""
    print("\n1. Display the size of Set 1")
    print("2. Display the size of Set 2")
    print("3. Add an element to Set 1")
    print("4. Add an element to Set 2")
    print("5. Remove an element from Set 1")
    print("6. Remove an element from Set 2")
    print("7. Intersection of Set 1 and Set 2")
    print("8. Union of Set 1 and Set 2")
    print("9. Difference between Set 1 and Set 2")
    print("10. Check if Set 1 is a Subset of Set 2")
    print("11. Exit")


def main():
    """Main function to interact with the user and perform set operations."""
    set1 = Set()
    set2 = Set()

    while True:
        menu()
        try:
            choice = int(input("Enter your choice: "))
            if choice == 1:
                print("Size of Set 1:", set1.size())
            elif choice == 2:
                print("Size of Set 2:", set2.size())
            elif choice == 3:
                element = int(input("Enter element to add to Set 1: "))
                set1.add(element)
            elif choice == 4:
                element = int(input("Enter element to add to Set 2: "))
                set2.add(element)
            elif choice == 5:
                element = int(input("Enter element to remove from Set 1: "))
                set1.remove(element)
            elif choice == 6:
                element = int(input("Enter element to remove from Set 2: "))
                set2.remove(element)
            elif choice == 7:
                print("Performing Intersection of Set 1 and Set 2")
                intersection_set = set1.intersection(set2)
                print("Intersection result:")
                for element in intersection_set:
                    print(element)
            elif choice == 8:
                print("Performing Union of Set 1 and Set 2")
                union_set = set1.union(set2)
                print("Union result:")
                for element in union_set:
                    print(element)
            elif choice == 9:
                print("Performing Difference (Set 1 - Set 2)")
                difference_set = set1.difference(set2)
                print("Difference result:")
                for element in difference_set:
                    print(element)
            elif choice == 10:
                print("Checking if Set 1 is a Subset of Set 2:")
                print("Is Set 1 a subset of Set 2?", set1.subset(set2))
            elif choice == 11:
                print("Exiting...")
                break
            else:
                print("Invalid choice! Please try again.")
        except ValueError:
            print("Invalid input! Please enter a valid number.")


if __name__ == "__main__":
    main()



Explanation - Sure Aryan! Here's a **line-by-line explanation** of **Assignment No. 2: ADT for Set Operations** so you understand everything clearly.

---

### 🔷 **`class Set:`**

Defines a class `Set` to simulate set behavior using lists.

---

### 🔸 `def __init__(self):`

Initializes an empty list to store unique elements in the set.

```python
self.elements = []
```

---

### 🔸 `def add(self, element):`

Adds an element **only if it's not already present**, ensuring set uniqueness.

```python
if element not in self.elements:
    self.elements.append(element)
```

---

### 🔸 `def remove(self, element):`

Removes the element if it exists in the set.

```python
if element in self.elements:
    self.elements.remove(element)
```

---

### 🔸 `def contains(self, element):`

Checks whether the element is in the set. Returns `True` or `False`.

```python
return element in self.elements
```

---

### 🔸 `def size(self):`

Returns the number of elements in the set.

```python
return len(self.elements)
```

---

### 🔸 `def __iter__(self):`

Returns an iterator so you can use the `for` loop to iterate over elements.

```python
return iter(self.elements)
```

---

### 🔸 `def intersection(self, other_set):`

Returns a **new Set** containing elements **common to both sets**.

```python
result = Set()
for element in self.elements:
    if other_set.contains(element):
        result.add(element)
return result
```

---

### 🔸 `def union(self, other_set):`

Returns a **new Set** with all **unique elements from both sets**.

```python
result = Set()
for element in self.elements:
    result.add(element)
for element in other_set.elements:
    result.add(element)
return result
```

---

### 🔸 `def difference(self, other_set):`

Returns a **new Set** with elements in this set **but not in other\_set**.

```python
result = Set()
for element in self.elements:
    if not other_set.contains(element):
        result.add(element)
return result
```

---

### 🔸 `def subset(self, other_set):`

Checks if **all elements** of this set are present in `other_set`.

```python
for element in self.elements:
    if not other_set.contains(element):
        return False
return True
```

---

## 🌟 User Interaction Functions:

---

### 🔸 `def menu():`

Displays the options for user to perform different set operations.

---

### 🔸 `def main():`

The **driver function** that uses `Set` class and provides a menu to:

* Add/remove elements
* Get size
* Perform union, intersection, difference
* Check for subset
* Exit

It creates two sets: `set1` and `set2`, and allows user to manipulate them.

---

### 🔸 `if __name__ == "__main__":`

Ensures `main()` runs **only** when the script is executed directly.

---

Questions -
✅ Assignment No. 2 Oral Questions with Answers
Title: Create ADT that implements the "Set" concept

🔹 Basic Conceptual Understanding
Q1. What is a Set in data structures?
A: A set is a collection of distinct elements with no duplicates. It supports operations like insertion, deletion, search, union, intersection, difference, and subset checking.

Q2. What is an ADT (Abstract Data Type)?
A: An ADT is a logical description of how data is organized and the operations supported on that data. It hides implementation details and shows only the interface.

Q3. How is a Set ADT different from an Array or List?
A: Unlike arrays or lists, a Set does not allow duplicate elements and often doesn’t maintain any particular order of elements.

🔹 Implementation-Oriented Questions
Q4. How did you implement the Set in your program?
A: We implemented the Set using either an array or a linked list and ensured that no duplicate elements were added. We also implemented functions for add, remove, contains, and set operations.

Q5. What does the add(element) function do?
A: It inserts a new element into the set only if it is not already present.

Q6. What does the remove(element) function do?
A: It searches and removes the specified element from the set, if it exists.

Q7. What is the purpose of the contains(element) function?
A: It checks whether the specified element exists in the set and returns true or false.

Q8. How do you find the size of the set?
A: The size() function counts and returns the total number of elements currently in the set.

Q9. How did you implement the iterator() function?
A: The iterator returns access to elements one by one (e.g., using a loop), allowing traversal through the set without exposing internal structure.

🔹 Set Theory Operations
Q10. How do you perform Union of two sets?
A: We create a new set and add all elements of both sets into it. Duplicates are automatically ignored.

Q11. How is Intersection performed?
A: By checking which elements are common to both sets, and storing those in a new set.

Q12. How do you compute the Difference between two sets A and B (A - B)?
A: We add elements from Set A into a new set only if they are not present in Set B.

Q13. How do you check if one set is a Subset of another?
A: For every element in Set A, we check if it exists in Set B. If all elements match, A is a subset of B.

Q14. What happens if we try to add a duplicate element?
A: It is ignored; sets do not allow duplicate entries.

Q15. What is the time complexity of common set operations?
A: Insertion/Deletion/Search: O(n) for array/linked list

Using hash table: O(1) on average

Using BST: O(log n)
