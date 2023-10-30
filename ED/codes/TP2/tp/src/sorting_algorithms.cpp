#include "../include/sorting_algorithms.h"

#include <numeric>
using namespace std;

void bubble_sort(Pair* v, int n){
    for(int i = 0; i < n-1; i++)
        for(int j = 1; j < n-i; j++)
            if (v[j] < v[j-1]) 
                swap(v[j-1], v[j]);
}

void insertion_sort(Pair* v, int n){
    Pair aux;
    for(int i = 1; i < n; i++) {
        aux = v[i];
        int j = i - 1;
        while (( j >= 0 ) && (aux < v[j])) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

void selection_sort(Pair *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
        if (v[j] < v[min])
            min = j;
        }
        swap(v[i], v[min]);
    }
}

void partiton(int e, int d, int* i, int* j, Pair* v);

void sort(int e, int d, Pair* v);

void quick_sort(Pair* v, int n){
    sort(0, n-1, v);
}

void Merge(Pair* v, int nl, int mid, int nr);

void merge_sort(Pair* v, int e, int d){
    if (e < d){
        int mid = (e+d)/2;
        merge_sort(v, e, mid);
        merge_sort(v, mid+1, d);
        Merge(v, e, mid, d);
    }
}

void redo(int e, int d, Pair* v){
    int i = e, j = i * 2;
    Pair x = v[i];
    while (j <= d){
        if (j < d)
            if (v[j] < v[j+1]) j++;
        if (x >= v[j]) break;
        v[i] = v[j];
        i = j; 
        j = i *2;
    }
    v[i] = x;
}

void heap_sort(Pair* v, int n){
    int e = n/2+1;
    while(e > 1){
        e--;
        redo(e, n, v);
    }
}

void my_sort(Pair* v, int n){

}

// QuickSort
void partiton(int e, int d, int* i, int* j, Pair* v){
    Pair x, w;
    *i = e; *j = d;
    x = v[(*i + *j)/2]; /* obtem o pivo x */
    do
    { 
        while (x > v[*i]) (*i)++;
        while (x < v[*j]) (*j)--;
        if (*i <= *j){ 
		    w = v[*i]; v[*i] = v[*j]; v[*j] = w;
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

void sort(int e, int d, Pair* v){
    int i, j;
    partiton(e, d, &i, &j, v);
    if(e < j) sort(e, j, v);
    if(i < d) sort(i, d, v);
}

// MergeSort
void Merge(Pair* v, int nl, int mid, int nr) {
    int subArrayOne = mid - nl + 1;
    int subArrayTwo = nr - mid;

    auto *lArray = new Pair[subArrayOne],
         *rArray = new Pair[subArrayTwo];

    int i = 0, j = 0, k = 0;
    for(; i < subArrayOne; i++)
        lArray[i] = v[nl+i];
    for(; j < subArrayTwo; j++)
        rArray[j] = v[mid+1+j];

    i = 0, j = 0;
    while(i < nl && j < nr){
        if(lArray[i] < rArray[j])
            v[k] = lArray[i], i++;
        else
            v[k] = rArray[j], j++;
        k++;
    } 

    if(k < nl+nr){
        for(; i < nl; i++)
            v[k] = lArray[i], k++;
        for(; j < nr; j++)
            v[k] = rArray[j], k++;
    }
}
