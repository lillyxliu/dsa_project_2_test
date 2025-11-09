#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cfloat>  
#include "person.h"
#include "dataStructureOne.h"
#include "dataStructureTwo.h"
#include "graph.h"
#include "functions.h"
#include <chrono>
#include "userInputTest.h"
using namespace std::chrono;
using namespace std;

// Larger Dataset Names Generated from https://1000randomnames.com/ 

int main(){ 
    cout << "----------------------------------" << endl;
    cout << "   Welcome to the DoppleGator!!" << endl;
    cout << "----------------------------------\n\n" << endl;  
    bool listening = true;
    string data_set_loaded = "../data/dataset.csv";
    map<string, Person> a_map;
    vector<string> vector_id;
    Graph calc_graph;
    int newly_added_count = 0; // Counter for newly added people

    // Load the default dataset at startup
    ifstream initial_data(data_set_loaded);
    if (initial_data.is_open()) {
        string headers;
        getline(initial_data, headers, '\n'); // skip header
        load_people_data(initial_data, a_map, vector_id);
        initial_data.close();
        cout << "Default dataset loaded successfully: " << data_set_loaded << endl;
        cout << "Loaded " << a_map.size() << " people." << endl;

        // timing the heap sort graph 
        auto heap_graph = measure_time([&](){
            calc_graph = build_graph(a_map, vector_id, "heap");
        });
        cout << "Graph build took " << heap_graph.count() << " microseconds." << endl;

        
    } else {
        cout << "Warning: Could not load default dataset. Please use option 0 to load a dataset." << endl;
    }

    while (listening) {
        cout << "----------------------------------" << endl;
        cout << "Menu:" << endl;
        cout << "0. Choose Data Set" << endl;
        cout << "1. Choose Sorting Algorithm" << endl;
        cout << "2. Graph Functions" << endl;
        cout << "3. Add Person" << endl;
        cout << "4. Lookup Person" << endl;
        cout << "5. View Person Information" << endl;
        cout << "6. Exit" << endl;
        cout << "[Currently Loaded Data Set: " << data_set_loaded << "]" << endl;
        cout << "[Number of newly added people: " << newly_added_count << "]" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) { // CHANGE DATASET
            cout << "Enter data set name (without path or .csv): ";
            string data_set_name;
            cin >> data_set_name;
            data_set_loaded = "../data/" + data_set_name + ".csv";

            ifstream data(data_set_loaded);
            if (!data.is_open()) {
                cout << "Error opening file. Reverting to previous dataset." << endl;
                continue;
            }

            string headers;
            getline(data, headers, '\n'); // skip header
            a_map.clear();
            vector_id.clear();

            load_people_data(data, a_map, vector_id);
            data.close();

            cout << "Data set loaded successfully: " << data_set_loaded << endl;

            load_people_data(initial_data, a_map, vector_id);
            cout << "Loaded " << a_map.size() << " people." << endl;
        } 

        else if(choice == 1) { // CHOOSE SORTING ALGORITHM
            cout << "Choose sorting algorithm (heap/quick): ";
            string algo_choice;
            cin >> algo_choice;
            if (algo_choice == "heap") {
                // rebuild graph
                auto heap_graph = measure_time([&](){
                calc_graph = build_graph(a_map, vector_id, "heap");
                });
                cout << "Graph rebuilt using heap sort takes " << heap_graph.count() << " microseconds." << endl;

            }
            if(algo_choice == "quick") {
                // rebuild graph
                auto quick_graph = measure_time([&](){
                calc_graph = build_graph(a_map, vector_id, "quick");
                });
                cout << "Graph rebuilt using quick sort takes " << quick_graph.count() << " microseconds." << endl;

            }
            else {
                cout << "Invalid choice. Please enter 'heap' or 'quick'." << endl;
            }
        }



        else if (choice == 2) { // GRAPH FUNCTIONS
            if (a_map.empty()) {
                cout << "No dataset loaded. Please load a dataset first." << endl;
                continue;
            }

            int choice_1;
            cout << "-----" << endl;
            cout << "> Graph Functions:" << endl;
            cout << ">> 1. Print Graph" << endl;
            cout << ">> 2. Vertex Count" << endl;
            cout << ">> 3. Edge Count" << endl;
            cout << ">> 4. Check Edge Existence" << endl;
            cout << ">> 5. Checkout Node" << endl;
            cout << "Enter choice: ";
            cin >> choice_1;

            if (choice_1 == 1) {
                
                calc_graph.printGraph(a_map);
            }
            else if (choice_1 == 2) {
                cout << "----------------------------------" << endl;
                cout << "Vertex Count: " << calc_graph.vertex_count() << endl;
                cout << "----------------------------------" << endl;

            }
            else if (choice_1 == 3) {
                cout << "----------------------------------" << endl;
                cout << "Edge Count: " << calc_graph.edge_count() << endl;
                cout << "----------------------------------" << endl;

            }
            else if (choice_1 == 4) {
                string from_id, to_id;
                cout << "Enter first ID: ";
                cin >> from_id;
                cout << "Enter second ID: ";
                cin >> to_id;
                int from_index = calc_graph.find_node_index(from_id);
                int to_index = calc_graph.find_node_index(to_id);

                if (calc_graph.isEdge(from_index, to_index)) {
                    cout << "Edge exists between " << lookup_id_get_obj(from_id,a_map).get_first_name() << " and " << lookup_id_get_obj(to_id,a_map).get_first_name() << endl;
                } else {
                    cout << "No edge exists between " << lookup_id_get_obj(from_id,a_map).get_first_name() << " and " << lookup_id_get_obj(to_id,a_map).get_first_name() << endl;
                }
            }
            else if (choice_1 == 5) {
                string id;
                cout << "Enter node ID to checkout: ";
                cin >> id;

                int index = calc_graph.find_node_index(id);
                if (index == -1) {
                    cout << "Node not found." << endl;
                } else {
                    cout << "[" << a_map[id].get_first_name() << "]:" << endl;
                    for (auto neighbor : calc_graph.nodes[index].neighbors) {
                        cout << a_map[neighbor.first].get_first_name()
                             << " (weight: " << neighbor.second << ")" << endl;
                    }
                }
            }
        } 
        else if (choice == 3) { // ADD PERSON
            try {
                Questions new_person;
                new_person.run_test();
                // create new person
                Person created = new_person.get_user_person();
                if (!created.get_id().empty()) {
                    // add to map
                    if (a_map.find(created.get_id()) == a_map.end()) {
                        a_map.insert({created.get_id(), created});
                    }
                    // add to graph
                    string sorting_algorithim  = "";
                    cout << "Select Sorting Algorithm to Add Person to Graph (heap/quick)" << endl;
                    cin >> sorting_algorithim;
                    auto time_graph = measure_time([&](){
                    add_person_to_graph(created, a_map, vector_id, calc_graph, 3, sorting_algorithim);
                    });
                    cout << "Graph rebuilt after adding person with " << sorting_algorithim << " takes " << time_graph.count() << " microseconds." << endl;
                }
                newly_added_count++;
                cout << "Person added successfully!" << endl;


        // exception handling from: https://www.geeksforgeeks.org/cpp/exception-handling-c/ 
            } catch (const exception& e) {
                cerr << "Error adding person: " << e.what() << endl;
            }
        } 
        else if (choice == 4) { // LOOKUP PERSON
            if (a_map.empty()) {
                cout << "No dataset loaded. Please load a dataset first." << endl;
                continue;
            }
            lookup_person(a_map);
        } 
        else if (choice == 5) { // VIEW PERSON INFO
            if (a_map.empty()) {
                cout << "No dataset loaded. Please load a dataset first." << endl;
                continue;
            }
            view_person_info(a_map);
        } 
        else if (choice == 6) { // EXIT
            cout << "Exiting program..." << endl;
            listening = false;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
