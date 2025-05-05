ASSIGNMENT NO: 7
TITLE: MINIMUM SPANNING TREE (MST)
PROBLEM STATEMENT:
You have a business with several offices; you want to lease phone lines to connect them up with each other;
and the phone company charges different amounts of money to connect different pairs of cities. You want a
set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting
appropriate data structures



#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <unordered_map>
using namespace std;

struct Edge {
    int destination;
    int cost;
};

class Graph {
public:
    vector<string> cities;
    unordered_map<string, int> cityIndex;  // Map city name to index for easier access
    vector<vector<Edge>> adjList;

    Graph(int numCities) {
        adjList.resize(numCities);
    }

    void addCity(const string& city) {
        cities.push_back(city);
        cityIndex[city] = cities.size() - 1;
    }

    void addEdge(const string& city1, const string& city2, int cost) {
        int city1Index = cityIndex[city1];
        int city2Index = cityIndex[city2];
        adjList[city1Index].push_back({city2Index, cost});
        adjList[city2Index].push_back({city1Index, cost});
    }

    void primMST() {
        int numCities = cities.size();
        vector<int> key(numCities, INT_MAX);
        vector<int> parent(numCities, -1);
        vector<bool> inMST(numCities, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        key[0] = 0;  // Start with city 0
        pq.push({0, 0});  // {cost, city}

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;  // Skip if city is already in MST
            inMST[u] = true;

            for (const auto& edge : adjList[u]) {
                int v = edge.destination;
                int cost = edge.cost;

                // If city v is not in MST and cost is smaller than key[v]
                if (!inMST[v] && cost < key[v]) {
                    key[v] = cost;
                    pq.push({cost, v});
                    parent[v] = u;
                }
            }
        }

        printMST(parent, key);
    }

    void printMST(const vector<int>& parent, const vector<int>& key) {
        cout << "Edge\t\tWeight\n";
        int totalCost = 0;
        for (int i = 1; i < parent.size(); i++) {
            cout << cities[parent[i]] << " - " << cities[i] << "\t" << key[i] << "\n";
            totalCost += key[i];
        }
        cout << "Total minimum cost: " << totalCost << endl;
    }
};

int main() {
    int numCities;
    cout << "Enter number of cities: ";
    cin >> numCities;

    Graph g(numCities);

    // Input cities
    cout << "Enter the names of the cities:\n";
    for (int i = 0; i < numCities; i++) {
        string city;
        cout << "City " << i + 1 << ": ";
        cin >> city;
        g.addCity(city);
    }

    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    // Input edges and their costs
    cout << "Enter the edges in the format (city1 city2 cost):\n";
    for (int i = 0; i < numEdges; i++) {
        string city1, city2;
        int cost;
        cout << "Edge " << i + 1 << ": ";
        cin >> city1 >> city2 >> cost;
        g.addEdge(city1, city2, cost);
    }

    g.primMST();

    return 0;
}









