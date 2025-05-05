ASSIGNMENT NO: 6
TITLE: IMPLEMENTATION OF GRAPH DATA STRUCTURES
PROBLEM STATEMENT:
There are flight paths between cities. If there is a flight between city A and city B then there is an edge
between the cities. The cost of the edge can be the time that flight takes to reach city B from A, or the
amount of fuel used for the journey. Represent this as a graph. The node can be represented by airport name
or name of the city. Use adjacency list representation of the graph or use adjacency matrix representation of
the graph. Check whether the graph is connected or not. Justify the storage representation used. 

#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

int adj_mat[50][50] = {0};
int visited[50] = {0};

void dfs(int s, int n, string arr[]) {
    visited[s] = 1;
    cout << arr[s] << " ";
    for (int i = 0; i < n; i++) {
        if (adj_mat[s][i] && !visited[i])
            dfs(i, n, arr);
    }
}

void bfs(int s, int n, string arr[]) {
    bool visited[n] = {false};
    int v;
    queue<int> bfsq;
    cout << arr[s] << " ";
    bfsq.push(s);
    visited[s] = true;
    while (!bfsq.empty()) {
        v = bfsq.front();
        bfsq.pop();
        for (int i = 0; i < n; i++) {
            if (adj_mat[v][i] && !visited[i]) {
                cout << arr[i] << " ";
                visited[i] = true;
                bfsq.push(i);
            }
        }
    }
}

int main() {
    cout << "Enter number of cities: ";
    int n, u;
    cin >> n;
    string cities[n];

    // Input city names
    for (int i = 0; i < n; i++) {
        cout << "Enter city #" << i + 1 << " (Airport Code): ";
        cin >> cities[i];
    }

    cout << "\nYour cities are:\n";
    for (int i = 0; i < n; i++) {
        cout << "City #" << i + 1 << ": " << cities[i] << endl;
    }

    // Input distance between cities
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Enter distance between " << cities[i] << " and " << cities[j] << ": ";
            cin >> adj_mat[i][j];
            adj_mat[j][i] = adj_mat[i][j]; // Since it's an undirected graph
        }
    }

    // Display adjacency matrix
    cout << "\nAdjacency Matrix (Distance between cities):\n";
    cout << setw(10) << " ";
    for (int i = 0; i < n; i++) {
        cout << setw(10) << cities[i];
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(10) << cities[i];
        for (int j = 0; j < n; j++) {
            cout << setw(10) << adj_mat[i][j];
        }
        cout << endl;
    }

    // Get starting city index
    cout << "Enter Starting City Index (0 to " << n - 1 << "): ";
    cin >> u;

    // Perform DFS and BFS
    cout << "DFS: ";
    dfs(u, n, cities);
    cout << endl;

    cout << "BFS: ";
    bfs(u, n, cities);
    cout << endl;

    return 0;
}

Explanation-Let's break down each line of the code to understand how it works step by step.

### **Include Headers:**

```cpp
#include <iostream>
#include <queue>
#include <iomanip>
```

* `#include <iostream>`: This header allows input and output operations such as `cin` and `cout`.
* `#include <queue>`: This header is included for using the `queue` container, which is used in BFS for storing the cities that need to be visited.
* `#include <iomanip>`: This is included to control the formatting of output (like setting the width of the output for better display of the adjacency matrix).

### **Global Variables:**

```cpp
int adj_mat[50][50] = {0};   // Adjacency matrix to store distances between cities
int visited[50] = {0};        // Array to keep track of visited cities
```

* `adj_mat[50][50]`: A 2D array that stores the adjacency matrix of the graph. Each cell `adj_mat[i][j]` contains the distance (or cost) between city `i` and city `j`. The matrix size is fixed at 50 cities.
* `visited[50]`: A 1D array used to mark whether a city has been visited during DFS or BFS. Initially, all cities are unvisited.

### **DFS Function:**

```cpp
void dfs(int s, int n, string arr[]) {
    visited[s] = 1;                   // Mark the starting city as visited
    cout << arr[s] << " ";            // Print the name of the city
    for (int i = 0; i < n; i++) {    // Loop through all cities to find connected ones
        if (adj_mat[s][i] && !visited[i])  // If there's a flight and the city hasn't been visited
            dfs(i, n, arr);                // Recursively call DFS for that city
    }
}
```

* **`visited[s] = 1;`**: Marks the starting city `s` as visited.
* **`cout << arr[s] << " ";`**: Prints the name of the city `s` (using the `arr[]` array which contains city names).
* **`for (int i = 0; i < n; i++)`**: Iterates through all cities to find if there's a flight to any other city.
* **`if (adj_mat[s][i] && !visited[i])`**: Checks if there’s a flight between cities `s` and `i`, and if city `i` has not been visited.
* **`dfs(i, n, arr);`**: If a city is connected and not visited, the function recursively calls `dfs` for that city.

### **BFS Function:**

