#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>

class Graph{
private:
std::vector<std::vector<int>> matrix;
std::vector<std::vector<int>> incident_id;
std::vector<std::vector<int>> incident_matrix;
std::vector<int> joint_links;
public:
    void width_traversal();
    void print_main_matrix();
    void print_incident_matrix();
    int get_links_amount();
    bool check_if_euler();
    void udate_by_upper_part();
    
    std::vector<int> get_joint_links_amount();

    Graph(const std::vector<std::vector<int>>& array);
    friend std::ostream& operator<<(std::ostream&, const std::vector<std::vector<int>>& vec);
};

Graph::Graph(const std::vector<std::vector<int>>& array){
    matrix = array;
    udate_by_upper_part();
    joint_links = get_joint_links_amount();
    std::vector<std::vector<int>> temp_vec_for_incident_id(2, std::vector<int>(get_links_amount(), 0));
    int count = get_links_amount();
    int counter = 0;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = i+1; j < matrix[i].size();j++){
            if(matrix[i][j] > 0){
                temp_vec_for_incident_id[0][counter] = i;
                temp_vec_for_incident_id[1][counter++] = j;
            }
        }
    }
    incident_id = temp_vec_for_incident_id;
    std::vector<std::vector<int>> temp_vec_for_incident_matrix(matrix.size(), std::vector<int>(get_links_amount(), 0));
    for (int i = 0; i < count; i++){
        temp_vec_for_incident_matrix[incident_id[0][i]][i] = 1;
        temp_vec_for_incident_matrix[incident_id[1][i]][i] = 1;
    }
    incident_matrix = temp_vec_for_incident_matrix;
};

void Graph::print_main_matrix(){
    std::cout << "main matrix:" << std::endl;
    for(int i = 0; i < matrix.size();i++){
        for(int j = 0; j < matrix[i].size(); j++){
            std::cout << std::setw(2) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::print_incident_matrix(){
    std::cout << "incident matrix:" << std::endl;
    std::cout << "    ";
    for(int i = 0; i < incident_id[0].size(); i++){
        std::cout << std::setw(2) << incident_id[0][i]<< "-"<< incident_id[1][i]<< " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < incident_matrix.size();i++){
        std::cout << i << "  ";
        for(int j = 0; j < incident_matrix[i].size(); j++){
            std::cout << std::setw(4) << incident_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Graph::get_links_amount(){
    int count = 0;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = i+1; j < matrix[i].size();j++){
            if(matrix[i][j] > 0) count++;
        }
    }
    return count;
}

std::vector<int> Graph::get_joint_links_amount(){
    std::vector<int> joint_links(matrix[0].size());
    for(int i = 0; i < matrix.size(); i++){
        joint_links[i] = 0;
        for(int j = 0; j < matrix[i].size();j++){
            if(matrix[i][j] > 0) joint_links[i]++;
        }
    }
    return joint_links;
}

bool Graph::check_if_euler(){
    for(int i = 0; i < matrix.size(); i++){
        if(joint_links[i] % 2 == 1) return 0;
    }
    return 1;
}

void Graph::udate_by_upper_part(){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = i+1; j < matrix[i].size();j++){
            matrix[j][i] = matrix[i][j];
        }
    }
}

void Graph::width_traversal(){
    std::vector<int> ban_list(matrix.size(), 0);
    std::vector<int> current_list(matrix.size(), 0);
    std::vector<int> new_list(matrix.size(), 0);
    int counter_ban_list = 0;
    int counter_current_list = 0;
    int counter_new_list = 0;
    current_list[counter_current_list++] = incident_id[0][0];
//    ban_list[counter_ban_list++] = current_list[0];

    std::cout << "[" << current_list[0] << "]" << std::endl;

    while(counter_ban_list < matrix.size()){
        for(int i = 0; i < counter_current_list; i++){
            std::cout << "from " << current_list[i] << " : ";
            for (int j = 0; j < incident_id[0].size(); j++){
                if(std::find(std::begin(ban_list),std::end(ban_list), current_list[i]) == std::end(ban_list)){
                    if(incident_id[0][j]==current_list[i])
                        new_list[counter_new_list++] = incident_id[1][j];
                    else if(incident_id[1][j]==current_list[i])
                        new_list[counter_new_list++] = incident_id[0][j];
                    std::cout << current_list[i] << " ";
                }
            }
        }
    }
//    std::cout << "[" << incident_id[0][0] << "]" << std::endl;
//    ban_list[counter++] = incident_id[0][0];

}