#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;
struct Edge {
int destination;
int cost;
};
class Graph {
public:
vector<string> cities = {"Mumbai", "Bengaluru", "Chennai", "Jaipur", "Pune", "Hyderabad"};
vector<vector<Edge>> adjList;
Graph(int numCities) {
adjList.resize(numCities);
}
void addEdge(int city1, int city2, int cost) {
adjList[city1].push_back({city2, cost});
adjList[city2].push_back({city1, cost});
}
void primMST() {
int numCities = cities.size();
vector<int> key(numCities, INT_MAX);
vector<int> parent(numCities, -1);
vector<bool> inMST(numCities, false);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
key[0] = 0;
pq.push({0, 0}); // {cost, city}
while (!pq.empty()) {
int u = pq.top().second;
pq.pop();
inMST[u] = true;
for (const auto& edge : adjList[u]) {
int v = edge.destination;
int cost = edge.cost;
if (!inMST[v] && cost < key[v]) {
key[v] = cost;
pq.push({cost, v});
parent[v] = u;
}
}
}
printMST(parent, key);
}
void printMST(const vector<int>& parent, const vector<int>& key) {
cout << "Edge\tWeight\n";
int totalCost = 0;
for (int i = 1; i < parent.size(); i++) {
cout << cities[parent[i]] << " - " << cities[i] << "\t" << key[i] << "\n";
totalCost += key[i];
}
cout << "Total minimum cost: " << totalCost << endl;
}
};
int main() {
Graph g(6); // 6 cities
// Adding edges (city1, city2, cost)
g.addEdge(0, 1, 10); // Mumbai - Bengaluru
g.addEdge(0, 2, 15); // Mumbai - Chennai
g.addEdge(1, 2, 5); // Bengaluru - Chennai
g.addEdge(1, 3, 12); // Bengaluru - Jaipur
g.addEdge(2, 3, 8); // Chennai - Jaipur
g.addEdge(3, 4, 7); // Jaipur - Pune
g.addEdge(4, 0, 6); // Pune - Mumbai
g.addEdge(1, 5, 20); // Bengaluru - Hyderabad
g.addEdge(2, 5, 25); // Chennai - Hyderabad
g.primMST();
return 0;
}


Explanation-Let's break down and explain each part of the code for both versions you provided. The code implements Prim's Minimum Spanning Tree (MST) algorithm using adjacency lists.

---

### **First Version (Flexible Input - User-Provided Cities)**

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <unordered_map>
using namespace std;
```

* `#include <iostream>`: Includes input-output stream for using `cin` and `cout`.
* `#include <vector>`: Includes the vector container, which is used to store cities and edges.
* `#include <queue>`: Includes the priority queue container, which is used for efficient extraction of the minimum cost edge during Prim's algorithm.
* `#include <limits.h>`: Defines `INT_MAX`, which is used to initialize the key values for the algorithm.
* `#include <unordered_map>`: Includes the unordered map for fast access to city names by index.

---

#### **Struct Edge and Graph Class**

```cpp
struct Edge {
    int destination;
    int cost;
};
```

* Defines an `Edge` structure to represent a connection between two cities (`destination`) with an associated cost (`cost`).

```cpp
class Graph {
public:
    vector<string> cities;
    unordered_map<string, int> cityIndex;
    vector<vector<Edge>> adjList;
```

* **`vector<string> cities;`**: A vector to store city names.
* **`unordered_map<string, int> cityIndex;`**: A map to associate city names with their indices in the adjacency list for easy access.
* **`vector<vector<Edge>> adjList;`**: An adjacency list where each city has a list of `Edge` objects representing the cities it is connected to and the costs of those connections.

```cpp
Graph(int numCities) {
    adjList.resize(numCities);
}
```

* **`Graph(int numCities)`**: Constructor to initialize the graph with `numCities` cities by resizing the adjacency list to accommodate the edges of each city.

---

#### **Methods for Adding Cities and Edges**

```cpp
void addCity(const string& city) {
    cities.push_back(city);
    cityIndex[city] = cities.size() - 1;
}
```

* **`addCity(const string& city)`**: Adds a city to the `cities` vector and stores the index of the city in the `cityIndex` map.

```cpp
void addEdge(const string& city1, const string& city2, int cost) {
    int city1Index = cityIndex[city1];
    int city2Index = cityIndex[city2];
    adjList[city1Index].push_back({city2Index, cost});
    adjList[city2Index].push_back({city1Index, cost});
}
```

* **`addEdge(const string& city1, const string& city2, int cost)`**: Adds an undirected edge between `city1` and `city2` with the given `cost`. It updates the adjacency list for both cities.

---

#### **Prim’s MST Algorithm**

```cpp
void primMST() {
    int numCities = cities.size();
    vector<int> key(numCities, INT_MAX);
    vector<int> parent(numCities, -1);
    vector<bool> inMST(numCities, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
```

