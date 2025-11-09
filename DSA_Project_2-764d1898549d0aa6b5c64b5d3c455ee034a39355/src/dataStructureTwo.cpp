using namespace std;
#include <map>
#include <vector>
#include <string>
#include "dataStructureTwo.h"
#include "functions.h"


void quick_sort(vector<string>& vector_id, int low, int high, Person& source_p, map<string, Person>& a_map, int type) {
    if (low < high) {
        int pivot = partition(vector_id, low, high, source_p, a_map, type);
        quick_sort(vector_id, low, pivot - 1, source_p, a_map, type);
        quick_sort(vector_id, pivot + 1, high, source_p, a_map, type);
    }
}

int partition_pairs(vector<pair<string,float>>& vec, int low, int high) {
    float pivot_value = vec[low].second;
    int up = low;
    int down = high;
    while (up < down) {
        while (up < high && vec[up].second <= pivot_value){
            up++;
        }
        while (vec[down].second > pivot_value){ 
            down--;
        }
        if (up < down){
            swap(vec[up], vec[down]);
        }
    }
    swap(vec[low], vec[down]);
    return down;
}

int partition(vector<string>& vector_id, int low, int high, Person& source_p, map<string, Person>& a_map, int type) {
    string pivot_id = vector_id[low];
    float pivot_value = id_to_value_type(pivot_id, source_p, a_map, type);
    int left = low - 1;
    int right = high + 1;
    while (true) {
        do {
            left++;
        } while (id_to_value_type(vector_id[left], source_p, a_map, type) < pivot_value);
        do {
            right--;
        } while (id_to_value_type(vector_id[right], source_p, a_map, type) > pivot_value);
        if (left >= right)
            return right;
        swap(vector_id[left], vector_id[right]);
    }
}
    void quick_sort_pairs(vector<pair<string,float>>& vec, int low, int high) {
    if (low < high) {
        int pivot = partition_pairs(vec, low, high);
        quick_sort_pairs(vec, low, pivot - 1);
        quick_sort_pairs(vec, pivot + 1, high);
    }
}
