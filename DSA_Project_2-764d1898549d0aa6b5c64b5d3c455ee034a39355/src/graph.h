#ifndef GRAPH_H
#define GRAPH_H
#pragma once

#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include "person.h"
//#include "functions.h"
using namespace std;

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/CORS
// https://www.npmjs.com/package/react-force-graph
// https://www.geeksforgeeks.org/cpp/implementation-of-graph-in-cpp/
// Slides: page 55 adjency list, page 58 one graph api
class Graph{
public: 
    struct Node {
        string id;
        vector<pair<string,float>> neighbors; // string: id, float: weight
        
        Node();
        Node(string id_);
        Node(const Node& other);
        Node& operator=(const Node& other);
        ~Node();
    };

public:
    vector<Node> nodes;
    map<string, int> id_to_index; // id is string, int is index in nodes vector

    Graph();
    Graph(int v);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();

    void add_node(string id);
    void add_edge(string from, string to, float weight);
    int vertex_count();
    int edge_count();
    bool isEdge(int form, int to);
    int getWeight(int from, int to);
    vector<int> getAdjacent(string id);
    void printGraph();
    void printGraph(map<string,Person>& a_map);
    int find_node_index(string id);

    const vector<Node>& get_nodes() const;
    const map<string, int>& get_id_to_index() const;

};

#endif
