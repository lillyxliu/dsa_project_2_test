#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
#include "person.h"
#include "userInputTest.h"
#include <limits>



Person user;
person_question_data personality_data_point;
Questions personality_questions_obj;


void Questions::run_test(){
    get_personality_values();
    ask_personality_questions();
    calculate_personality();
    convert_personality_scale();
    get_physical_values();
    ask_physical_questions();
}

void Questions::get_personality_values() {
    //read from csv file and populate 2d_vector
    ifstream data("../data/Questions.csv");
    if(!data.is_open()){
        cout << "Error opening file" << endl;
        return;
    }
    string headers;
    getline(data, headers,'\n'); // 1st line
    
    string row_str;
    
    while(getline(data, row_str, '\n')){
      stringstream ss(row_str);
      string question, category, flipped_str, first_column, second_column;
    
      getline(ss, question, ',');
      getline(ss, category, ',');
      getline(ss, flipped_str, ',');   
      getline(ss, first_column, ',');
      getline(ss, second_column, ',');
      
            personality_data_point.question = question;
            personality_data_point.category = category;
            personality_data_point.flipped = true;  // Reset flipped to true for each new question
            personality_data_point.yes_indicates = first_column;
            personality_data_point.no_indicates = second_column;
      
            if (first_column == "Extraversion" || first_column == "Intuition" || first_column == "Thinking" || first_column == "Perceiving"){
                personality_data_point.flipped = false;
            }

            personality_bank.push_back(personality_data_point);
}
  
}

void Questions::update_score(string& category, int answer, bool flipped) {
    if (flipped) {
        answer = 6 - answer;
    }
    int value = answer - 3; // Normalize to -2 to +2 scale

    if (category == "Social") {
        set_social_score(get_social_score() + value);
    } else if (category == "Processing") {
        set_processing_score(get_processing_score() + value);
    } else if (category == "Decision") {
        set_decision_score(get_decision_score() + value);
    } else if (category == "Tactics") {
        set_tactics_score(get_tactics_score() + value);
    }
}

void Questions::ask_personality_questions(){

cout << "\n---------------------------------------- \nPersonality Test" << endl;

  cout << " \nWe will now begin the questionnaire.\nPlease answer the following questions on a scale from 1 to 5\nWhere 1 means 'Strongly Disagree' and 5 means 'Strongly Agree'." << endl;

  //cin fail method from: https://www.geeksforgeeks.org/cpp/how-to-use-cin-fail-method-in-cpp/ 


    int question_count = personality_bank.size();
    for (int i = 0; i < question_count; i++){
        int answer;
        bool valid_input = false;
        while (!valid_input) {
            cout << "\n----------------------------------------" << endl;
            cout << "Question " << i + 1 << " of " << question_count << endl;
            cout << personality_bank[i].question << ": ";
            cin >> answer;
            if (cin.fail() || answer < 1 || answer > 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            } else {
                valid_input = true;
            }
        }
        personality_bank[i].answer = answer;
        update_score(personality_bank[i].category, personality_bank[i].answer, personality_bank[i].flipped);
    }
}

void Questions::calculate_personality(){
    cout << "\n----------------------------------------" << endl;
    cout << "End of Personality Test" << endl;

    string personalityType = "";


// E or I
if (get_social_score() >= 0) {
    personalityType += "E";
} else {
    personalityType += "I";
}

// N or S
if (get_processing_score() >= 0) {
    personalityType += "N";
} else {
    personalityType += "S";
}

// T or F
if (get_decision_score() >= 0) {
    personalityType += "T";
} else {
    personalityType += "F";
}

// P or J
if (get_tactics_score() >= 0) {
    personalityType += "P";
} else {
    personalityType += "J";
}

cout << "Your personality type is: " << personalityType << endl;
}

