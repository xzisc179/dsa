ASSIGNMENT NO: 8
TITLE : BUILD OPTIMAL BINARY SEARCH TREE
PROBLEM STATEMENT:
Given sequence k = k1 <k2 < … <kn of n sorted keys, with a search probability pi for each key ki. Build
the Binary search tree that has the least search cost given the access probability for each key? 



#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int sum(const vector<int> &freq, int i, int j) {
 int s = 0;
 for (int k = i; k <= j; k++) {
 s += freq[k];
 }
 return s;
}
int optimalBST(const vector<int> &keys, const
vector<int> &freq, int n) {
 vector<vector<int>> cost(n, vector<int>(n, 0));
 for (int i = 0; i < n; i++) {
 cost[i][i] = freq[i];
 }
 for (int length = 2; length <= n; length++) {
 for (int i = 0; i <= n - length; i++) {
 int j = i + length - 1;
 cost[i][j] = INT_MAX;
 for (int r = i; r <= j; r++) {
 int c = ((r > i) ? cost[i][r - 1] : 0) +
 ((r < j) ? cost[r + 1][j] : 0) +
 sum(freq, i, j);
 if (c < cost[i][j]) {
 cost[i][j] = c;
 }
 }
 }
 }
 return cost[0][n - 1];
}
int main() {
 int n;
 cout << "Enter number of keys: ";
 cin >> n;
 vector<int> keys(n), freq(n);
 cout << "Enter keys: ";
 for (int i = 0; i < n; i++) {
 cin >> keys[i];
 }
 cout << "Enter frequencies: ";
 for (int i = 0; i < n; i++) {
 cin >> freq[i];
 }
 int minCost = optimalBST(keys, freq, n);
 cout << "Minimum search cost for Optimal BST: " <<
minCost << endl;
 return 0;
}


explanation - Let's break down the code step by step to understand the process of constructing an optimal binary search tree (BST) for the given sorted keys and their search probabilities.

### Explanation of the Code:

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
```

* This includes the necessary header files:

  * `<iostream>`: For input and output operations.
  * `<vector>`: To use the vector container for dynamic arrays.
  * `<climits>`: To use constants like `INT_MAX`, which is used to represent infinity.

```cpp
int sum(const vector<int> &freq, int i, int j) {
    int s = 0;
    for (int k = i; k <= j; k++) {
        s += freq[k];
    }
    return s;
}
```

* **`sum` function**: This function calculates the sum of the search frequencies from index `i` to index `j` in the `freq` array.
* It iterates over the range `[i, j]` and sums up the frequencies of the keys that are between those indices.

```cpp
int optimalBST(const vector<int> &keys, const vector<int> &freq, int n) {
    vector<vector<int>> cost(n, vector<int>(n, 0));
```

* **`optimalBST` function**: This function calculates the minimum cost of constructing the optimal binary search tree (BST).
* `cost` is a 2D vector (table) where `cost[i][j]` will store the minimum cost of constructing a BST with keys from index `i` to `j`.

```cpp
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
    }
```

* Here, the diagonal elements `cost[i][i]` are initialized to the frequency of the respective key `freq[i]`. This represents the cost of a BST with just one key, which is simply the frequency of accessing that key.

```cpp
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            cost[i][j] = INT_MAX;
```

* **Dynamic Programming Step**:

  * This is the main loop that calculates the minimum cost for all subtrees of increasing length.
  * `length` represents the size of the subtree (from 2 to `n` keys).
  * The outer loop iterates over all possible starting indices `i` for subtrees of that length.
  * `j` is the ending index for that subtree (since the subtree has a length of `length`, it ends at `i + length - 1`).
  * `cost[i][j]` is initialized to `INT_MAX` to ensure we find the minimum cost in the next step.

```cpp
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) +
                        sum(freq, i, j);
```

* This inner loop iterates over all possible roots `r` for the subtree starting at `i` and ending at `j`. Each key can be the root of the subtree.

  * If `r > i`, the cost of the left subtree is `cost[i][r - 1]`.
  * If `r < j`, the cost of the right subtree is `cost[r + 1][j]`.
  * The `sum(freq, i, j)` calculates the sum of frequencies from `i` to `j`, which is the cost of accessing the keys in this range.

```cpp
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                }
            }
        }
    }
