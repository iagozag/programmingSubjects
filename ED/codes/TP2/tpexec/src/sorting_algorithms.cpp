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
    for(int i = 1; i < n; i++) {
        Pair aux = v[i];
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
        for(int j = i + 1; j < n; j++)
            if(v[j] < v[min]) 
                min = j;

        swap(v[i], v[min]);
    }
}

void quick_sort(Pair* v, int e, int d){
    int i, j;
    partition(e, d, &i, &j, v);
    if(e < j) quick_sort(v, e, j);
    if(i < d) quick_sort(v, i, d);
}

void merge_sort(Pair* v, int e, int d){
    if (e < d){
        int mid = (e+d)/2;
        merge_sort(v, e, mid);
        merge_sort(v, mid+1, d);
        merge(v, e, mid, d);
    }
}

void heap_sort(Pair* v, int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

void my_sort(Pair* v, int n){
    bool sorted = false;
    while (!sorted) {
        sorted = true;

        for (int i = 1; i < n-1; i += 2)
            if(v[i] > v[i + 1]){
                swap(v[i], v[i + 1]);
                sorted = false;
            }

        for(int i = 0; i < n - 1; i += 2)
            if(v[i] > v[i + 1]) {
                swap(v[i], v[i + 1]);
                sorted = false;
            }
    }  
}

// QuickSort
void partition(int e, int d, int* i, int* j, Pair* v){
    Pair x, w;
    *i = e; *j = d;
    x = v[(*i + *j)/2];
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

// MergeSort
void merge(Pair* v, int nl, int mid, int nr) {
    int end1 = mid - nl + 1;
    int end2 = nr - mid;

    auto *lArray = new Pair[end1],
         *rArray = new Pair[end2];

    int i = 0, j = 0, k = nl;
    for(; i < end1; i++)
        lArray[i] = v[nl+i];
    for(; j < end2; j++)
        rArray[j] = v[mid+1+j];

    i = 0, j = 0;
    while(i < end1 && j < end2){
        if(lArray[i] < rArray[j]) v[k] = lArray[i], i++;
        else v[k] = rArray[j], j++;
        k++;
    } 

    for(; i < end1; i++)
        v[k] = lArray[i], k++;
    for(; j < end2; j++)
        v[k] = rArray[j], k++;

    delete[] lArray;
    delete[] rArray;
}

// HeapSort
void heapify(Pair* v, int n, int i){
    int largest = i,
        l = 2 * i + 1,
        r = 2 * i + 2;

    if (l < n && v[l] > v[largest])
        largest = l;

    if (r < n && v[r] > v[largest])
        largest = r;

    if (largest != i) {
        swap(v[i], v[largest]);

        heapify(v, n, largest);
    }
}
