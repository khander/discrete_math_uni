#include <iostream>
#include <vector>
#include "graph.cpp"
#include "deijkstra.cpp"
#include "floyd.cpp"
#include "ford.cpp"

using namespace std;

int main(){
    std::vector<std::vector<int>> array ={
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 0}
    };

    std::vector<std::vector<int>> array2 ={
        {0, 7, 0, 0, 1},
        {3, 0, -5, 0, 0},
        {-2, 0, 0, 0, 5},
        {0, 4, 0, 0, 0},
        {0, 8, 0, 1, 0}
    };
    /*
    Graph graph(array);
    graph.print_main_matrix();
    graph.print_incident_matrix();

    graph.create_linked_graph();
    cout<< graph.check_if_euler() << endl;
    */
    //graph.painting();

    //prep_deijkstra(array2, 0);
    prep_floyd(array2);
    //prep_ford(array2, 0);

    return 0;
}