* **`primMST()`**: Implements Prim's algorithm to find the MST.
* **`key`**: A vector to store the minimum cost to connect a city to the MST. Initialized to `INT_MAX`.
* **`parent`**: A vector to store the parent city for each city in the MST.
* **`inMST`**: A boolean vector to track which cities are already included in the MST.
* **`pq`**: A priority queue that stores pairs of `(cost, city)`, always allowing us to extract the city with the smallest connecting cost.

```cpp
key[0] = 0;
pq.push({0, 0});
```

* **`key[0] = 0`**: Starts the MST from city 0, setting its key to 0.
* **`pq.push({0, 0});`**: Adds city 0 to the priority queue with a cost of 0.

```cpp
while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    inMST[u] = true;
```

* The `while` loop continues until all cities are included in the MST.
* **`int u = pq.top().second;`**: Extracts the city `u` with the smallest cost from the priority queue.
* **`pq.pop();`**: Removes city `u` from the queue.
* **`inMST[u] = true;`**: Marks city `u` as added to the MST.

```cpp
for (const auto& edge : adjList[u]) {
    int v = edge.destination;
    int cost = edge.cost;
    if (!inMST[v] && cost < key[v]) {
        key[v] = cost;
        pq.push({cost, v});
        parent[v] = u;
    }
}
```

* Loops through each edge of city `u` to explore its neighbors.
* If the neighboring city `v` is not in the MST and the cost to reach `v` is smaller than its current `key`, the algorithm updates `key[v]`, adds it to the priority queue, and sets `u` as the parent of `v`.

```cpp
printMST(parent, key);
```

* After constructing the MST, it calls `printMST()` to display the MST.

---

#### **Printing the MST**

```cpp
void printMST(const vector<int>& parent, const vector<int>& key) {
    cout << "Edge\tWeight\n";
    int totalCost = 0;
    for (int i = 1; i < parent.size(); i++) {
        cout << cities[parent[i]] << " - " << cities[i] << "\t" << key[i] << "\n";
        totalCost += key[i];
    }
    cout << "Total minimum cost: " << totalCost << endl;
}
```

* **`printMST()`**: Displays the edges of the MST and their corresponding weights.
* **`totalCost`**: Keeps track of the total cost of the MST.
* **`cout`**: Prints the edges and their costs, and finally the total cost of the MST.

---

#### **Main Function**

```cpp
int main() {
    int numCities;
    cout << "Enter number of cities: ";
    cin >> numCities;
```

* **`main()`**: The entry point of the program. It first takes the number of cities as input.

```cpp
Graph g(numCities);
```

* Creates a graph object `g` with the specified number of cities.

```cpp
cout << "Enter the names of the cities:\n";
for (int i = 0; i < numCities; i++) {
    string city;
    cout << "City " << i + 1 << ": ";
    cin >> city;
    g.addCity(city);
}
```

* Loops to input the names of the cities and adds them to the graph using `addCity()`.

```cpp
int numEdges;
cout << "Enter the number of edges: ";
cin >> numEdges;
```

* Takes the number of edges as input.

```cpp
cout << "Enter the edges in the format (city1 city2 cost):\n";
for (int i = 0; i < numEdges; i++) {
    string city1, city2;
    int cost;
    cout << "Edge " << i + 1 << ": ";
    cin >> city1 >> city2 >> cost;
    g.addEdge(city1, city2, cost);
}
```

* Takes input for each edge (city1, city2, cost) and adds it to the graph using `addEdge()`.

```cpp
g.primMST();
```

* Calls the `primMST()` function to compute the minimum spanning tree.

---

### **Second Version (Hardcoded Cities)**

This version is similar to the first one, but with a predefined set of cities (`Mumbai`, `Bengaluru`, etc.) instead of taking user input.

```cpp
vector<string> cities = {"Mumbai", "Bengaluru", "Chennai", "Jaipur", "Pune", "Hyderabad"};
```

* The cities are hardcoded as a list, which makes the program simpler but less flexible.

