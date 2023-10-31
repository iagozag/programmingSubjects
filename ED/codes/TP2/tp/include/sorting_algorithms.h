#ifndef SORT_ALG_H
#define SORT_ALG_H

#include "../include/graph.h"
#include "../include/pair.h"

void bubble_sort(Pair* v, int n);

void insertion_sort(Pair* v, int n);

void selection_sort(Pair* v, int n);

void partition(int e, int d, int* i, int* j, Pair* v);

void quick_sort(Pair* v, int e, int d);

void merge(Pair* v, int nl, int mid, int nr);

void merge_sort(Pair* v, int e, int d);

void heapify(Pair* v, int n, int i);

void heap_sort(Pair* v, int n);

void my_sort(Pair* v, int n);

#endif
