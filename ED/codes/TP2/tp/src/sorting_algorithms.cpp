#include "../include/sorting_algorithms.h"
#include "../include/memlog.h"

#include <numeric>
using namespace std;

void bubble_sort(Pair* v, int n){
    for(int i = 0; i < n-1; i++)
        for(int j = 1; j < n-i; j++){
            // Monitor memory read
            leMemLog((long int)(&(v[j])), sizeof(double), 0);
            leMemLog((long int)(&(v[j - 1])), sizeof(double), 0);
            
            if (v[j] < v[j-1]) 
                swap(v[j-1], v[j]);
            
            // Monitor memory write
            escreveMemLog((long int)(&(v[j - 1])), sizeof(double), 0);
            escreveMemLog((long int)(&(v[j])), sizeof(double), 0);
        }
}

void insertion_sort(Pair* v, int n){
    for(int i = 1; i < n; i++) {
        Pair aux = v[i];
        int j = i - 1;
        while ((j >= 0) && (aux < v[j])) {
            // Monitor memory read
            leMemLog((long int)(&(v[j])), sizeof(double), 0);
            
            v[j + 1] = v[j];
            
            // Monitor memory write
            escreveMemLog((long int)(&(v[j + 1])), sizeof(double), 0);
            
            j--;
        }
        v[j + 1] = aux;
        
        // Monitor memory write
        escreveMemLog((long int)(&(v[j + 1])), sizeof(double), 0);
    }
}

void selection_sort(Pair *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
            // Monitor memory read
            leMemLog((long int)(&(v[j])), sizeof(double), 0);
            leMemLog((long int)(&(v[min])), sizeof(double), 0);
            
            if(v[j] < v[min]) 
                min = j;
        }
        swap(v[i], v[min]);
        
        // Monitor memory write
        escreveMemLog((long int)(&(v[i])), sizeof(double), 0);
        escreveMemLog((long int)(&(v[min])), sizeof(double), 0);
    }
}

void quick_sort(Pair* v, int e, int d){
    int i, j;
    partition(e, d, &i, &j, v);
    if(e < j) {
        // Monitor memory read
        leMemLog((long int)(&(v[e])), (j - e + 1) * sizeof(double), 0);
        
        quick_sort(v, e, j);
    }
    if(i < d) {
        // Monitor memory read
        leMemLog((long int)(&(v[i])), (d - i + 1) * sizeof(double), 0);
        
        quick_sort(v, i, d);
    }
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
    for (int i = n / 2 - 1; i >= 0; i--) {
        // Monitor memory read
        leMemLog((long int)(&(v[i])), sizeof(double), 0);
        
        heapify(v, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        // Monitor memory read
        leMemLog((long int)(&(v[0])), sizeof(double), 0);
        leMemLog((long int)(&(v[i])), sizeof(double), 0);
        
        swap(v[0], v[i]);
        
        // Monitor memory write
        escreveMemLog((long int)(&(v[0])), sizeof(double), 0);
        escreveMemLog((long int)(&(v[i])), sizeof(double), 0);
        
        heapify(v, i, 0);
    }
}

void my_sort(Pair* v, int n){
    bool sorted = false;
    while (!sorted) {
        sorted = true;

        for (int i = 1; i < n-1; i += 2) {
            // Monitor memory read
            leMemLog((long int)(&(v[i])), sizeof(double), 0);
            leMemLog((long int)(&(v[i + 1])), sizeof(double), 0);
            
            if(v[i] > v[i + 1]) {
                swap(v[i], v[i + 1]);
                sorted = false;
            }
            
            // Monitor memory write
            escreveMemLog((long int)(&(v[i])), sizeof(double), 0);
            escreveMemLog((long int)(&(v[i + 1])), sizeof(double), 0);
        }

        for(int i = 0; i < n - 1; i += 2) {
            // Monitor memory read
            leMemLog((long int)(&(v[i])), sizeof(double), 0);
            leMemLog((long int)(&(v[i + 1])), sizeof(double), 0);
            
            if(v[i] > v[i + 1]) {
                swap(v[i], v[i + 1]);
                sorted = false;
            }
            
            // Monitor memory write
            escreveMemLog((long int)(&(v[i])), sizeof(double), 0);
            escreveMemLog((long int)(&(v[i + 1])), sizeof(double), 0);
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
        while (x > v[*i]) {
            // Monitor memory read
            leMemLog((long int)(&(v[*i])), sizeof(double), 0);
            
            (*i)++;
        }
        
        while (x < v[*j]) {
            // Monitor memory read
            leMemLog((long int)(&(v[*j])), sizeof(double), 0);
            
            (*j)--;
        }
        
        if (*i <= *j) { 
            w = v[*i]; 
            v[*i] = v[*j]; 
            v[*j] = w;
            
            // Monitor memory write
            escreveMemLog((long int)(&(v[*i])), sizeof(double), 0);
            escreveMemLog((long int)(&(v[*j])), sizeof(double), 0);
            
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// MergeSort
void merge(Pair* v, int nl, int mid, int nr) {
    int end1 = mid - nl + 1;
    int end2 = nr - mid;

    auto *lArray = new Pair[end1];
    auto *rArray = new Pair[end2];

    int i = 0, j = 0, k = nl;

    for(; i < end1; i++) {
        leMemLog((long int)(&(v[nl + i])), sizeof(double), 0);
        lArray[i] = v[nl + i];
    }

    for(; j < end2; j++) {
        leMemLog((long int)(&(v[mid + 1 + j])), sizeof(double), 0);
        rArray[j] = v[mid + 1 + j];
    }

    i = 0, j = 0;
    while(i < end1 && j < end2){
        if(lArray[i] < rArray[j]) {
            v[k] = lArray[i];
            i++;
        } else {
            v[k] = rArray[j];
            j++;
        }
        k++;

        escreveMemLog((long int)(&(v[k])), sizeof(double), 0);
    }

    for(; i < end1; i++) {
        v[k] = lArray[i];
        k++;
        
        escreveMemLog((long int)(&(v[k])), sizeof(double), 0);
    }

    for(; j < end2; j++) {
        v[k] = rArray[j];
        k++;

        escreveMemLog((long int)(&(v[k])), sizeof(double), 0);
    }

    delete[] lArray;
    delete[] rArray;
}

// HeapSort
void heapify(Pair* v, int n, int i){
    int largest = i,
        l = 2 * i + 1,
        r = 2 * i + 2;

    if (l < n && v[l] > v[largest]) {
        // Monitor memory read
        leMemLog((long int)(&(v[l])), sizeof(double), 0);
        leMemLog((long int)(&(v[largest])), sizeof(double), 0);
        
        largest = l;
    }

    if (r < n && v[r] > v[largest]) {
        // Monitor memory read
        leMemLog((long int)(&(v[r])), sizeof(double), 0);
        leMemLog((long int)(&(v[largest])), sizeof(double), 0);
        
        largest = r;
    }

    if (largest != i) {
        swap(v[i], v[largest]);

        // Monitor memory write
        escreveMemLog((long int)(&(v[i])), sizeof(double), 0);
        escreveMemLog((long int)(&(v[largest])), sizeof(double), 0);
        
        heapify(v, n, largest);
    }
}