The rest of the code structure is nearly identical to the first version, but it uses the hardcoded cities instead of asking the user for city names.

---

### **Summary**

* **Prim's Algorithm**: The code implements Prim's MST algorithm to connect cities with the minimum cost using a priority queue to efficiently select the next city to add to the MST.
* **Graph Representation**: The graph is represented using an adjacency list where each city is connected to others with edges that have a cost.
* **User Input and Hardcoded Data**: The first version allows user input for cities and edges, while the second version uses predefined cities and edges.

Questions -
Here’s a concise set of **10 to 15 oral questions** and their answers on **Minimum Spanning Tree (MST)**:

---

### 1. What is a Minimum Spanning Tree (MST)?

**Answer:** A Minimum Spanning Tree (MST) is a subgraph of an undirected weighted graph that connects all the vertices with the minimum total edge weight, without forming any cycles.

---

### 2. Explain Prim’s Algorithm for MST.

**Answer:** Prim's Algorithm starts at an arbitrary vertex, adding the nearest vertex to the MST until all vertices are included. It selects the minimum weight edge that doesn’t form a cycle.

---

### 3. Explain Kruskal’s Algorithm for MST.

**Answer:** Kruskal’s Algorithm sorts all edges by weight and adds them one by one to the MST, provided they don’t form a cycle, until the tree contains all vertices.

---

### 4. What is the difference between Prim’s and Kruskal’s algorithms?

**Answer:** Prim’s algorithm grows the MST from a starting vertex by adding one vertex at a time, while Kruskal’s algorithm adds edges in increasing weight order. Prim’s is better for dense graphs, Kruskal’s for sparse graphs.

---

### 5. What is a cycle, and why is it avoided in an MST?

**Answer:** A cycle is a path where the first and last vertices are the same. It is avoided in MSTs because trees do not contain cycles, and cycles would increase the total cost.

---

### 6. What is the Union-Find data structure, and how is it used in Kruskal’s algorithm?

**Answer:** Union-Find tracks disjoint sets. In Kruskal’s, it ensures that adding an edge does not create a cycle by checking if two vertices belong to the same set and merging them if not.

---

### 7. What is the time complexity of Prim’s and Kruskal’s algorithms?

**Answer:**

* Prim’s: $O(E \log V)$ using a priority queue.
* Kruskal’s: $O(E \log E)$, dominated by edge sorting.

---

### 8. How do you handle disconnected graphs in MST?

**Answer:** A disconnected graph doesn’t have a spanning tree. Kruskal’s algorithm will form a Minimum Spanning Forest (MSF), consisting of MSTs for each connected component.

---

### 9. Can an MST have cycles?

**Answer:** No, an MST is a tree and by definition, trees don’t have cycles.

---

### 10. Can the same edge appear more than once in an MST?

**Answer:** No, each edge in an MST is unique. A tree, by definition, does not have repeated edges.

---

### 11. What is the role of edge weights in an MST?

**Answer:** The edge weights determine the total cost of the MST. The goal is to minimize the sum of the weights of the edges connecting all vertices.

---

### 12. What is the significance of the weight of edges in Prim’s algorithm?

**Answer:** The weight determines the minimum cost edge to add next to the MST. The algorithm always chooses the smallest edge that doesn’t create a cycle.

---

### 13. Is MST always unique?

**Answer:** No, if there are multiple edges with the same weight, there could be multiple MSTs with the same total weight but different edge selections.

---

### 14. What is the difference between a spanning tree and a minimum spanning tree?

**Answer:** A spanning tree connects all vertices with $V-1$ edges, while a minimum spanning tree is the spanning tree with the least total edge weight.

---

### 15. What is the maximum number of edges in an MST?

**Answer:** The maximum number of edges in an MST is $V-1$, where $V$ is the number of vertices. A tree with $V$ vertices has exactly $V-1$ edges.

---

These concise questions and answers cover the basics of MST and algorithms associated with it. Let me know if you'd like more!
