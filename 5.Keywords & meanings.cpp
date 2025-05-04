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
