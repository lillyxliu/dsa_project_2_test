#include "functions.h"
#include <queue>
#include <functional>
#include <algorithm>
#include <limits>
#include "dataStructureOne.h"
#include "dataStructureTwo.h"

// find  most similar people to a target Person
vector<pair<string,float>> find_most_similar(Person& target, map<string,Person>& a_map, int k);


Person lookup_id_get_obj(string id, map<string,Person>& a_map){  
    return a_map[id];
} 

float id_to_value_physical(string& id, Person& p_source,  map<string,Person>& a_map){
    Person per = lookup_id_get_obj(id, a_map);
    float value = per.calc_physical_dif(p_source);
    return value;
}

float id_to_value_personality(string& id, Person& p_source,  map<string,Person>& a_map){
    Person per = lookup_id_get_obj(id, a_map);
    float value = per.calc_pers_dif(p_source);
    return value;
}
float sum_personality_and_physical(string& id, Person& p_source, map<string,Person>& a_map){
    float personality = id_to_value_personality(id, p_source, a_map);
    float physical = id_to_value_physical(id, p_source, a_map);
    return personality + physical;
}

float compare_to_zero(string& id, Person& p_source){
    return 0.0;
}

float id_to_value_type(string& id, Person& p_source,  map<string,Person>& a_map,int type){
    if(type == 0){
        return id_to_value_personality(id, p_source, a_map);
    }else if(type == 1){ 
        return id_to_value_physical(id, p_source, a_map);
    }else if(type == 2){
        return sum_personality_and_physical(id, p_source, a_map);
    }else{
        return 0.0; // placeholder
    } 
}

void load_people_data(ifstream& data,map<string,Person>& a_map, vector<string>& vector_id){    
    string row_str;
    while(getline(data, row_str, '\n')){
      Person p(row_str);
      a_map.insert({p.get_id(),p});
      vector_id.push_back(p.get_id()); 
    }
}

void measure_sorting_algos(map<string,Person>& a_map, vector<string>& vector_id, Person& source_p){
    vector<string> vector_id_personality_heap = vector_id;
    vector<string> vector_id_physical_heap = vector_id;
    vector<string> vector_id_personality_quick = vector_id;
    vector<string> vector_id_physical_quick = vector_id;
    auto heap_pers_time = measure_time([&](){
        heap_sort(vector_id_personality_heap, source_p, a_map, 0); // by personality
    });
    auto heap_phys_time = measure_time([&](){
        heap_sort(vector_id_physical_heap, source_p, a_map, 1); // by physical
    });
    cout << "heap_sort took " << (heap_pers_time + heap_phys_time).count() << " microseconds." << endl;
    auto quick_pers_time = measure_time([&](){
        quick_sort(vector_id_personality_quick, 0, vector_id_personality_quick.size() - 1, source_p, a_map, 0); // by personality
    });
    auto quick_phys_time = measure_time([&](){
        quick_sort(vector_id_physical_quick, 0, vector_id_physical_quick.size() - 1, source_p, a_map, 1); // by physical
    });
    cout << "quick_sort took " << (quick_pers_time + quick_phys_time).count() << " microseconds." << endl;
}

void print_loaded_first_names(map<string,Person>& a_map, vector<string>& vector_id){
    cout << "----------------------" << endl;
    cout << "Printing first names: " << endl;
    for(int i =0 ; i<vector_id.size();i++){
        cout << a_map[vector_id[i]].get_first_name() << " "; 
    }
    cout << "Printing first names: " << endl;
}


