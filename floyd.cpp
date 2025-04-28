#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX / 2;

void floyd(const vector<vector<int>>& graph) {
    int n = graph.size();
    
    vector<vector<int>> dist(n, vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = graph[i][j];
        }
    }
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (dist[i][i] < 0) {
            cout << "Error: below zero cycle!\n";
            return;
        }
    }
    
    cout << "Matrix of shortest ways:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

int prep_floyd(const vector<vector<int>>& arr) {
    int n = arr.size();
    vector<vector<int>> graph (arr.size(), std::vector<int>(arr.size(), INF));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(arr[i][j] > 0 || i == j){
                graph[i][j] = arr[i][j];
            }
        }
    }
    floyd(graph);
    
    return 0;
}