void Questions::convert_personality_scale(){ 
    // Convert scores from -10 to +10 scale to 0 to 1 scale
    user.set_social_s((social_score + 10) / 20.0 * 1.0);
    user.set_process_s((processing_score + 10) / 20.0 * 1.0);
    user.set_decision_s((decision_score + 10) / 20.0 * 1.0);
    user.set_tactics((tactics_score + 10) / 20.0 * 1.0);
}

void Questions::get_person_info() {
    cout << "\n----------------------------------------" << endl;
    cout << "Personal Information" << endl;
    
    cout << "\nEnter first name: ";
    cin >> first_name;
    
    cout << "Enter last name: ";
    cin >> last_name;

    // make new id
    string new_id;
    int max_id = 0;

    // Check from largerDataset.csv
    ifstream largeData("../data/LargerDataset.csv");
    if (largeData.is_open()) {
        string line;
        getline(largeData, line); // skip header
        while (getline(largeData, line)) {
            size_t pos = line.find(',');
            pos = line.find(',', pos + 1);
            pos = line.find(',', pos + 1);
            string id = line.substr(line.rfind(',', pos - 1) + 1, pos - line.rfind(',', pos - 1) - 1);
            id.erase(0, id.find_first_not_of('0'));
            max_id = max(max_id, stoi(id));
        }
        largeData.close();
    }

    // Check from dataset.csv
    ifstream smallData("../data/dataset.csv");
    if (smallData.is_open()) {
        string line;
        getline(smallData, line); // skip header
        while (getline(smallData, line)) {
            size_t pos = line.find(',');
            pos = line.find(',', pos + 1);
            pos = line.find(',', pos + 1);
            string id = line.substr(line.rfind(',', pos - 1) + 1, pos - line.rfind(',', pos - 1) - 1);
            id.erase(0, id.find_first_not_of('0'));
            max_id = max(max_id, stoi(id));
        }
        smallData.close();
    }

    // make new id with leading zeros
    new_id = to_string(max_id + 1);
    while (new_id.length() < 8) {
        new_id = "0" + new_id;
    }

    user_id = new_id;

    // store
    user.set_first_name(first_name);
    user.set_last_name(last_name);
    user.set_id(user_id);
    cout << "Your ID: " << user_id << endl;
    cout << "----------------------------------------" << endl;
}

Person Questions::get_user_person() const {
    Person p;
    p.set_first_name(first_name);
    p.set_last_name(last_name);
    p.set_id(user_id);
    p.set_social_s((float)social_score / 20.0f + 0.5f); // assuming -10 to +10 scale
    p.set_process_s((float)processing_score / 20.0f + 0.5f);
    p.set_decision_s((float)decision_score / 20.0f + 0.5f);
    p.set_tactics((float)tactics_score / 20.0f + 0.5f);
    // Set physical traits from global user (which is updated in ask_physical_questions)
    p.set_height_s(user.get_height_s());
    p.set_eye_s(user.get_eye_s());
    p.set_hair_s(user.get_hair_s());
    p.set_gender_s(user.get_gender_s());
    p.set_skin_s(user.get_skin_s());
    return p;
}

