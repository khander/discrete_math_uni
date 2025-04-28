#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


struct Edge {
    int dest;
    int weight;
};


struct Vertex {
    int index;
    int distance;

    bool operator<(const Vertex& other) const {
        return distance > other.distance;
    }
};

void deijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, INT_MAX); // расстояния до всех вершин
    vector<bool> visited(n, false);    // посещенные вершины
    
    distances[start] = 0;
    
    priority_queue<Vertex> pq;
    pq.push({start, 0});
    
    while (!pq.empty()) {

        Vertex current = pq.top();
        pq.pop();
        int u = current.index;
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (const Edge& edge : graph[u]) {
            int v = edge.dest;
            int weight = edge.weight;
            
            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                pq.push({v, distances[v]});
            }
        }
    }
    
    cout << "Destination from " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Point " << i << ": cant be reached\n";
        } else {
            cout << "Point " << i << ": " << distances[i] << "\n";
        }
    }
}

int prep_deijkstra(const vector<vector<int>>& arr, int from) {
    int n = arr.size();
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(arr[i][j] > 0){
                graph[i].push_back({j, arr[i][j]});
            }
        }
    }

    deijkstra(graph, from);
    return 0;
}