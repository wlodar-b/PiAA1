#include "Tester.hpp"
#include "DataGenerator.hpp"
#include "Sorts.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <iomanip>

void copyArray(int* source, int* dest, int size) {
    std::copy(source, source + size, dest);
}

void Tester::runAllTests() {
    std::vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    int trials = 100;
    
    std::vector<std::pair<std::string, double>> scenarios = {
        {"Losowe dane", 0.0},
        {"25% posortowane", 25.0},
        {"50% posortowane", 50.0},
        {"75% posortowane", 75.0},
        {"95% posortowane", 95.0},
        {"99% posortowane", 99.0},
        {"99.7% posortowane", 99.7},
        {"100% posortowane", 100.0},
        {"Odwrotne", -1.0}
    };

    std::ofstream file("wyniki.csv");
    file << "Rozmiar;Scenariusz;Algorytm;Sredni_Czas_ms\n";

    std::cout << "--- ROZPOCZECIE EKSPERYMENTOW ---" << std::endl;

    // MAGIA: Ta zmienna zabrania kompilatorowi usunięcia kodu sortującego!
    volatile long long antiOptimizeSum = 0;

    for (int size : sizes) {
        std::cout << "\nTestowanie rozmiaru: " << size << " elementow..." << std::endl;
        
        int* originalData = new int[size];
        int* copyData = new int[size];

        for (const auto& scenario : scenarios) {
            std::string scenarioName = scenario.first;
            double percentage = scenario.second;

            double timeMerge = 0.0, timeQuick = 0.0, timeIntro = 0.0;

            for (int i = 0; i < trials; i++) {
                // Generowanie danych
                if (scenarioName == "Losowe dane") {
                    DataGenerator::fillRandom(originalData, size);
                } else if (scenarioName == "Odwrotne") {
                    DataGenerator::fillReverseSorted(originalData, size);
                } else if (scenarioName == "100% posortowane") {
                    DataGenerator::fillPartiallySorted(originalData, size, 100.0);
                } else {
                    DataGenerator::fillPartiallySorted(originalData, size, percentage);
                }

                // --- MERGE SORT ---
                copyArray(originalData, copyData, size);
                auto start = std::chrono::steady_clock::now();
                mergeSort(copyData, size);
                auto end = std::chrono::steady_clock::now();
                timeMerge += std::chrono::duration<double, std::milli>(end - start).count();
                antiOptimizeSum += copyData[size / 2]; // Wykorzystujemy wynik, by nie został zignorowany

                // --- QUICK SORT ---
                copyArray(originalData, copyData, size);
                start = std::chrono::steady_clock::now();
                quickSort(copyData, 0, size - 1);
                end = std::chrono::steady_clock::now();
                timeQuick += std::chrono::duration<double, std::milli>(end - start).count();
                antiOptimizeSum += copyData[size / 2]; // Wykorzystujemy wynik

                // --- INTRO SORT ---
                copyArray(originalData, copyData, size);
                start = std::chrono::steady_clock::now();
                introSort(copyData, size);
                end = std::chrono::steady_clock::now();
                timeIntro += std::chrono::duration<double, std::milli>(end - start).count();
                antiOptimizeSum += copyData[size / 2]; // Wykorzystujemy wynik
            }

            timeMerge /= trials;
            timeQuick /= trials;
            timeIntro /= trials;

            file << size << ";" << scenarioName << ";Merge Sort;" << std::fixed << std::setprecision(4) << timeMerge << "\n";
            file << size << ";" << scenarioName << ";Quick Sort;" << std::fixed << std::setprecision(4) << timeQuick << "\n";
            file << size << ";" << scenarioName << ";Intro Sort;" << std::fixed << std::setprecision(4) << timeIntro << "\n";

            std::cout << "  Zakonczono: " << scenarioName << std::endl;
        }

        delete[] originalData;
        delete[] copyData;
    }

    file.close();
    std::cout << "\n--- ZAKONCZONO WSZYSTKIE TESTY ---" << std::endl;
    // Pusty warunek wypisujący sumę, aby upewnić się, że kompilator jej potrzebuje
    if (antiOptimizeSum == -1) std::cout << " ";
}