// this build graph but with option to parse in sorting option
Graph build_graph(map<string,Person>& a_map, vector<string>& vector_id, string sort_option){
    int connections_max = 3;
    Graph calc_graph;
    int count = 0;
    vector<vector<pair<string, float>>> pre_calc_weights(vector_id.size(), vector<pair<string, float>>());
    for(int i =0; i< vector_id.size();i++){
        Person& person_one = a_map[vector_id[i]];
        for(int j= i+1; j< vector_id.size(); j++){
            Person& person_two = a_map[vector_id[j]];
            float weight_personality = person_one.calc_pers_dif(person_two)/4.0f;
            float weight_physical = person_one.calc_physical_dif(person_two)/4.0f;
            float total_weight = (weight_personality*0.8 + weight_physical*0.2);
            pre_calc_weights[i].push_back({vector_id[j], total_weight});
            pre_calc_weights[j].push_back({vector_id[i], total_weight});
        }

    if(sort_option == "heap" || sort_option == "Heap"){
        heap_sort_generic(pre_calc_weights[i], true);
    }else if(sort_option == "quick" || sort_option == "Quick"){
        quick_sort_pairs(pre_calc_weights[i], 0, pre_calc_weights[i].size()-1);
    }else{
        heap_sort_generic(pre_calc_weights[i],false);
    }
        for(int c = 0; c < min(connections_max, (int)pre_calc_weights[i].size()); c++){
            calc_graph.add_edge(vector_id[i], pre_calc_weights[i][c].first, pre_calc_weights[i][c].second);
        }
        count++;
        
        if ((vector_id.size() >= 10 && count % (vector_id.size() / 10) == 0) || vector_id.size() < 10) {
            cout << "Loaded: " << count << "; " << endl;
        }
    }
    return calc_graph;
}

void lookup_person(map<string,Person>& a_map){
    cout << "\nSearch by:" << endl;
    cout << "1. ID" << endl;
    cout << "2. Name" << endl;
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input." << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice == 1) {
        string id;
        cout << "Enter person ID: ";
        getline(cin, id);
        id.erase(0, id.find_first_not_of(" \t\r\n"));
        id.erase(id.find_last_not_of(" \t\r\n") + 1);
        auto it = a_map.find(id);
        if (it == a_map.end()) {
            cout << "Person with ID " << id << " does not exist." << endl;
        } else {
            cout << "Person with ID " << id << " exists: " << it->second.get_first_name() << " " << it->second.get_last_name() << endl;
        }
        return;
    }
    else if (choice == 2) {
        string first_name, last_name;
        cout << "Enter first name: ";
        getline(cin, first_name);
        cout << "Enter last name: ";
        getline(cin, last_name);
        // https://cplusplus.com/reference/string/string/find_first_not_of/
        // finds the index of the first character that is not a space, tab, return, or new line
        first_name.erase(0, first_name.find_first_not_of(" \t\r\n"));
        first_name.erase(first_name.find_last_not_of(" \t\r\n") + 1);
        last_name.erase(0, last_name.find_first_not_of(" \t\r\n"));
        last_name.erase(last_name.find_last_not_of(" \t\r\n") + 1);
        vector<const Person*> matches;
        for (const auto &pair : a_map) {
            const Person &p = pair.second;
            if (p.get_first_name() == first_name && p.get_last_name() == last_name) {
                matches.push_back(&p);
            }
        }
        if (matches.empty()) {
            cout << "Person with name " << first_name << " " << last_name << " not found." << endl;
        } else {
            cout << "Found " << matches.size() << " matching person(s):" << endl;
            for (const Person* mp : matches) {
                cout << "  " << mp->get_first_name() << " " << mp->get_last_name() << " (ID: " << mp->get_id() << ")" << endl;
            }
        }
        return;
    }
    else {
        cout << "Invalid choice." << endl;
        return;
    }
}

