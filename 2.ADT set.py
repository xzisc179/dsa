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
