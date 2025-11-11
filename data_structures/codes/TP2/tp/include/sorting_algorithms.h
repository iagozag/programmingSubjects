#ifndef SORT_ALG_H
#define SORT_ALG_H

#include "../include/graph.h"
#include "../include/pair.h"

/**
 * @brief Função para ordenar um array de pares usando o algoritmo Bubble Sort.
 * @param v O array de pares.
 * @param n O número de elementos no array.
 */
void bubble_sort(Pair* v, int n);

/**
 * @brief Função para ordenar um array de pares usando o algoritmo Insertion Sort.
 * @param v O array de pares.
 * @param n O número de elementos no array.
 */
void insertion_sort(Pair* v, int n);

/**
 * @brief Função para ordenar um array de pares usando o algoritmo Selection Sort.
 * @param v O array de pares.
 * @param n O número de elementos no array.
 */
void selection_sort(Pair* v, int n);

/**
 * @brief Função auxiliar para particionar um array de pares para o Quick Sort.
 * @param e O índice do primeiro elemento.
 * @param d O índice do último elemento.
 * @param i Um ponteiro para o índice i.
 * @param j Um ponteiro para o índice j.
 * @param v O array de pares.
 */
void partition(int e, int d, int* i, int* j, Pair* v);

/**
 * @brief Função para ordenar um array de pares usando o algoritmo Quick Sort.
 * @param v O array de pares.
 * @param e O índice do primeiro elemento.
 * @param d O índice do último elemento.
 */
void quick_sort(Pair* v, int e, int d);

/**
 * @brief Função auxiliar para mesclar dois subarrays em um array maior para o Merge Sort.
 * @param v O array de pares.
 * @param nl O número de elementos no subarray esquerdo.
 * @param mid O índice do meio do array.
 * @param nr O número de elementos no subarray direito.
 */
void merge(Pair* v, int nl, int mid, int nr);

/**
 * @brief Função para ordenar um array de pares usando o algoritmo Merge Sort.
 * @param v O array de pares.
 * @param e O índice do primeiro elemento.
 * @param d O índice do último elemento.
 */
void merge_sort(Pair* v, int e, int d);

/**
 * @brief Função auxiliar para construir um heap binário a partir de um array de pares para o Heap Sort.
 * @param v O array de pares.
 * @param n O número de elementos no array.
 * @param i O índice de raiz do heap.
 */
void heapify(Pair* v, int n, int i);

/**
 * @brief Função para ordenar um array de pares usando o algoritmo Heap Sort.
 * @param v O array de pares.
 * @param n O número de elementos no array.
 */
void heap_sort(Pair* v, int n);

/**
 * @brief Função personalizada para ordenar um array de pares.
 * @param v O array de pares.
 * @param n O número de elementos no array.
 */
void my_sort(Pair* v, int n);

#endif
