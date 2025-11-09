#include "person.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


void Person::set_attributes(){
    // cout << input_string << endl; //tester
    vector<string> tokens;
    stringstream ss(input_string);
    string token; 
    
    while(getline(ss, token, ',')){
        tokens.push_back(token);
    }

    if(tokens.size() != 12){
        cerr << "Error: Invalid input string format." << endl;
        return;
    }   
    /* citation: 
    getline string: https://www.geeksforgeeks.org/cpp/getline-string-c/ 
    string to float: https://en.cppreference.com/w/cpp/string/basic_string/stof
    */
    first_name = tokens[0];
    last_name = tokens[1];
    id = tokens[2];
    height_s = stof(tokens[3]);
    eye_s = stof(tokens[4]);
    hair_s = stof(tokens[5]);
    gender_s = stof(tokens[6]);
    skin_s = stof(tokens[7]);
    social_s = stof(tokens[8]);
    process_s = stof(tokens[9]);
    decision_s = stof(tokens[10]);
    tactics_s = stof(tokens[11]);

}

float Person::calc_physical_dif(const Person& other){
    float physical_dif = 0.0;
    physical_dif = abs(height_s - other.height_s) +
    abs(eye_s - other.eye_s) + abs(hair_s - other.hair_s)  + abs(skin_s - other.skin_s);
    // gender_s difference excluded
    return physical_dif;
};

float Person::calc_pers_dif(const Person& other){
    float pers_dif = 0.0;
    pers_dif = abs(social_s - other.social_s) + abs(process_s - other.process_s) +
    abs(decision_s - other.decision_s) + abs(tactics_s - other.tactics_s);
    return pers_dif;
};

float Person::calc_physical_dif_euclidean(const Person& other){
    float physical_dif = 0.0;
    physical_dif = pow(height_s - other.height_s,2) + pow(eye_s - other.eye_s,2) +
    pow(hair_s - other.hair_s,2) + pow(skin_s- other.skin_s,2);
    // gender_s difference excluded
    physical_dif = sqrt(physical_dif);
    return physical_dif;
};

float Person::calc_pers_dif_euclidean(const Person& other){
    float pers_dif = 0.0;
    pers_dif = pow(social_s - other.social_s,2) + pow(process_s - other.process_s,2) +
    pow(decision_s - other.decision_s,2) + pow(tactics_s - other.tactics_s,2);
    pers_dif = sqrt(pers_dif); 
    return pers_dif;
};


