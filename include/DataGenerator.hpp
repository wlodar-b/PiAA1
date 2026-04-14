#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

#include <vector>

class DataGenerator {
public:
    // Generuje tablicę liczb losowych
    static void fillRandom(int* array, int size, int minVal = 1, int maxVal = 1000000);

    // Generuje tablicę częściowo posortowaną
    static void fillPartiallySorted(int* array, int size, double percentage);

    // Generuje tablicę posortowaną malejąco
    static void fillReverseSorted(int* array, int size);

};

#endif // DATA_GENERATOR_HPP