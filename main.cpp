#include <iostream>
#include <vector>
#include "graph.cpp"

using namespace std;

int main(){
    std::vector<std::vector<int>> array ={
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 0}
    };
    Graph graph(array);
   // graph.udate_by_upper_part();
    graph.print_main_matrix();
    //printf("\n%d\n", graph.get_links_amount());
    graph.print_incident_matrix();

    graph.create_linked_graph();
    //std::vector<int> jj = graph.get_joint_links_amount();
    //cout<< jj[2] << endl;
    cout<< graph.check_if_euler() << endl;
    return 0;
}