```cpp
void bfs(int s, int n, string arr[]) {
    bool visited[n] = {false};   // Array to keep track of visited cities in BFS
    int v;                       // Variable to store the current city being processed
    queue<int> bfsq;             // Queue to store cities for BFS traversal
    cout << arr[s] << " ";       // Print the starting city
    bfsq.push(s);                // Add the starting city to the queue
    visited[s] = true;           // Mark the starting city as visited
    while (!bfsq.empty()) {      // Continue until all cities are visited
        v = bfsq.front();        // Get the front city from the queue
        bfsq.pop();              // Remove that city from the queue
        for (int i = 0; i < n; i++) {   // Loop through all cities
            if (adj_mat[v][i] && !visited[i]) {   // If there's a flight and city hasn't been visited
                cout << arr[i] << " ";  // Print the city name
                visited[i] = true;     // Mark it as visited
                bfsq.push(i);         // Add city to the queue
            }
        }
    }
}
```

* **`bool visited[n] = {false};`**: Creates an array to track visited cities during BFS.
* **`queue<int> bfsq;`**: A queue is used to store the cities that need to be visited next in BFS.
* **`cout << arr[s] << " ";`**: Prints the starting city name.
* **`bfsq.push(s);`**: Adds the starting city to the queue.
* **`visited[s] = true;`**: Marks the starting city as visited.
* **`while (!bfsq.empty())`**: Loops while the queue has cities to visit.
* **`v = bfsq.front(); bfsq.pop();`**: Retrieves and removes the city at the front of the queue.
* **`for (int i = 0; i < n; i++)`**: Loops through all cities to find unvisited neighbors.
* **`bfsq.push(i);`**: Adds an unvisited neighboring city to the queue.

### **Main Function:**

```cpp
int main() {
    cout << "Enter number of cities: ";
    int n, u;
    cin >> n;   // Input the number of cities
    string cities[n];   // Array to store the names of the cities

    // Input city names
    for (int i = 0; i < n; i++) {
        cout << "Enter city #" << i + 1 << " (Airport Code): ";
        cin >> cities[i];   // Store city name (airport code) in cities array
    }

    cout << "\nYour cities are:\n";
    for (int i = 0; i < n; i++) {
        cout << "City #" << i + 1 << ": " << cities[i] << endl;   // Display city names
    }

    // Input distance between cities
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Enter distance between " << cities[i] << " and " << cities[j] << ": ";
            cin >> adj_mat[i][j];   // Input distance (edge cost) between cities
            adj_mat[j][i] = adj_mat[i][j];  // Since it's an undirected graph, mirror the value
        }
    }

    // Display adjacency matrix
    cout << "\nAdjacency Matrix (Distance between cities):\n";
    cout << setw(10) << " ";  // Set the width for alignment of matrix columns
    for (int i = 0; i < n; i++) {
        cout << setw(10) << cities[i];  // Display city names along the top
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(10) << cities[i];   // Display city names along the left
        for (int j = 0; j < n; j++) {
            cout << setw(10) << adj_mat[i][j];   // Display the corresponding distance in the matrix
        }
        cout << endl;
    }

    // Get starting city index
    cout << "Enter Starting City Index (0 to " << n - 1 << "): ";
    cin >> u;   // Input the index of the starting city

    // Perform DFS and BFS
    cout << "DFS: ";
    dfs(u, n, cities);   // Call DFS function to perform depth-first search
    cout << endl;

    cout << "BFS: ";
    bfs(u, n, cities);   // Call BFS function to perform breadth-first search
    cout << endl;

    return 0;
}
```

* **`int n, u;`**: Declares variables `n` (number of cities) and `u` (starting city index).
* **`cin >> n;`**: Takes input for the number of cities.
* **`string cities[n];`**: Creates an array `cities[]` to store the names of cities.
* **`cin >> cities[i];`**: For each city, the name (airport code) is inputted and stored in the `cities[]` array.
* **`for (int i = 0; i < n; i++)`**: Displays the names of all the cities entered.
* **`cin >> adj_mat[i][j];`**: For each pair of cities `(i, j)`, the distance (or flight time) is inputted and stored in the adjacency matrix. The distance is mirrored because it's an undirected graph.
* **`cout << setw(10)`**: This ensures proper formatting and alignment of the output in the adjacency matrix.
* **`cin >> u;`**: Takes the starting city index as input.
* **`dfs(u, n, cities);`**: Performs DFS traversal starting from the city `u`.
* **`bfs(u, n, cities);`**: Performs BFS traversal starting from the city `u`.

### **Final Output**:

* **Adjacency Matrix**: Displays the distance between each pair of cities.
* **DFS and BFS Traversal**: Outputs the cities visited in DFS and BFS order starting from the user-provided city index.

---

Questions -
### Oral Questions with Answers

---

#### 1. **Define Graph?**

