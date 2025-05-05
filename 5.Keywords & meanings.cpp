ASSIGNMENT NO: 5
TITLE : TO STUDY DICTIONARY AND PERFORM DIFFERENT OPERATIONS ON IT USING
BINARY SEARCH TREE.
PROBLEM STATEMENT: A Dictionary stores keywords & its meanings. Now provide facility for
adding new keywords, deleting keywords, & updating values of any entry. Also provide facility to display
whole data sorted in ascending/ Descending order, Also we have to find how many maximum comparisons
may require for finding any keyword. 


#include<iostream>
#include<string>
using namespace std;

struct Node {
    string key;
    string meaning;
    Node* left;
    Node* right;
    
    Node(string k, string m) {
        key = k;
        meaning = m;
        left = right = nullptr;
    }
};

class Dictionary {
private:
    Node* root;
    
    // Helper function to insert a new node
    Node* insert(Node* root, string key, string meaning) {
        if (root == nullptr) {
            return new Node(key, meaning);
        }
        
        if (key < root->key) {
            root->left = insert(root->left, key, meaning);
        } else if (key > root->key) {
            root->right = insert(root->right, key, meaning);
        }
        
        return root;
    }
    
    // Helper function for inorder traversal (ascending order)
    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->key << ": " << root->meaning << endl;
        inorder(root->right);
    }
    
    // Helper function for reverse inorder traversal (descending order)
    void descending_order(Node* root) {
        if (root == nullptr) return;
        descending_order(root->right);
        cout << root->key << ": " << root->meaning << endl;
        descending_order(root->left);
    }
    
    // Helper function to search for a key
    Node* search(Node* root, string key) {
        if (root == nullptr || root->key == key) {
            return root;
        }
        
        if (key < root->key) {
            return search(root->left, key);
        } else {
            return search(root->right, key);
        }
    }
    
    // Helper function to delete a node
    Node* deleteNode(Node* root, string key) {
        if (root == nullptr) return root;
        
        // If key is smaller than root's key, go to left subtree
        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        }
        // If key is greater than root's key, go to right subtree
        else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        }
        // Key is same as root's key, so this node needs to be deleted
        else {
            // Node has only one child or no child
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            
            // Node with two children, get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }
    
    // Helper function to find the minimum value node
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

public:
    Dictionary() {
        root = nullptr;
    }

    // Function to create the dictionary by inserting nodes
    void createDictionary() {
        string key, meaning;
        char choice;
        
        do {
            cout << "Enter the word: ";
            cin >> key;
            cout << "Enter the meaning: ";
            cin.ignore();
            getline(cin, meaning);
            
            root = insert(root, key, meaning);
            
            cout << "Do you want to add more words? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
    }
    
    // Function to display the dictionary in ascending order
    void printAscending() {
        cout << "Dictionary in Ascending Order:\n";
        inorder(root);
    }
    
    // Function to display the dictionary in descending order
    void printDescending() {
        cout << "Dictionary in Descending Order:\n";
        descending_order(root);
    }
    
    // Function to search for a word
    void searchWord(string key) {
        Node* result = search(root, key);
        if (result != nullptr) {
            cout << key << ": " << result->meaning << endl;
        } else {
            cout << "Word not found!" << endl;
        }
    }
    
    // Function to delete a word
    void deleteWord(string key) {
        root = deleteNode(root, key);
        cout << key << " deleted from dictionary." << endl;
    }

    // Function to find the maximum comparisons required to search a word
    int maxComparisons() {
        return maxComparisonsHelper(root, 0);
    }
    
    // Helper function to find the maximum comparisons required
    int maxComparisonsHelper(Node* root, int depth) {
        if (root == nullptr) return depth;
        
        int leftDepth = maxComparisonsHelper(root->left, depth + 1);
        int rightDepth = maxComparisonsHelper(root->right, depth + 1);
        
        return max(leftDepth, rightDepth);
    }
};

int main() {
    Dictionary dict;
    
    dict.createDictionary();
    
    // Print dictionary in ascending order
    dict.printAscending();
    
    // Print dictionary in descending order
    dict.printDescending();
    
    // Search for a word
    string searchKey;
    cout << "Enter word to search: ";
    cin >> searchKey;
    dict.searchWord(searchKey);
    
    // Delete a word
    string deleteKey;
    cout << "Enter word to delete: ";
    cin >> deleteKey;
    dict.deleteWord(deleteKey);
    
    // Print the dictionary after deletion
    dict.printAscending();
    
    // Maximum comparisons for searching a word
    cout << "Maximum comparisons required: " << dict.maxComparisons() << endl;

    return 0;
}


Explanation - Here's a **line-by-line explanation** of **Assignment No. 5: Dictionary Operations Using a Binary Search Tree (BST)**:

---

### 🔷 **`struct Node`**

Defines a node of the binary search tree (BST) used for the dictionary:

```cpp
string key;        // The word (key) in the dictionary
string meaning;    // The meaning of the word (value)
Node* left;        // Pointer to the left child
Node* right;       // Pointer to the right child
```

The constructor initializes a node with a key (word) and its meaning. It also sets both left and right child pointers to `nullptr`.

---

### 🔷 **`class Dictionary`**

This class manages the dictionary operations using a **Binary Search Tree**.

#### **Private Member Functions**:

1. **`insert()`**:

   * **Recursive function** to insert a new word (key) and its meaning into the BST.
   * If the key is smaller than the current node’s key, it moves to the left; otherwise, it goes to the right.

2. **`inorder()`**:

   * **Recursive function** to traverse the BST in **ascending order** (in-order traversal).
   * It prints the words and their meanings in alphabetical order.

3. **`descending_order()`**:

   * **Recursive function** for **reverse in-order traversal** to display the dictionary in **descending order** (Z to A).
   * It prints the words and meanings in reverse alphabetical order.

4. **`search()`**:

   * **Recursive function** to search for a word in the BST.
   * If the key matches the node’s key, it returns the node; otherwise, it continues searching in the appropriate subtree.

5. **`deleteNode()`**:

   * **Recursive function** to delete a word from the dictionary.
   * It handles three cases:

     * Node has no children (leaf node).
     * Node has one child.
     * Node has two children (in this case, the **in-order successor** is used to replace the deleted node).

6. **`minValueNode()`**:

   * **Helper function** to find the **in-order successor** (smallest node) of a given node. It’s used in the `deleteNode()` function when deleting a node with two children.

7. **`maxComparisonsHelper()`**:

   * **Recursive function** to calculate the maximum depth (number of comparisons) required to search for any word in the tree.
   * The depth is the length of the longest path from the root to a leaf node.

#### **Public Member Functions**:

1. **`createDictionary()`**:

   * Accepts user input to create the dictionary by inserting new words and meanings into the BST.
   * It prompts the user to enter more words until they choose not to.

2. **`printAscending()`**:

   * Displays the dictionary in **ascending order** (alphabetical order) by calling `inorder()`.

3. **`printDescending()`**:

   * Displays the dictionary in **descending order** (reverse alphabetical order) by calling `descending_order()`.

4. **`searchWord()`**:

   * Searches for a word in the dictionary and displays its meaning if found.

5. **`deleteWord()`**:

   * Deletes a word from the dictionary and displays a confirmation message.

6. **`maxComparisons()`**:

   * Calls `maxComparisonsHelper()` to find the maximum number of comparisons required to find any word in the dictionary.

---

### 🔷 **`main()` Function**

The main function performs the following operations:

1. **Create Dictionary**: Prompts the user to input words and their meanings and builds the dictionary (BST).
2. **Display Dictionary in Ascending Order**: Calls `printAscending()` to print the words and meanings in alphabetical order.
3. **Display Dictionary in Descending Order**: Calls `printDescending()` to print the words and meanings in reverse alphabetical order.
4. **Search for a Word**: Prompts the user to search for a word and displays its meaning if found.
5. **Delete a Word**: Prompts the user to delete a word and confirms its deletion.
6. **Maximum Comparisons**: Displays the maximum number of comparisons needed to find any word in the dictionary.

---

### ✅ **Example Walkthrough**

1. **Input words** like "apple" with meaning "fruit", "banana" with meaning "yellow fruit", etc.
2. **Display** the dictionary in both ascending and descending order.
3. **Search for a word** like "apple" and view its meaning.
4. **Delete a word** like "banana" and confirm it’s deleted.
5. **Calculate the maximum comparisons** required for searching in the BST.

---

Questions -
Here are the oral questions with detailed answers based on your assignment:

---

### 1. **What are the properties of a Binary Search Tree (BST)?**

**Answer:**
A Binary Search Tree (BST) is a binary tree where:

* Each node has at most two children.
* For every node, the key in the left subtree is less than the node's key, and the key in the right subtree is greater than the node's key.
* Both left and right subtrees of every node must also be binary search trees.
  The major advantage of a BST is that it allows efficient searching, insertion, and deletion operations with a time complexity of O(log n) in a balanced tree.

---

### 2. **Explain the process of creating a dictionary using a Binary Search Tree.**

**Answer:**
To create a dictionary using a BST:

* Start by initializing an empty BST (with a root node as `nullptr`).
* Each keyword and its meaning are stored as a node in the BST.
* To add a new keyword, insert it into the tree by comparing the keyword's string to existing keywords in the tree.
* If the new keyword is less than the current node's keyword, move to the left child; if greater, move to the right.
* Continue this process recursively until the appropriate position is found, and then insert the new node.

---

### 3. **Describe the different types of tree traversals in a BST (Preorder, Inorder, Postorder).**

**Answer:**

* **Preorder Traversal**: Visit the current node, then recursively visit the left subtree and the right subtree. The order is: Root → Left → Right.
* **Inorder Traversal**: Recursively visit the left subtree, then the current node, and finally the right subtree. The order is: Left → Root → Right. This traversal is useful for printing the keys in ascending order for a BST.
* **Postorder Traversal**: Recursively visit the left subtree, the right subtree, and then the current node. The order is: Left → Right → Root. This is often used for deletion and cleanup operations.

---

### 4. **How do you insert a new node into a Binary Search Tree?**

**Answer:**
To insert a new node:

* Start at the root of the tree.
* Compare the key of the new node with the key of the current node.
* If the new node's key is smaller, move to the left child; if larger, move to the right child.
* Repeat this process recursively until you find a `nullptr` position, and insert the new node there.

---

### 5. **What is the difference between recursive and iterative search functions in a BST?**

**Answer:**

* **Recursive Search**: The search function is called recursively, where at each step, the left or right subtree is searched depending on the comparison result between the search key and the current node's key. It’s easier to implement but uses more stack space.
* **Iterative Search**: The search is performed iteratively using a loop. The tree is traversed using the left or right child based on comparisons, avoiding recursion and stack usage. It’s more space-efficient than recursion.

---

### 6. **How would you delete a node in a Binary Search Tree?**

**Answer:**
To delete a node from a BST:

1. **If the node has no children** (leaf node): Simply remove it.
2. **If the node has one child**: Remove the node and replace it with its only child.
3. **If the node has two children**: Find the node’s in-order predecessor or successor (the maximum node in the left subtree or minimum node in the right subtree), replace the node with this predecessor/successor, and delete the predecessor/successor recursively.

---

### 7. **What are the time complexities of searching and inserting nodes in a Binary Search Tree?**

**Answer:**

* **Searching**: The time complexity of searching in a BST is O(h), where h is the height of the tree. In a balanced tree, this is O(log n), but in the worst case (unbalanced tree), it becomes O(n).
* **Insertion**: The time complexity of insertion is also O(h), where h is the height of the tree. In a balanced tree, it’s O(log n), and in the worst case, it’s O(n) for an unbalanced tree.

---

### 8. **How do you display the entire dictionary in ascending or descending order using BST?**

**Answer:**

* **Ascending Order**: Use Inorder Traversal, which visits nodes in the order: Left → Root → Right. This will give the keys in ascending order.
* **Descending Order**: Perform a reverse Inorder Traversal, which visits nodes in the order: Right → Root → Left. This will give the keys in descending order.

---

### 9. **Describe a scenario where you would need to compare the lengths of the keys in a BST insertion operation.**

**Answer:**
When inserting keywords into a BST, comparing the lengths of the keys ensures that the comparison is performed correctly. If the keys differ in length, the shorter key may be compared based on lexicographical order, and the remaining characters of the longer key are ignored. This ensures that the BST structure is maintained.

---

### 10. **Explain how to find the maximum number of comparisons required when searching for a keyword in a BST.**

**Answer:**
The maximum number of comparisons occurs in the worst-case scenario, which is when the tree is unbalanced and resembles a linked list. In this case, each node has only one child. The maximum comparisons required would be equal to the height of the tree, which is O(n), where n is the number of nodes. For a balanced tree, the maximum comparisons are O(log n), where n is the number of nodes.

---

### 11. **Construct a Binary Search Tree for the following inputs: 22, 14, 18, 50, 9, 15, 7, 6, 12, 32, 25.**

**Answer:**
The tree construction follows this process:

1. Insert 22 (root).
2. Insert 14 (left of 22).
3. Insert 18 (right of 14).
4. Insert 50 (right of 22).
5. Insert 9 (left of 14).
6. Insert 15 (right of 14).
7. Insert 7 (left of 9).
8. Insert 6 (left of 7).
9. Insert 12 (right of 9).
10. Insert 32 (right of 50).
11. Insert 25 (left of 32).

The resulting BST structure looks like this:

```
         22
        /  \
      14    50
     /  \   /
    9   18 32
   / \     /
  7  15   25
 /
6
 \
  12
```

---

### 12. **What happens when inserting values into a Binary Search Tree in a non-random order?**

**Answer:**
If values are inserted into a BST in sorted or reverse-sorted order, the tree becomes unbalanced, with all nodes either going to the left or right, making it behave like a linked list. This increases the time complexity of search and insertion operations to O(n), which is inefficient compared to the O(log n) complexity in a balanced tree.

---

### 13. **What is the significance of balancing a Binary Search Tree, and how can it be achieved?**

**Answer:**
Balancing a BST ensures that the height of the tree is minimized, thus keeping the time complexity of operations like search, insert, and delete to O(log n). Techniques to balance a BST include:

* **AVL Tree**: A self-balancing BST where the balance factor (difference between the heights of left and right subtrees) is maintained.
* **Red-Black Tree**: A balanced BST that uses colors to ensure the tree remains balanced after each insertion or deletion.

---

### 14. **Can you implement an iterative version of the search function in a Binary Search Tree?**

**Answer:**
Yes, here is an example of an iterative search function:

```cpp
Node* iterativeSearch(Node* root, string key) {
    while (root != nullptr) {
        if (key == root->key) {
            return root;
        }
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return nullptr;
}
```

In this version, the search proceeds down the tree iteratively, checking left or right depending on the comparison with the current node’s key.

---

These answers should help you prepare for both the theoretical and practical aspects of your assignment.
