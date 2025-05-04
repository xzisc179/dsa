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
