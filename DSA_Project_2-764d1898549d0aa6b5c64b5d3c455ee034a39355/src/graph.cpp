#include "graph.h"
//////////////////
// Node Methods //
//////////////////
Graph::Node::Node() {} // default constructor

Graph::Node::Node(string id_){  // parameterized constructor
    id = id_;
}
Graph::Node::Node(const Graph::Node& other){
    id = other.id;
    neighbors = other.neighbors;
}

Graph::Node& Graph::Node::operator=(const Graph::Node& other) {
    if (this != &other) {
        id = other.id;
        neighbors = other.neighbors;
    }
    return *this;
}

Graph::Node::~Node() {} // destructor
///////////////////
// Graph Methods //
///////////////////
Graph::Graph(){} // defualt constructor

Graph::Graph(int v){ // constructor: initialize v nodes
    for(int i = 0; i < v; i++){
        nodes.push_back(Node("")); // empty id
    }
}

Graph::Graph(const Graph& other){ // copy constructor
    nodes = other.nodes;
    id_to_index = other.id_to_index;
}

Graph& Graph::operator=(const Graph& other){ // assignment operator
    if(this != &other){
        nodes = other.nodes;
        id_to_index = other.id_to_index;
    }
    return *this;
}

Graph::~Graph(){} // destructor, no dynamic memory


void Graph::add_node(string id){
    if(id_to_index.find(id) == id_to_index.end()){ 
        id_to_index[id] = nodes.size(); 
        nodes.push_back(Node(id));
    }
}

void Graph::add_edge(string from, string to , float weight){
    if(to == from){
        return;
    }
    add_node(from);
    add_node(to);
    int from_index = find_node_index(from);
    int to_index = find_node_index(to);
    for(auto neighbor: nodes[from_index].neighbors){
        if(neighbor.first == to){
            return;
        }
    }
    nodes[from_index].neighbors.push_back({to,weight});
}

int Graph::vertex_count(){
    return nodes.size();
}
int Graph::edge_count(){
    int count = 0;
    for(int i = 0; i< nodes.size();i++){
        count += nodes[i].neighbors.size();
    }
    return count/2;
}


bool Graph::isEdge(int from, int to){
    if(from< 0 || to <0 ){
        return false;
    }
    if(from >= nodes.size() || to >= nodes.size()){
        return false;
    }
    int from_index = find_node_index(nodes[from].id);
    int to_index = find_node_index(nodes[to].id);
    if(from_index == -1 || to_index == -1){
        return false;
    }
    for(auto neighbor: nodes[from_index].neighbors){
        if(neighbor.first == nodes[to_index].id){
            return true;
        }
    }
    return false;
}

int Graph::getWeight(int from, int to){
    int from_index = find_node_index(nodes[from].id);
    int to_index = find_node_index(nodes[to].id);
    for(int i = 0; i<nodes[from_index].neighbors.size();i++){
        if(nodes[from_index].neighbors[i].first== nodes[to_index].id){
            return nodes[from_index].neighbors[i].second;
        }
    }
    return -1;
}
vector<int> Graph::getAdjacent(string id){
    int node_index = find_node_index(id);
    vector<int> adjacent_indices;
    if(node_index == -1){
        return adjacent_indices;
    }
    for(auto neighbor: nodes[node_index].neighbors){
        adjacent_indices.push_back(find_node_index(neighbor.first));
    }
    return adjacent_indices;
}
void Graph::printGraph(){ // structural print based on id
    for(auto node: nodes){
        for(auto neighbor: node.neighbors){
            cout << node.id << ": " << neighbor.first << "; weight: " << neighbor.second << ";" << endl;
        }
    }
}
void Graph::printGraph(map<string,Person>& a_map){ // prints user version of graph
    for(auto node: nodes){
        cout << endl << "[" << a_map[node.id].get_first_name() << "]: " ;
        for(auto neighbor: node.neighbors){
            cout << a_map[neighbor.first].get_first_name() << "(" << neighbor.second << ")";
            if( neighbor.first != node.neighbors.back().first){
                cout << ", ";
            }
        }
        cout << endl;
    }
}
    
int Graph::find_node_index(string id){
    auto iter = id_to_index.find(id);
    if(iter != id_to_index.end()){
        return iter->second;
    }
    return -1;
} 