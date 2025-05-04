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