**Answer**:
A **graph** is a non-linear data structure consisting of a set of **vertices (nodes)** connected by **edges (arcs)**. It represents pairwise relationships between objects. In a graph, vertices are the points and edges are the connections between them. Graphs can be classified into **directed** (edges have a direction) and **undirected** (edges do not have a direction).

---

#### 2. **Explain Breadth-First Search (BFS) traversal of a Graph using an example.**

**Answer**:
**Breadth-First Search (BFS)** is an algorithm for traversing or searching tree or graph data structures. It starts at the root (or any arbitrary node) and explores all the neighbor nodes at the present depth prior to moving on to nodes at the next depth level. It uses a **queue** for implementation.

**Example**: Consider the graph:

```
1 - 2 - 3
|   |
4 - 5
```

BFS traversal starting from vertex 1 will visit nodes in the order: **1 → 2 → 4 → 3 → 5**.

* Start from vertex 1, visit it.
* Visit all adjacent nodes of vertex 1 (i.e., 2 and 4).
* Then move to the next level and visit nodes adjacent to 2 (i.e., 3 and 5).

**Time Complexity**: O(V + E), where V is the number of vertices and E is the number of edges.

---

#### 3. **Explain Depth-First Search (DFS) traversal of a Graph using an example.**

**Answer**:
**Depth-First Search (DFS)** is an algorithm for traversing or searching tree or graph data structures. It starts at the root (or any arbitrary node) and explores as far as possible along each branch before backing up. DFS uses a **stack** (can be implemented using recursion) to store vertices.

**Example**: Consider the graph:

```
1 - 2 - 3
|   |
4 - 5
```

DFS traversal starting from vertex 1 will visit nodes in the order: **1 → 2 → 3 → 5 → 4**.

* Start from vertex 1, visit it.
* Move to vertex 2, then explore vertex 3, then backtrack to vertex 5, and then explore vertex 4.

**Time Complexity**: O(V + E), where V is the number of vertices and E is the number of edges.

---

#### 4. **Discuss the following with reference to graphs:**

**(i) Directed Graph**
**Answer**:
A **directed graph** (or **digraph**) is a graph in which edges have a direction. Each edge has a starting vertex (source) and an ending vertex (destination), representing a one-way relationship between the two vertices. The direction of an edge is important, as it signifies a one-way flow of information or control.

**(ii) Undirected Graph**
**Answer**:
An **undirected graph** is a graph where the edges have no direction. The relationship between two vertices is mutual. In an undirected graph, if there is an edge between vertex A and vertex B, it means both A and B are connected in both directions.

**(iii) Degree of Vertex**
**Answer**:
The **degree** of a vertex in a graph is the number of edges incident to it. In an undirected graph, the degree is simply the count of edges connecting to the vertex. In a directed graph, we distinguish between **in-degree** (edges directed into the vertex) and **out-degree** (edges directed out of the vertex).

**(iv) Null Graph**
**Answer**:
A **null graph** is a graph that has no edges. It contains only isolated vertices with no connections between them. It is a trivial type of graph.

**(v) Acyclic Graph**
**Answer**:
An **acyclic graph** is a graph that does not contain any cycles (i.e., a path that begins and ends at the same vertex). A **Directed Acyclic Graph (DAG)** is a type of directed graph that has no cycles. Acyclic graphs are commonly used in scheduling problems and data processing pipelines.

---

#### 5. **Explain the difference between Adjacency Matrix and Adjacency List for graph representation.**

**Answer**:

* **Adjacency Matrix**:
  An adjacency matrix is a 2D array where each element indicates whether a pair of vertices is connected by an edge. For a graph with n vertices, the adjacency matrix has dimensions n × n.

  * **Space Complexity**: O(V²), where V is the number of vertices.
  * **Use Case**: It is efficient for dense graphs where most pairs of vertices are connected.

* **Adjacency List**:
  An adjacency list represents a graph as an array or list of lists. Each vertex has a list that stores all the vertices that it is directly connected to.

  * **Space Complexity**: O(V + E), where V is the number of vertices and E is the number of edges.
  * **Use Case**: It is more space-efficient for sparse graphs where few edges exist between vertices.

---

#### 6. **What is the time complexity of DFS and BFS traversals?**

**Answer**:
Both **Depth-First Search (DFS)** and **Breadth-First Search (BFS)** have the same time complexity:

* **Time Complexity**: O(V + E), where V is the number of vertices and E is the number of edges.

This is because in both algorithms, each vertex and edge is visited exactly once.

---

#### 7. **What is the space complexity of DFS and BFS traversals?**

**Answer**:

* **DFS**:
  Space complexity is O(V) due to the recursive stack used for DFS. In the worst case, the recursion stack can go as deep as the number of vertices (for example, in a skewed graph).

* **BFS**:
  Space complexity is O(V) as well, due to the queue used in BFS to keep track of the vertices to visit next.

---

These oral questions and answers cover fundamental concepts of graph theory, graph traversals, and graph representations. You can use these answers for better understanding or during exams. Let me know if you'd like more details!
