
using namespace std;
#include <map>
#include <vector>
#include <string>
#include "dataStructureOne.h"
#include "person.h"
#include <algorithm>
#include "functions.h"


void heapify(vector<string>& vector_id, Person& p_source, int n, int i , map<string,Person>& a_map, int type){
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    float smallest_value = id_to_value_type(vector_id[smallest], p_source, a_map, type);
    if (l < n) {
        float left_value = id_to_value_type(vector_id[l], p_source, a_map, type);
        if(left_value > smallest_value){
            smallest = l;
            smallest_value = left_value;
        }
    }
    if (r < n) {
        float right_value = id_to_value_type(vector_id[r], p_source, a_map, type);
        if(right_value > smallest_value){
            smallest = r;
            smallest_value = right_value;
        }
    }
    if (smallest != i) {
        swap(vector_id[i], vector_id[smallest]);
        heapify(vector_id, p_source, n, smallest, a_map, type);
    }
}

void heap_sort(vector<string>& vector_id, Person& source_p, map<string,Person>& a_map, int type){
    int n = vector_id.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vector_id, source_p, n, i , a_map, type);
    for (int i = n - 1; i > 0; i--) {
        swap(vector_id[0], vector_id[i]);
        heapify(vector_id, source_p, i, 0, a_map, type);
    }
}

