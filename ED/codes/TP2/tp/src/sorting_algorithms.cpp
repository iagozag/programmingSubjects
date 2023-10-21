#include "../include/sorting_algorithms.h"

void bubble_sort(int *A, int *c, int n){

}

void insertion_sort(int **A, int *c, int n){
    for(int i = 1; i < n; i++){
        int* vert = A[i], key = c[i], j = i-1;
        while(j >= 0 && key < c[j])
            A[j+1] = A[j], c[j+1] = c[j], j--;
        A[j+1] = vert, c[j+1] = key;
    }
}

void selection_sort(int *A, int *c, int n){

}

void quick_sort(int *A, int *c, int n){

}

void merge_sort(int *A, int *c, int n){

}

void heap_sort(int *A, int *c, int n){

}

void my_sort(int *A, int *c, int n){

}
