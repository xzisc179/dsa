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
