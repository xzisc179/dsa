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
