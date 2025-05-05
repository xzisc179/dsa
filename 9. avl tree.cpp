ASSIGNMENT NO: 9
TITLE: IMPLEMENTATION OF AVL TREE
PROBLEM STATEMENT:
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords,
deleting keywords, updating values of any entry. Provide facility to display whole data sorted in
ascending/ Descending order. Also find how many maximum comparisons may require for finding any
keyword. Use Height balance tree and find the complexity for finding a keyword. (AVL Tree)



#include <iostream>
#include <string>
using namespace std;

struct AVLNode {
    string key, value;
    int height;
    AVLNode *left, *right;

    AVLNode(string k, string v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLNode *root;
    AVLTree() : root(nullptr) {}

    int height(AVLNode *node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode *node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode *y) {
        AVLNode *x = y->left;
        AVLNode *T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* rotateLeft(AVLNode *x) {
        AVLNode *y = x->right;
        AVLNode *T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* balance(AVLNode *node) {
        node->height = max(height(node->left), height(node->right)) + 1;
        int bf = balanceFactor(node);
        if (bf > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode* insert(AVLNode *node, string key, string value) {
        if (!node) return new AVLNode(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value;  // update value if key exists
        return balance(node);
    }

    AVLNode* findMin(AVLNode *node) {
        while (node && node->left) node = node->left;
        return node;
    }

    AVLNode* remove(AVLNode *node, string key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode *temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                AVLNode *temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
        }
        return balance(node);
    }

    void inorder(AVLNode *node) {
        if (!node) return;
        inorder(node->left);
        cout << "[" << node->key << ": " << node->value << "] ";
        inorder(node->right);
    }

    void reverseInorder(AVLNode *node) {
        if (!node) return;
        reverseInorder(node->right);
        cout << "[" << node->key << ": " << node->value << "] ";
        reverseInorder(node->left);
    }

    void displayAscending() {
        inorder(root);
        cout << endl;
    }

    void displayDescending() {
        reverseInorder(root);
        cout << endl;
    }

    bool search(AVLNode *node, string key, int &comparisons) {
        comparisons++;
        if (!node) return false;
        if (key == node->key) return true;
        if (key < node->key) return search(node->left, key, comparisons);
        return search(node->right, key, comparisons);
    }
};

int main() {
    AVLTree tree;
    int choice;
    do {
        cout << "\nDictionary Operations:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Value\n";
        cout << "4. Display in Ascending Order\n";
        cout << "5. Display in Descending Order\n";
        cout << "6. Search Keyword\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();  // to clear newline after integer input

        switch (choice) {
        case 1: {
            string key, value;
            cout << "Enter keyword: ";
            getline(cin, key);
            cout << "Enter meaning: ";
            getline(cin, value);
            tree.root = tree.insert(tree.root, key, value);
            break;
        }
        case 2: {
            string key;
            cout << "Enter keyword to delete: ";
            getline(cin, key);
            tree.root = tree.remove(tree.root, key);
            break;
        }
        case 3: {
            string key, value;
            cout << "Enter keyword to update: ";
            getline(cin, key);
            cout << "Enter new meaning: ";
            getline(cin, value);
            tree.root = tree.insert(tree.root, key, value);
            break;
        }
        case 4:
            tree.displayAscending();
            break;
        case 5:
            tree.displayDescending();
            break;
        case 6: {
            string key;
            int comparisons = 0;
            cout << "Enter keyword to search: ";
            getline(cin, key);
            if (tree.search(tree.root, key, comparisons))
                cout << "Keyword found with " << comparisons << " comparisons.\n";
            else
                cout << "Keyword not found after " << comparisons << " comparisons.\n";
            break;
        }
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
    } while (choice != 7);
    return 0;
}

Explanation - Sure! Let's go through each line of the code step by step to understand how it works.

### Header Files:

```cpp
#include <iostream>
#include <string>
using namespace std;
```

* **`#include <iostream>`**: Includes the standard input/output stream library to allow input and output operations such as `cin` and `cout`.
* **`#include <string>`**: Includes the string library to use the `string` class for handling strings (for the keywords and meanings).
* **`using namespace std;`**: This allows us to use standard C++ library functions and objects (like `cin`, `cout`, `string`, etc.) without having to prefix them with `std::`.

### AVL Node Structure:

```cpp
struct AVLNode {
    string key, value;
    int height;
    AVLNode *left, *right;

    AVLNode(string k, string v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};
```

* **`struct AVLNode`**: Defines a node structure for the AVL Tree. Each node contains:

  * `key`: A string representing the keyword (e.g., "apple").
  * `value`: A string representing the meaning of the keyword (e.g., "A fruit").
  * `height`: An integer to store the height of the node (used for balancing the tree).
  * `left`, `right`: Pointers to the left and right children of the node (i.e., the left and right subtrees).

* **Constructor `AVLNode(string k, string v)`**:

  * This initializes an `AVLNode` with the given keyword `k`, value `v`, sets the initial height to `1` (as new nodes have no children), and the `left` and `right` pointers to `nullptr` (indicating no children).

### AVLTree Class Definition:

```cpp
class AVLTree {
public:
    AVLNode *root;
    AVLTree() : root(nullptr) {}
```

* **`class AVLTree`**: Defines the AVL Tree class, which will manage the AVL Tree operations.
* **`AVLNode *root`**: A pointer to the root node of the AVL Tree.
* **Constructor `AVLTree()`**: Initializes the tree with `root` set to `nullptr`, indicating that the tree is empty initially.

### Helper Methods:

```cpp
    int height(AVLNode *node) {
        return node ? node->height : 0;
    }
```

* **`height(AVLNode *node)`**: Returns the height of a given node. If the node is not `nullptr`, it returns the node's height. If the node is `nullptr`, it returns `0`.

```cpp
    int balanceFactor(AVLNode *node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
```

* **`balanceFactor(AVLNode *node)`**: Calculates the balance factor of a node by subtracting the height of the right subtree from the height of the left subtree. The balance factor is used to determine if the tree is unbalanced.

```cpp
    AVLNode* rotateRight(AVLNode *y) {
        AVLNode *x = y->left;
        AVLNode *T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }
```

* **`rotateRight(AVLNode *y)`**: This function performs a right rotation around node `y`. A right rotation is used when the left subtree is too tall (left-heavy).

  * It makes `x` (the left child of `y`) the new root, and `y` becomes the right child of `x`.
  * The height of both nodes `x` and `y` is updated after the rotation.

```cpp
    AVLNode* rotateLeft(AVLNode *x) {
        AVLNode *y = x->right;
        AVLNode *T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }
```

* **`rotateLeft(AVLNode *x)`**: This function performs a left rotation around node `x`. A left rotation is used when the right subtree is too tall (right-heavy).

  * It makes `y` (the right child of `x`) the new root, and `x` becomes the left child of `y`.
  * The height of both nodes `x` and `y` is updated after the rotation.

```cpp
    AVLNode* balance(AVLNode *node) {
        node->height = max(height(node->left), height(node->right)) + 1;
        int bf = balanceFactor(node);
        if (bf > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
```

* **`balance(AVLNode *node)`**: Balances the tree by checking the balance factor of the given node. If the node is unbalanced, it performs the necessary rotations (right or left, or both).

  * If the balance factor is greater than 1 (left-heavy), it checks if the left child is also left-heavy (for a right rotation) or right-heavy (left-right rotation).
  * If the balance factor is less than -1 (right-heavy), it checks if the right child is also right-heavy (for a left rotation) or left-heavy (right-left rotation).
  * The function returns the balanced node.

### Insert and Remove Methods:

```cpp
    AVLNode* insert(AVLNode *node, string key, string value) {
        if (!node) return new AVLNode(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value;  // update value if key exists
        return balance(node);
    }
```

* **`insert(AVLNode *node, string key, string value)`**: Inserts a new node with the given `key` and `value` into the tree.

  * If the node is `nullptr`, it creates a new node.
  * If the `key` is less than the current node's key, it recursively inserts the key in the left subtree. If it's greater, it inserts in the right subtree.
  * If the `key` already exists, it updates the value.
  * After insertion, it balances the tree.

```cpp
    AVLNode* remove(AVLNode *node, string key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode *temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                AVLNode *temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
        }
        return balance(node);
    }
```

* **`remove(AVLNode *node, string key)`**: Removes a node with the specified `key` from the tree.

  * If the node has one or no children, it deletes the node and returns the child (if any).
  * If the node has two children, it finds the minimum node from the right subtree, replaces the current node with it, and deletes the original minimum node.
  * After removal, the tree is balanced.

### Display Methods:

```cpp
    void inorder(AVLNode *node) {
        if (!node) return;
        inorder(node->left);
        cout << "[" << node->key << ": " << node->value << "] ";
        inorder(node->right);
    }
```

* **`inorder(AVLNode *node)`**: Traverses the tree in in-order (ascending order) and prints each node's key and value.

  * It first visits the left subtree, then the current node, and finally the right subtree.

```cpp
    void reverseInorder(AVLNode *node) {
        if (!node) return;
        reverseInorder(node->right);
        cout << "[" << node->key << ": " << node->value << "] ";
        reverseInorder(node->left);
    }
```

* **`reverseInorder(AVLNode *node)`**: Traverses the tree in reverse in-order (descending order) and prints each node's key and value.

  * It first visits the right subtree, then the current node, and finally the left subtree.

### Search Method:

```cpp
    bool search(AVLNode *node, string key, int &comparisons) {
        comparisons++;
        if (!node) return false;
        if (key == node->key) return true;
        if (key < node->key) return search(node->left, key, comparisons);
        return search(node->right, key, comparisons);
    }
```

* **`search(AVLNode *node, string key, int &comparisons)`**: Searches for the given `key` in the tree and counts the number of comparisons made during the search.

  * It recursively searches the left or right subtree based on the comparison of the `key` with the current node's `key`.
  * The `comparisons` counter is incremented each time a comparison is made.

### Main Function:

```cpp
int main() {
    AVLTree tree;
    int choice;
    do {
        cout << "\nDictionary Operations:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Value\n";
        cout << "4. Display in Ascending Order\n";
        cout << "5. Display in Descending Order\n";
        cout << "6. Search Keyword\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();  // to clear newline after integer input
```

* **`int main()`**: The entry point of the program. It initializes an `AVLTree` object and provides a menu for the user to perform different operations.
* The **`do-while` loop** continuously displays the menu and performs the selected operation until the user chooses to exit.

The rest of the `main` function is responsible for handling user inputs, performing the corresponding tree operations (insertion, deletion, update, display, search), and displaying the results. Each case

    
Questions-    Here are 15 oral questions with answers related to the **AVL Tree** assignment:

---

### **1. What is an AVL Tree?**

**Answer:**
An AVL Tree is a self-balancing binary search tree where the difference in heights of the left and right subtrees of any node (called the balance factor) is at most 1. This ensures efficient operations like search, insert, and delete, all with a time complexity of $O(\log n)$.

---

### **2. What is the balance factor in an AVL Tree?**

**Answer:**
The balance factor of a node in an AVL tree is the difference between the height of its left subtree and the height of its right subtree. It is calculated as:

$$
\text{Balance Factor} = \text{Height(left subtree)} - \text{Height(right subtree)}
$$

A balance factor of -1, 0, or 1 indicates that the node is balanced. If the balance factor is outside this range, the tree needs to be rebalanced.

---

### **3. How do you determine if an AVL Tree is unbalanced?**

**Answer:**
An AVL tree is considered unbalanced if the balance factor of any node is greater than 1 or less than -1. This means the heights of the left and right subtrees of that node differ by more than 1, requiring a rotation to restore balance.

---

### **4. What are the four types of rotations in an AVL Tree?**

**Answer:**
The four types of rotations in an AVL Tree are:

* **Left Rotation (LL Rotation)**: Performed when the left subtree of the left child is taller.
* **Right Rotation (RR Rotation)**: Performed when the right subtree of the right child is taller.
* **Left-Right Rotation (LR Rotation)**: A combination of a left rotation followed by a right rotation, performed when the right child of the left subtree is taller.
* **Right-Left Rotation (RL Rotation)**: A combination of a right rotation followed by a left rotation, performed when the left child of the right subtree is taller.

---

### **5. Explain the process of a Left Rotation in an AVL Tree.**

**Answer:**
A left rotation is performed when the right subtree of a node is taller. In this operation, the node becomes the left child of its right child, and the right child of the node takes over as the new root of the subtree. The left child of the new root becomes the right child of the original node.

---

### **6. What happens during a Right Rotation in an AVL Tree?**

**Answer:**
A right rotation is performed when the left subtree of a node is taller. The node becomes the right child of its left child, and the left child of the node takes over as the new root of the subtree. The right child of the new root becomes the left child of the original node.

---

### **7. What is the Left-Right (LR) rotation?**

**Answer:**
The Left-Right (LR) rotation is a combination of a left rotation followed by a right rotation. It is performed when a node becomes unbalanced due to the right child of its left subtree being taller. First, a left rotation is applied on the left child, followed by a right rotation on the root.

---

### **8. What is the Right-Left (RL) rotation?**

**Answer:**
The Right-Left (RL) rotation is a combination of a right rotation followed by a left rotation. It is performed when a node becomes unbalanced due to the left child of its right subtree being taller. First, a right rotation is applied on the right child, followed by a left rotation on the root.

---

### **9. What is the height of an AVL Tree?**

**Answer:**
The height of an AVL tree is the length of the longest path from the root to any leaf node. The height is used to calculate the balance factor and to perform rotations when the tree becomes unbalanced.

---

### **10. What is the time complexity for searching a keyword in an AVL Tree?**

**Answer:**
The time complexity for searching a keyword in an AVL tree is $O(\log n)$, where $n$ is the number of nodes. This is because the tree remains balanced, and the search space is halved at each level, similar to binary search.

---

### **11. What is the worst-case time complexity for insertions and deletions in an AVL Tree?**

**Answer:**
The worst-case time complexity for both insertions and deletions in an AVL tree is $O(\log n)$. This is because even in the worst case, the tree is balanced and the operations involve traversing only the height of the tree, which is logarithmic.

---

### **12. Why is an AVL Tree better than a regular Binary Search Tree (BST)?**

**Answer:**
An AVL Tree is better than a regular BST because it maintains balance, ensuring that operations like search, insert, and delete are efficient with a time complexity of $O(\log n)$. In contrast, a regular BST can degrade to a linear structure, causing operations to take $O(n)$ time in the worst case.

---

### **13. How do you rebalance an AVL Tree after an insertion?**

**Answer:**
After an insertion in an AVL tree, the height of the affected node is updated, and the balance factor is calculated. If the balance factor becomes -2 or 2, rotations (left, right, left-right, or right-left) are performed to restore balance in the tree.

---

### **14. How do you perform the deletion of a keyword in an AVL Tree?**

**Answer:**
To delete a keyword from an AVL tree:

1. Perform the standard BST deletion for the keyword.
2. Update the height of the affected node.
3. Check the balance factor of the node and perform the necessary rotations (left, right, left-right, or right-left) to restore balance.

---

### **15. What is the significance of an AVL Tree in maintaining a dictionary of keywords and meanings?**

**Answer:**
An AVL Tree is ideal for maintaining a dictionary of keywords and meanings because it ensures efficient searching, insertion, and deletion of entries. The height-balancing property ensures that even as the dictionary grows, operations remain efficient with a logarithmic time complexity, providing fast access to keywords.

---

These questions and answers cover key concepts of AVL trees, including insertion, deletion, rotations, and the advantages of using AVL trees for maintaining a balanced dictionary. Let me know if you need further details or clarifications!
