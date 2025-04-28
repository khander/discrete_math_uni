#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

struct Joint;

struct Link{
    Joint* from;
    Joint* to;
    int weight;
};

struct Joint{
    char node_name;
    int number;
    std::vector<Link*> links;
};

class Graph{
private:
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> incident_id;
    std::vector<std::vector<int>> incident_matrix;
    std::vector<Joint*> linked_graph_joints;
    std::vector<int> joint_links;
    //Joint* head_joint;
public:
    void width_traversal();
    void painting();
    void print_main_matrix();
    void print_incident_matrix();
    int get_links_amount();
    bool check_if_euler();
    void udate_by_upper_part();
    void create_linked_graph();
    int get_links_amount(int);      // for established index
    bool check_if_incident(int,int);

    std::vector<int> get_joint_links_amount();

    Graph(const std::vector<std::vector<int>>& array);
    friend std::ostream& operator<<(std::ostream&, const std::vector<std::vector<int>>& vec);
};

void Graph::create_linked_graph(){
    for(int count = 0;count < matrix.size(); count++){
        Joint* joint = new Joint;
        joint->number = count;
        joint->node_name = 'A' + count;
        linked_graph_joints.push_back(joint);
    }
    for(int count = 0; count < matrix.size(); count++){
        for(int i = 0; i < matrix.size(); i++){
            if(matrix[count][i] > 0){
                linked_graph_joints[count]->links.push_back(new Link{linked_graph_joints[count], linked_graph_joints[count], matrix[count][i]});
                printf("link created\n");
            }
        }

    }
    //printf("%c", head_joint->node_name);
}

int Graph::get_links_amount(int x){
    int counter = 0;
    for (int i = 0; i < matrix.size(); i++){
        if(matrix[x][i] > 0)
            counter++;
    }
    return counter;
}

void Graph::painting(){
    std::vector<std::vector<int>> temp_vec_for_painting(2, std::vector<int>(matrix.size(), 0));
    for (int i = 0; i < temp_vec_for_painting[0].size(); i++){
        temp_vec_for_painting[0][i] = i;
        temp_vec_for_painting[1][i] = get_links_amount(i);
    }
    
    std::vector<std::vector<int>> transposed(temp_vec_for_painting[0].size(), std::vector<int>(2));
    for (int i = 0; i < temp_vec_for_painting[0].size(); ++i) {
        transposed[i][0] = temp_vec_for_painting[0][i];
        transposed[i][1] = temp_vec_for_painting[1][i];
    }

    std::sort(transposed.begin(), transposed.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[1] > b[1];
    });

    for (int i = 0; i < temp_vec_for_painting[0].size(); ++i) {
        temp_vec_for_painting[0][i] = transposed[i][0]; 
        temp_vec_for_painting[1][i] = transposed[i][1];
    }

    for (int i = 0; i < temp_vec_for_painting.size(); i++){
        for (int j = 0; j < temp_vec_for_painting[0].size(); j++){
            std::cout << temp_vec_for_painting[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> paint(5, std::vector<int>(0));
//version brut
    
    int current_paint = 0;
    int counter = 0;

    while(temp_vec_for_painting[0].size() > 0){
        int counter = 0;
        bool flag = 0;
        paint[current_paint].push_back(temp_vec_for_painting[0][0]);
        temp_vec_for_painting[0].erase(temp_vec_for_painting[0].begin());
        temp_vec_for_painting[1].erase(temp_vec_for_painting[1].begin());
        while(counter < temp_vec_for_painting[0].size()){
            bool inner_flag = 0;
            for (int i = 0; i < paint[current_paint].size(); i++){
                if (!check_if_incident(temp_vec_for_painting[0][counter], paint[current_paint][i]))
                    inner_flag = 1;
            }
            if(!inner_flag){
                paint[current_paint].push_back(temp_vec_for_painting[0][counter]);
                temp_vec_for_painting[0].erase(temp_vec_for_painting[0].begin());
                temp_vec_for_painting[1].erase(temp_vec_for_painting[1].begin());
            }

        }

            //to do : finish function
        

    }
}

bool Graph::check_if_incident(int a, int b){
    return matrix[a][b];
}

Graph::Graph(const std::vector<std::vector<int>>& array){
    matrix = array;
//    udate_by_upper_part();
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

    create_linked_graph();
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

/* void Graph::width_traversal(){
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

} */