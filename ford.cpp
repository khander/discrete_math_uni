#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Link_ {
    int src;
    int dest;
    int weight; 
};

void ford(const vector<Link_>& edges, int n, int start) {
    vector<int> distances(n, INT_MAX);
    distances[start] = 0;

    for (int i = 1; i <= n - 1; ++i) {
        for (const Link_& Link_ : edges) {
            int u = Link_.src;
            int v = Link_.dest;
            int weight = Link_.weight;
            
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    for (const Link_& Link_ : edges) {
        int u = Link_.src;
        int v = Link_.dest;
        int weight = Link_.weight;
        
        if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
            cout << "Below zero cycle from start!\n";
            return;
        }
    }

    cout << "Shortest way from " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Point " << i << ": unreacheble\n";
        } else {
            cout << "Point " << i << ": " << distances[i] << "\n";
        }
    }
}

int prep_ford(const vector<vector<int>>& arr, int from) {
    int n = arr.size();
    vector<Link_> edges;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(arr[i][j] > 0){
                edges.push_back({i, j, arr[i][j]});
            }
        }
    }
    ford(edges, n, 0);

    return 0;
}