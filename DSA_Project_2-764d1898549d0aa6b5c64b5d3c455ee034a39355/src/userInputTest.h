#include <string>
#include <vector>
using namespace std;


struct person_question_data
{
    // Member variables
    string question;
    string category;
    bool flipped;
    string yes_indicates;
    string no_indicates;
    int answer;

    // Default constructor
    person_question_data() {
        question = "";
        category = "";
        flipped = true;
        yes_indicates = "";
        no_indicates = "";
        answer = 0;
    }

    // Constructor
    person_question_data(string& question, string& category, bool flipped, string& yes_indicates, string& no_indicates, int answer = 0) {    
    this->question = question;
    this->category = category;
    this->flipped = flipped;
    this->yes_indicates = yes_indicates;
    this->no_indicates = no_indicates;
    this->answer = answer;
}


    // Copy constructor
    person_question_data(const person_question_data& other) {
        question = other.question;
        category = other.category;
        flipped = other.flipped;
        yes_indicates = other.yes_indicates;
        no_indicates = other.no_indicates;
        answer = other.answer;
    }

    // Destructor
    ~person_question_data() {
        // no dynamic memory to free
    }
};

struct PhysicalQuestion
{
    string question;
    vector<string> options;
    char user_answer = '-';

    // Default constructor
    PhysicalQuestion() : question(""), options(), user_answer('-') {}
    
    // Parameterized constructor
    PhysicalQuestion(const string& q, const vector<string>& opts, char ans = '-')
        : question(q), options(opts), user_answer(ans) {}
    
    // Copy constructor
    PhysicalQuestion(const PhysicalQuestion& other) = default;
    
    // Destructor
    ~PhysicalQuestion() = default;
};



class Questions {
    public:
        Questions() : social_score(0), processing_score(0), decision_score(0), tactics_score(0) {}
        Questions(const Questions& other) 
            : personality_bank(other.personality_bank),
              physical_bank(other.physical_bank),
              physical_questions(other.physical_questions),
              social_score(other.social_score),
              processing_score(other.processing_score),
              decision_score(other.decision_score),
              tactics_score(other.tactics_score) {}
        Questions& operator=(const Questions& other) {
            if (this != &other) {
                personality_bank = other.personality_bank;
                physical_bank = other.physical_bank;
                physical_questions = other.physical_questions;
                social_score = other.social_score;
                processing_score = other.processing_score;
                decision_score = other.decision_score;
                tactics_score = other.tactics_score;
            }
            return *this;
        }
        ~Questions() = default;


       
        void run_test();

        // Personality Test
        void get_personality_values();
        void ask_personality_questions();
        void update_score(string& category, int answer, bool flipped);
        void calculate_personality();
        void convert_personality_scale();

        // Physical Test
        void get_physical_values();
        void ask_physical_questions();
        double convert_physical_scale(const string& question_type, char letter);


        // Getters
        int get_social_score(){ return social_score; }
        int get_processing_score(){ return processing_score; }
        int get_decision_score(){ return decision_score; }
        int get_tactics_score(){ return tactics_score; }

        // Setters
        void set_social_score(int score){ social_score = score; }
        void set_processing_score(int score){ processing_score = score; }
        void set_decision_score(int score){ decision_score = score; }
        void set_tactics_score(int score){ tactics_score = score; }

        // User Info
        string get_first_name() const { return first_name; }
        string get_last_name() const { return last_name; }
        string get_user_id() const { return user_id; }
        Person get_user_person() const;
        void get_person_info();
        bool lookup_person(const string& search_id = "", const string& search_first_name = "", const string& search_last_name = "");
    
        private:
        string first_name;
        string last_name;
        string user_id;
        vector<person_question_data> personality_bank;
        vector<string> physical_bank;
        vector<PhysicalQuestion> physical_questions;
        int social_score = 0;
        int processing_score = 0;
        int decision_score = 0;
        int tactics_score = 0;
};