void add_person_to_graph(const Person& new_p, map<string,Person>& a_map, vector<string>& vector_id, Graph& g, int connections_max, string sort_option){
    string new_id = new_p.get_id();

    if (a_map.find(new_id) == a_map.end()) {
        a_map[new_id] = new_p;
        g.add_node(new_id);
        vector_id.push_back(new_id);
    }
    
    vector<pair<string,float>> weights;
    for(const string& existing_id: vector_id){
        if(existing_id == new_id){
            continue; // skip newly added id
        }
        Person& existing = a_map[existing_id];
        float w = existing.calc_pers_dif(new_p)/4.0f * 0.8f +
                  existing.calc_physical_dif(new_p)/4.0f * 0.2f;
        weights.push_back({existing_id,w});
    }
    
    if(sort_option == "heap"){
        heap_sort_generic(weights,false);
    }else if(sort_option == "quick"){
        quick_sort_pairs(weights, 0, weights.size()-1);
    }else{
        heap_sort_generic(weights,false);
    }
    
    int n = min(connections_max, (int)weights.size());
    for(int i =0; i<n; i++){
        string other_id = weights[i].first;
        float w = weights[i].second;
        g.add_edge(new_id,other_id,w); // directed graph
    }
}

void display_person_info(const Person& p) {
    cout << "\n----------------------------------------" << endl;
    cout << "Person Information:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Basic Information:" << endl;
    cout << "ID: " << p.get_id() << endl;
    cout << "Name: " << p.get_first_name() << " " << p.get_last_name() << endl;
    cout << "\nPhysical Traits (0-1 scale):" << endl;
    cout << "Height: " << p.get_height_s() << endl;
    cout << "Eye Color: " << p.get_eye_s() << endl;
    cout << "Hair Color: " << p.get_hair_s() << endl;
    cout << "Gender: " << (p.get_gender_s() > 0.5 ? "Female" : "Male") << endl;
    cout << "Skin Color: " << p.get_skin_s() << endl;
    cout << "\nPersonality Scores (0-1 scale):" << endl;
    cout << "Social: " << p.get_social_s() << endl;
    cout << "Processing: " << p.get_process_s() << endl;
    cout << "Decision Making: " << p.get_decision_s() << endl;
    cout << "Tactics: " << p.get_tactics() << endl;
    cout << "----------------------------------------" << endl;
}

void view_person_info(map<string,Person>& a_map) {
    string id;
    cout << "Enter person ID to view person information: ";
    cin >> id;
    auto it = a_map.find(id);
    if (it != a_map.end()) {
        cout << "\nREFERENCE PERSON:" << endl;
        display_person_info(it->second);
        int k = 3;
        vector<pair<string,float>> similars = find_most_similar(it->second, a_map, k);
        if (!similars.empty()){
            cout << "\nMost similar people (closest first):" << endl;
            for (size_t i = 0; i < similars.size(); ++i){
                const string &other_id = similars[i].first;
                float score = similars[i].second;
                auto it2 = a_map.find(other_id);
                if (it2 != a_map.end()){
                    cout << "\n" << i+1 << ". " << it2->second.get_first_name() << " " << it2->second.get_last_name()
                         << " (ID: " << other_id << ") - similarity score: " << score << endl;
                    cout << "Compared Person's Attributes:" << endl;
                    display_person_info(it2->second);
                }
            }
        } else {
            cout << "No other people in dataset to compare." << endl;
        }
    }
    else {
        cout << "Person not found." << endl;
    }
}

vector<pair<string,float>> find_most_similar(Person& target, map<string,Person>& a_map, int k){
    using Pair = pair<float, string>;
    auto cmp = [](const Pair &a, const Pair &b){ return a.first < b.first; };
    priority_queue<Pair, vector<Pair>, decltype(cmp)> pq(cmp);
    for (const auto &pair : a_map){
        const string &other_id = pair.first;
        const Person &other = pair.second;
        if (other_id == target.get_id()) continue;
        float weight_personality = target.calc_pers_dif(other)/4.0f;
        float weight_physical = target.calc_physical_dif(other)/4.0f;
        float total_weight = (weight_personality * 0.8f + weight_physical * 0.2f);
        if ((int)pq.size() < k) {
            pq.push({total_weight, other_id});
        } else if (total_weight < pq.top().first) {
            pq.pop();
            pq.push({total_weight, other_id});
        }
    }
    vector<pair<string,float>> results;
    while(!pq.empty()){
        results.push_back({pq.top().second, pq.top().first});
        pq.pop();
    }
    reverse(results.begin(), results.end());
    return results;
}