```

* For each root `r`, we calculate the total cost of the subtree and check if it's less than the current value stored in `cost[i][j]`. If it is, we update `cost[i][j]` with the new minimum value.

```cpp
    return cost[0][n - 1];
}
```

* After completing the calculations, the minimum search cost for the entire tree (with all keys from 0 to `n-1`) will be stored in `cost[0][n-1]`.

```cpp
int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;
    vector<int> keys(n), freq(n);
    cout << "Enter keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    cout << "Enter frequencies: ";
    for (int i = 0; i < n; i++) {
        cin >> freq[i];
    }
    int minCost = optimalBST(keys, freq, n);
    cout << "Minimum search cost for Optimal BST: " << minCost << endl;
    return 0;
}
```

* **Main function**:

  * It starts by asking for the number of keys `n`.
  * Then, it takes input for the sorted keys (`keys`) and their respective search frequencies (`freq`).
  * It calls the `optimalBST` function to calculate the minimum search cost for the optimal binary search tree.
  * Finally, it outputs the result.

### Key Concepts:

* **Dynamic Programming**: The code uses a bottom-up dynamic programming approach to solve the problem. It builds up the solution by considering smaller subproblems and using their solutions to solve larger problems.
* **Optimal Substructure**: The optimal solution for a problem (minimum search cost of a BST) can be constructed from the optimal solutions of smaller subproblems (subtrees).
* **Overlapping Subproblems**: The same subproblems (costs for subtrees) are computed multiple times, so storing the solutions in a table avoids recomputation.

### Example:

If the keys are `[10, 20, 30]` with corresponding frequencies `[34, 8, 50]`, the function calculates the minimum search cost for the optimal BST based on these keys and frequencies.

The dynamic programming approach efficiently computes the optimal solution for the minimum search cost, which minimizes the overall time complexity of the problem.

Questions -
Here are 10-15 questions with answers related to the **Optimal Binary Search Tree (OBST)** assignment:

### **1. What is an Optimal Binary Search Tree (OBST)?**

**Answer:**
An Optimal Binary Search Tree (OBST) is a binary search tree that minimizes the total expected search cost for a set of keys, given their respective access probabilities. It is designed to ensure that the most frequently accessed keys are placed closer to the root to minimize the search time.

---

### **2. How is the search cost calculated in an Optimal Binary Search Tree?**

**Answer:**
The search cost in an OBST is calculated by multiplying the depth of each key by its probability and summing this for all keys.

$$
\text{Cost}(T) = \sum_{i=0}^{n-1} p_i \times d_i
$$

where $p_i$ is the probability of key $k_i$, and $d_i$ is the depth of $k_i$ in the tree.

---

### **3. What is the role of dynamic programming in constructing an OBST?**

**Answer:**
Dynamic programming helps break down the problem of constructing an OBST into smaller subproblems. It calculates the minimum search cost for every possible subtree and stores the results in a table to avoid redundant calculations, leading to an optimal solution.

---

### **4. What is the recursive relation used in dynamic programming for OBST?**

**Answer:**
The recursive relation is:

$$
e[i, j] = \min_{i \leq r \leq j} \left( e[i, r-1] + e[r+1, j] + \sum_{k=i}^{j} p_k \right)
$$

where $e[i, j]$ is the minimum expected cost for the subtree formed by keys $k_i$ to $k_j$, and the root $k_r$ is chosen to minimize the cost.

---

### **5. What is the base case for the dynamic programming approach in OBST?**

**Answer:**
The base case is when there is only one key, i.e., $i = j$, where the cost is simply the probability of that key:

$$
e[i, i] = p_i
$$

---

### **6. How is the root of a subtree selected in OBST?**

**Answer:**
The root of a subtree is selected by choosing the key that minimizes the expected search cost. This is done by iterating over all possible roots and selecting the one that gives the smallest sum of costs for the left and right subtrees.

---

### **7. What is the role of the root matrix $R[i, j]$ in OBST?**

**Answer:**
The root matrix $R[i, j]$ stores the index of the root for each subtree. This helps in reconstructing the OBST after calculating the optimal costs for all subtrees.

---

### **8. What is the weight matrix $W[i, j]$ used for in OBST?**

**Answer:**
The weight matrix $W[i, j]$ stores the sum of the probabilities for keys between $k_i$ and $k_j$, which is used to calculate the expected cost for the subtree. It helps avoid redundant calculations of the sum of probabilities for every subproblem.

---

### **9. How is the final OBST reconstructed once the dynamic programming tables are filled?**

**Answer:**
Once the tables are filled, the root of the entire tree is found in $R[0, n-1]$. The left and right subtrees are recursively reconstructed by referring to the root matrix $R$ and the corresponding subarrays.

---

### **10. Can an OBST be constructed without dynamic programming? If so, how?**

**Answer:**
An OBST can be constructed without dynamic programming using a brute-force approach. In this method, all possible binary search trees are generated, and the cost of each is computed. The tree with the minimum cost is selected. However, this method is inefficient, especially for larger input sizes, as the number of trees grows exponentially.

---

### **11. What is the time complexity of constructing an OBST using dynamic programming?**

**Answer:**
The time complexity of constructing an OBST using dynamic programming is $O(n^3)$, where $n$ is the number of keys. This is because we calculate the cost for all possible pairs of keys and for all possible roots in each pair.

---

### **12. What is the space complexity of constructing an OBST using dynamic programming?**

**Answer:**
The space complexity is $O(n^2)$, as we need to store the dynamic programming tables for expected costs, weights, and roots, all of which are of size $n \times n$.

---

### **13. How does the OBST algorithm ensure that the tree is balanced?**

**Answer:**
The OBST algorithm doesn't necessarily produce a perfectly balanced tree. Instead, it minimizes the search cost by ensuring that frequently accessed keys are closer to the root. This could lead to an unbalanced tree, but with the lowest possible search cost for the given probabilities.

---

### **14. What happens if all the keys in OBST have the same probability?**

**Answer:**
If all the keys have the same probability, the OBST will be a balanced binary search tree. The search cost will be the same for all keys, and the tree is constructed by placing the root at the middle of the array to ensure balance.

---

### **15. What is the main difference between a regular Binary Search Tree (BST) and an Optimal Binary Search Tree (OBST)?**

**Answer:**
The main difference is that an OBST is constructed to minimize the expected search cost based on access probabilities, while a regular BST is built based on the order of insertion or key comparisons. OBST optimizes the placement of nodes based on frequency, leading to a more efficient search.

---

These questions cover key concepts related to OBST and its construction using dynamic programming. Let me know if you'd like further clarification on any point!
