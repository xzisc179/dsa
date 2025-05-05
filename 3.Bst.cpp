ASSIGNMENT NO: 3
TITLE: TO STUDY BST AND OPERATIONS ON IT.
PROBLEM STATEMENT: -
Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the
order given.
After constructing a binary tree -
i. Insert new node
ii. Find number of nodes in longest path
iii. Minimum data value found in the tree
iv. Change a tree so that the roles of the left and right pointers are swapped at every node
v. Search a value 


#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

bool search(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->data == value) return true;
    if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

int findMin(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return -1;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root->data;
}

int longestPath(Node* root) {
    if (root == nullptr) return 0;
    int leftHeight = longestPath(root->left);
    int rightHeight = longestPath(root->right);
    return max(leftHeight, rightHeight) + 1;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void mirror(Node* root) {
    if (root == nullptr) return;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

int main() {
    Node* root = nullptr;
    int n, value;

    cout << "Enter number of elements: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> value;
        root = insert(root, value);
    }

    cout << "\nInorder traversal: ";
    inorder(root);
    cout << endl;

    int key;
    cout << "Enter value to search: ";
    cin >> key;
    if (search(root, key))
        cout << key << " is found" << endl;
    else
        cout << key << " is not found" << endl;

    cout << "Minimum value in BST: " << findMin(root) << endl;

    mirror(root);
    cout << "Inorder traversal after mirroring: ";
    inorder(root);
    cout << endl;

    cout << "Length of the longest path: " << longestPath(root) << endl;

    return 0;
}


Explanation -Here’s a **line-by-line explanation** of **Assignment No. 3: Binary Search Tree (BST) and Operations**, written in C++:

---

### 🔷 **`struct Node`**

Defines a node in the BST:

```cpp
int data;        // holds value
Node* left;      // pointer to left child
Node* right;     // pointer to right child
```

The constructor initializes a node with a value and sets both child pointers to `nullptr`.

---

### 🔷 **`insert()` Function**

Recursive function to **insert a new node** into the BST:

* If `root` is `nullptr`, create a new node.
* If value < root’s data → insert in left subtree.
* Otherwise → insert in right subtree.

---

### 🔷 **`search()` Function**

Recursively checks if a value exists in the tree:

* Base case: `nullptr` → return false
* Match → return true
* Go left or right based on comparison

---

### 🔷 **`findMin()` Function**

Finds the **smallest value** by going leftmost in the tree.

---

### 🔷 **`longestPath()` Function**

Returns the **length of the longest path** (height of the tree):

* Recursively gets the height of left and right subtree
* Returns the greater height + 1

---

### 🔷 **`inorder()` Function**

Performs an **in-order traversal** (Left → Root → Right).

---

### 🔷 **`mirror()` Function**

**Swaps left and right children** of every node recursively to create a **mirror image** of the tree.

---

### 🔷 **`main()` Function**

1. Takes input `n` = number of nodes
2. Accepts `n` values and inserts them into BST
3. Displays inorder traversal
4. Asks for a value to search
5. Shows if value is found
6. Displays **minimum value**
7. Performs **mirror operation**
8. Displays new inorder traversal
9. Displays **longest path length**

---

### ✅ **Example Output Walkthrough**

For input: `50, 30, 70, 20, 40, 60, 80`

* Inorder before mirroring: `20 30 40 50 60 70 80`
* Inorder after mirroring: `80 70 60 50 40 30 20`
* Min value: `20`
* Longest path: `3`

---

Questions - 
    ✅ Assignment No. 3 Oral Questions with Answers
Title: To study BST and operations on it

🔹 Basic Understanding
Q1. What is a Binary Search Tree (BST)?
A: A BST is a binary tree where each node has a key such that:

All keys in the left subtree are less than the node’s key.

All keys in the right subtree are greater than the node’s key.

This property is recursively true for all nodes.

Q2. How is a BST constructed from a list of values?
A: Starting with an empty tree, each value is inserted one by one following BST insertion rules: compare with the root, move left or right accordingly, and insert at the appropriate position.

Q3. What is the time complexity of insertion in a BST?
A:

Best/Average case: O(log n) (when tree is balanced)

Worst case: O(n) (when tree becomes skewed)

🔹 Operations-Based Questions
Q4. How do you insert a new node in a BST?
A: Start from the root, compare the key with the current node, and recursively go left or right until an appropriate null spot is found to insert the new node.

Q5. How do you find the number of nodes in the longest path?
A: This is equivalent to finding the height of the BST, which is the length of the longest path from the root to a leaf node. Use recursion to calculate it.

Q6. How do you find the minimum data value in a BST?
A: The minimum value is always located at the leftmost node of the BST.

Q7. How do you swap left and right pointers at every node?
A: This operation is called mirroring or inversion of the tree. It can be done using postorder traversal and recursively swapping the left and right pointers at each node.

Q8. How do you search a value in BST?
A: Start at the root and compare the target value:

If equal → found.

If less → search in the left subtree.

If greater → search in the right subtree.
Repeat until the value is found or the node becomes null.

🔹 Additional Questions
Q9. What is the space complexity of BST operations?
A:

Space for recursion (call stack): O(h), where h is the height of the tree.

For balanced trees: O(log n); for skewed trees: O(n)

Q10. Can duplicate values be inserted into a BST?
A: Usually no, but some implementations allow them either on the left or right. Standard BSTs do not support duplicates.

Q11. What are the traversal techniques in BST?
A:

Inorder (LNR): gives sorted order.

Preorder (NLR) and Postorder (LRN): used for copying or deleting the tree.

Q12. What are some real-world applications of BST?
A:

Searching and sorting

Symbol tables in compilers

Database indexing

Implementing dynamic sets and lookup tables

