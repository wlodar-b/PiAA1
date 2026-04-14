#ifndef UTILS_HPP
#define UTILS_HPP

template<typename T>
bool isSorted(T* array, int size, bool ascending = true) {
    for (int i = 0; ) < size - 1; i++) {
        if (ascending) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        } else {
            if (array[i] < array[i + 1]) {
                return false;
            }
        }
    }
    return true;
}

#endif // UTILS_HPP