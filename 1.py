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
