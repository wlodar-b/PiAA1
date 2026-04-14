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

// QUICKSORT (Złożoność: Średnia O(n log n))

template <typename T>
int partition(T* array, int left, int right, bool ascending) {
    T pivot = array[left + (right - left) / 2];
    int i = left, j = right;

    while (i <= j) {
        if (ascending) {
            while (array[i] < pivot) i++;
            while (array[j] > pivot) j--;
        } else {
            while (array[i] > pivot) i++;
            while (array[j] < pivot) j--;
        }
        if (i <= j) {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }
}

template <typename T>
void quickSort(T* array, int left, int right, bool ascending = true) {
    if (left < right) {
        int pivotIndex = partition(array, left, right, ascending);
        if (left < pivotIndex - 1) quickSort(array, left, pivotIndex - 1, ascending);
        if (pivotIndex < right) quickSort(array, pivotIndex, right, ascending);
    }
}

// INTROSORT (Hybryda Quick Sort i Heap Sort)

// Pomocnicza funkcja dla Heap Sort
template <typename T>
void heapify(T* array, int n, int i, int offset, bool ascending) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (ascending) {
        if (l < n && array[offset + l] > array[offset + largest]) largest = l;
        if (r < n && array[offset + r] > array[offset + largest]) largest = r;
    } else {
        if (l < n && array[offset + l] < array[offset + largest]) largest = l;
        if (r < n && array[offset + r] < array[offset + largest]) largest = r;
    }

    if (largest != i) {
        std::swap(array[offset + i], array[offset + largest]);
        heapify(array, n, largest, offset, ascending);
    }
}

template <typename T>
void heapSort(T* array, int left, int right, bool ascending) {
    int n = right - left + 1;
    for (int i = n / 2 - 1; i >= 0; i--) heapify(array, n, i, left, ascending);
    for (int i = n - 1; i > 0; i--) {
        std::swap(array[left], array[left + i]);
        heapify(array, i, 0, left, ascending);
    }
}

template <typename T>
void introSortRecursive(T* array, int left, int right, int depthLimit, bool ascending) {
    int n = right - left + 1;
    if (n <= 1) return;

    if (depthLimit == 0) {
        heapSort(array, left, right, ascending); // Przełącz na Heap Sort
        return;
    }

    int pivotIndex = partition(array, left, right, ascending);
    introSortRecursive(array, left, pivotIndex - 1, depthLimit - 1, ascending);
    introSortRecursive(array, pivotIndex, right, depthLimit - 1, ascending);
}

template <typename T>
void introSort(T* array, int size, bool ascending = true) {
    int depthLimit = 2* std::log2(size); // Standardowy limit głębokości dla Introsort
    introSortRecursive(array, 0, size - 1, depthLimit, ascending);
}

#endif // SORTS_HPP