bool Questions::lookup_person(const string& search_id, const string& search_first_name, const string& search_last_name) {
    vector<string> files_to_search = {"../data/dataset.csv", "../data/LargerDataset.csv"};
    bool found = false;

    for (const string& filepath : files_to_search) {
        ifstream file(filepath);
        if (!file.is_open()) {
            continue;
        }
        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            stringstream ss(line);
            string fname, lname, id, height, eye_color, hair_color, gender, skin_color, social, processing, decision, tactics;
            getline(ss, fname, ',');
            getline(ss, lname, ',');
            getline(ss, id, ',');
            getline(ss, height, ',');
            getline(ss, eye_color, ',');
            getline(ss, hair_color, ',');
            getline(ss, gender, ',');
            getline(ss, skin_color, ',');
            getline(ss, social, ',');
            getline(ss, processing, ',');
            getline(ss, decision, ',');
            getline(ss, tactics);
            bool id_match = (search_id.empty() || id == search_id);
            bool name_match = (search_first_name.empty() && search_last_name.empty()) || 
                           (fname == search_first_name && lname == search_last_name);
            if (id_match || name_match) {
                found = true;
                first_name = fname;
                last_name = lname;
                user_id = id;
                social_score = (stof(social) * 20.0) - 10;
                processing_score = (stof(processing) * 20.0) - 10;
                decision_score = (stof(decision) * 20.0) - 10;
                tactics_score = (stof(tactics) * 20.0) - 10;
                cout << "\nFound person in database:" << endl;
                cout << "Name: " << first_name << " " << last_name << endl;
                cout << "ID: " << user_id << endl;
                cout << "Physical Traits:" << endl;
                cout << "Height: " << height << endl;
                cout << "Eye Color: " << eye_color << endl;
                cout << "Hair Color: " << hair_color << endl;
                cout << "Gender: " << (stof(gender) > 0.5 ? "Female" : "Male") << endl;
                cout << "Skin Color: " << skin_color << endl;
                cout << "\nPersonality Scores (scaled -10 to +10):" << endl;
                cout << "Social: " << social_score << endl;
                cout << "Processing: " << processing_score << endl;
                cout << "Decision: " << decision_score << endl;
                cout << "Tactics: " << tactics_score << endl;
                break;
            }
        }
        file.close();
        if (found) break;
    }
    if (!found) {
        cout << "No matching person found in the database." << endl;
    }
    return found;
}

