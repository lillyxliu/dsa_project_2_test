#ifndef DATASTRUCTUREONE_H
#define DATASTRUCTUREONE_H
using namespace std;
#include <map>
#include <vector>
#include <string>
#include "person.h"
#pragma once



void heapify(vector<string>& vector_id, Person& p_source, int n, int i , map<string,Person>& a_map, int type);
void heap_sort(vector<string>& vector_id, Person& source_p, map<string,Person>& a_map, int type);
template <typename T>
void heapify_generic(vector<T>& vector_gen, int n, int i, bool ascending){
    int extreme = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(ascending){
        if (l < n && vector_gen[l].second > vector_gen[extreme].second){
            extreme = l;
        } if (r < n && vector_gen[r].second > vector_gen[extreme].second){
            extreme = r;
        }
    }else{
        if(l < n && vector_gen[l].second < vector_gen[extreme].second){
            extreme = l;
        } if(r < n &&  vector_gen[r].second < vector_gen[extreme].second){
            extreme = r;    
        }
    }
    if (extreme != i) {
        swap(vector_gen[i], vector_gen[extreme]);
        heapify_generic(vector_gen, n, extreme, ascending);
    }
}
template <typename T>
void heap_sort_generic(vector<T>& vector_gen , bool ascending){
    int n = vector_gen.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_generic(vector_gen, n, i, ascending);
    for (int i = n - 1; i > 0; i--) {
        swap(vector_gen[0], vector_gen[i]);
        heapify_generic(vector_gen, i, 0, ascending);
    }
}


#endif 