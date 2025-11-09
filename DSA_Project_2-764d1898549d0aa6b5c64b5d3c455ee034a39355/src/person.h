#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person {
    private:
        string first_name, last_name, id;
        string input_string;

        // Personality Attributes
        float social_s, process_s, decision_s, tactics_s;

        // Physical Attributes
        float height_s, eye_s, hair_s, gender_s, skin_s;
        
        void set_attributes(); // Function to initialize attributes from input_string
        
    public:
        // attributes initialized to 0.0
        Person() {
            social_s = process_s = decision_s = tactics_s = 0.0f;
            height_s = eye_s = hair_s = gender_s = skin_s = 0.0f;
        }
        Person(string input){
            // Default constructor
            this->input_string = input;
            // Initialize attributes to zero
            this->social_s =  this->process_s = this->decision_s = this->tactics_s = 0.0;
            this->height_s = this->eye_s = this->hair_s = this->gender_s = this->skin_s = 0.0;
            set_attributes();
        } 
        Person(const Person& other) = default; // Copy constructor

        ~Person() = default; // Destructor
        
    float calc_physical_dif(const Person& other);
    float calc_pers_dif(const Person& other);
    float calc_physical_dif_euclidean(const Person& other);
    float calc_pers_dif_euclidean(const Person& other);

    // Getters
    string get_id() const { return id; }
    string get_first_name() const { return first_name; }
    string get_last_name() const { return last_name; }
    float get_social_s() const { return social_s; }
    float get_process_s() const { return process_s; }
    float get_decision_s() const { return decision_s; }
    float get_tactics() const { return tactics_s; }

    float get_height_s() const { return height_s; }
    float get_eye_s() const { return eye_s; }
    float get_hair_s() const { return hair_s; }
    float get_gender_s() const { return gender_s; }
    float get_skin_s() const { return skin_s; }

    //Setters
    void set_id(string id_in) {  id = id_in; }
    void set_first_name(string first_name_in){first_name = first_name_in;}
    void set_last_name(string last_name_in){last_name = last_name_in;}
    void set_social_s(float social_in) { social_s = social_in; }
    void set_process_s(float process_in) { process_s = process_in;}
    void set_decision_s(float decisions_in) { decision_s = decisions_in; }
    void set_tactics(float tactics_in) { tactics_s = tactics_in;}

    void set_height_s(float height_in) { height_s = height_in; }
    void set_eye_s(float eyes_in) { eye_s = eyes_in; }
    void set_hair_s(float hair_in) { hair_s = hair_in;}
    void set_gender_s(float gender_in) { gender_s = gender_in;}
    void set_skin_s(float skin_in) { skin_s = skin_in; }

    
};

#endif // PERSON_H