void Questions::get_physical_values() {
    // First get user's personal information
    get_person_info();
    ifstream data("../data/QuestionsPhysical.csv");
    if (!data.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    string headers;
    getline(data, headers); // Skip header line

    string line;
    while (getline(data, line)) {
        if (line.empty()) continue;
        if (line.front() == '"') line.erase(0, 1);
        if (!line.empty() && line.back() == '"') line.pop_back();
        PhysicalQuestion pq;
        string curr_question = line;
        size_t pos = curr_question.find(" a)");
        if (pos != string::npos) {
            pq.question = curr_question.substr(0, pos);
            string options = curr_question.substr(pos + 1);
            char current_label = 'a';
            while (true) {
                string label = string(1, current_label) + ")";
                size_t start = options.find(label);
                if (start == string::npos) break;
                size_t next = options.find(" " + string(1, current_label + 1) + ")", start + 2);
                string choice = (next == string::npos)
                    ? options.substr(start + 2)
                    : options.substr(start + 2, next - (start + 2));
                pq.options.push_back(choice);
                current_label++;
            }
        } else {
            pq.question = curr_question;
        }
        physical_bank.push_back(curr_question);
        physical_questions.push_back(pq);
    }
}



// string npos from:  https://www.geeksforgeeks.org/cpp/stringnpos-in-c-with-examples/ 
string get_valid_height() {
    string height;

    while (true) {
        cout << "Enter your height (example: 5'9): ";
        getline(cin >> ws, height);

        // remove spaces
        height.erase(remove(height.begin(), height.end(), ' '), height.end());

        // find apostrophe
        size_t apostrophe_position = height.find('\'');

        // check format
        if (apostrophe_position == string::npos || apostrophe_position == 0 || apostrophe_position == height.length() - 1) {
            cout << "Invalid format. Please use the correct format.\n";
            continue;
        }

        // get feet and inches
        string feet = height.substr(0, apostrophe_position);
        string inches = height.substr(apostrophe_position + 1);

        bool valid = true;

        // check that both are numbers
        for (char c : feet)
            if (!isdigit(c)) valid = false;
        for (char c : inches)
            if (!isdigit(c)) valid = false;

        if (!valid) {
            cout << "Invalid format. Please use numbers only, like 5'9.\n";
            continue;
        }

        return height; // valid input
    }
}

    // Convert height like "5'9" to 0.0-1.0 scale (clamped to a reasonable range)
    double convert_height_to_scale(const string& h) {
        size_t pos = h.find('\'');
        if (pos == string::npos) return 0.0;
        try {
            int feet = stoi(h.substr(0, pos));
            int inches = stoi(h.substr(pos + 1));
            int totalInches = feet * 12 + inches;
            const int min_inches = 48; // 4'0"
            const int max_inches = 78; // 6'6"
            if (totalInches < min_inches) totalInches = min_inches;
            if (totalInches > max_inches) totalInches = max_inches;
            return double(totalInches - min_inches) / double(max_inches - min_inches);
        } catch (...) {
            return 0.0;
        }
    }


void Questions::ask_physical_questions() {
    cout << "\n----------------------------------------" << endl;
    cout << "Physical Test" << endl;
    cout << "\nWe will now ask a few physical-related questions." << endl;

    for (int i = 0; i < physical_questions.size(); i++) {
        PhysicalQuestion& pq = physical_questions[i];
        cout << "\n----------------------------------------" << endl;
        cout << "Question " << i + 1 << ": " << pq.question << endl;
        if (!pq.options.empty()) {
            char current_label = 'a';
            for (const auto& option : pq.options) {
                cout << "  " << current_label << ") " << option << endl;
                current_label++;
            }
            char user_choice;
            bool valid = false;
            while (!valid) {
                cout << "Enter your choice (a-" << char('a' + pq.options.size() - 1) << "): ";
                cin >> user_choice;
                if (user_choice >= 'a' && user_choice < 'a' + pq.options.size()) {
                    valid = true;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
            pq.user_answer = user_choice;
            string q = pq.question;
            transform(q.begin(), q.end(), q.begin(), ::tolower);
            if (q.find("gender") != string::npos) {
                user.set_gender_s(static_cast<float>(convert_physical_scale("gender", user_choice)));
            }
            else if (q.find("eye") != string::npos || q.find("eyes") != string::npos) {
                user.set_eye_s(static_cast<float>(convert_physical_scale("eyes", user_choice)));
            }
            else if (q.find("race") != string::npos || q.find("skin") != string::npos) {
                user.set_skin_s(static_cast<float>(convert_physical_scale("race", user_choice)));
            }
            else if (q.find("hair") != string::npos) {
                user.set_hair_s(static_cast<float>(convert_physical_scale("hair", user_choice)));
            }
        } else {
            if (pq.question.find("tall") != string::npos || pq.question.find("height") != string::npos) {
                string valid_height = get_valid_height();
                pq.options.push_back(valid_height);
                pq.user_answer = '-';
                user.set_height_s(static_cast<float>(convert_height_to_scale(valid_height)));
            } else {
                cout << "Your answer: ";
                string user_input;
                getline(cin >> ws, user_input);
                pq.options.push_back(user_input);
                pq.user_answer = '-';
            }
        }
    }
    cout << "\n----------------------------------------" << endl;
    cout << "Here are your responses:\n\n";
    for (const auto& pq : physical_questions) {
        cout << pq.question << endl;
        if (pq.user_answer != '-') {
            int index = pq.user_answer - 'a';
            cout << "  You chose: " << pq.user_answer << ") " << pq.options[index] << endl;
        } else {
            cout << "  Your answer: " << pq.options[0] << endl;
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "End of Physical Test" << endl;
}


double Questions::convert_physical_scale(const string& question_type, char letter) {
    int num_options = 0;

    // Determine number of options based on question type
    if (question_type == "gender") {
        num_options = 3; // a-c
    } 
    else if (question_type == "eyes") {
        num_options = 10; // a-j
    } 
    else if (question_type == "race") {
        num_options = 6; // a-f
    }
    else if (question_type == "hair") {
        num_options = 8; // a-h
    } 
    else {
        return -1.0; // unknown question type
    }
    int index = letter - 'a';
    if(index < 0 || index >= num_options) return -1.0;
    return static_cast<double>(index) / (num_options - 1);
}