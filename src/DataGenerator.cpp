#include "DataGenerator.hpp"
#include <random>
#include <algorithm>
#include <functional>

void DataGenerator::fillRandom(int* array, int size, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);

    for (int i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }
}

void DataGenerator::fillPartiallySorted(int* array, int size, double percentage) {
    // Najpierw wypełniamy tablicę losowymi liczbami
    fillRandom(array, size);

    // Obliczamy liczbę elementów, które mają być posortowane
    int elementToSort = static_cast<int>(size * (percentage / 100.0));

    // Srtujemy tylko wybrany fragment początkowy
    // Używamy bibliotecznego sortowania, bo to tylko do przygotowania danych do testów
    std::sort(array, array + elementToSort);
}

void DataGenerator::fillReverseSorted(int* array, int size) {
    // Wypełniamy tablicę losowymi liczbami
    fillRandom(array, size);

    // Sortujemy tablicę w porządku malejącym
    std::sort(array, array + size, std::greater<int>());
}
