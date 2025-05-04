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
