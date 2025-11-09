#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "person.h"
#include "dataStructureOne.h"
#include "dataStructureTwo.h"
#include "graph.h"

using namespace std::chrono;
using namespace std;


Person lookup_id_get_obj(string id, map<string,Person>& a_map);
float id_to_value_physical(string& id, Person& p_source,  map<string,Person>& a_map);
float id_to_value_personality(string& id, Person& p_source,  map<string,Person>& a_map);
float id_to_value_type(string& id, Person& p_source,  map<string,Person>& a_map,int type);
void load_people_data(ifstream& data,map<string,Person>& a_map, vector<string>& vector_id);
template<typename T>
auto measure_time(T funct){
    auto start_funct = high_resolution_clock::now();
    funct();
    auto end_funct= high_resolution_clock::now();
    return duration_cast<microseconds>(end_funct - start_funct);
}
void measure_sorting_algos(map<string,Person>& a_map, vector<string>& vector_id, Person& source_p);
void print_loaded_first_names(map<string,Person>& a_map, vector<string>& vector_id);
Graph build_graph(map<string,Person>& a_map, vector<string>& vector_id, string sort_option = "heap");
void display_person_info(const Person& p);
void lookup_person(map<string,Person>& a_map);
void view_person_info(map<string,Person>& a_map);
void add_person_to_graph(const Person& new_p, map<string,Person>& a_map, vector<string>& vector_id, Graph& g, int connections_max, string sort_option = "heap");


#endif 
