#ifndef SORTS_HPP
#define SORTS_HPP

#include <iostream>
#include <cmath>

// Merge Sort (Złożoność O(n log n))

template <typename T>
void merge(T* array, T* buffer, int left, int mid, int right, bool ascending) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        bool condition = ascending ? (array[i] <= array[j]) : (array[i] >= array[j]);
        if (condition) buffer[k++] = array[i++];
        else buffer[k++] = array[j++];
    }

    while (i <= mid) buffer[k++] = array[i++];
    while (j <= right) buffer[k++] = array[j++];

    for (i = left; i <= right; i++) array[i] = buffer[i];
}

template <typename T>
void mergeSortRecursive(T* array, T* buffer, int left, int right, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(array, buffer, left, mid, ascending);
        mergeSortRecursive(array, buffer, mid + 1, right, ascending);
        merge(array, buffer, left, mid, right, ascending);
    }
}

// Główny interfejs dla Merge Sort
template <typename T>
void mergeSort(T* array, int size, bool ascending = true) {
    T* buffer = new T[size];
    mergeSortRecursive(array, buffer, 0, size - 1, ascending);
    delete[] buffer;
}



#endif // SORTS_HPP