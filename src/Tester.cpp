#include "Tester.hpp"
#include "DataGenerator.hpp"
#include "Sorts.hpp"
#include "Utils.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> // Do formatowania wyjścia

// Funkcja pomocnicza do kopiowania tablic
void copyArray(int* source, int* dest, int size) {
    std::copy(source, source + size, dest);
}

void Tester::runAllTests() {
    std::vector<int> sizes = {10000, 50000, 100000, 500000, 1000000}; // Różne rozmiary tablic do testowania
    int trials = 100; // Liczba prób dla każdego rozmiaru

    // Nazwy naszych scenariuszy testowych
    std::vector<std::pair<std::string, double>> scenarios = {
        {"Losowe dane", 0.0},
        {"25% posortowane", 25.0},
        {"50% posortowane", 50.0},
        {"75% posortowane", 75.0},
        {"95% posortowane", 95.0},
        {"99% posortowane", 99.0},
        {"99.7% posortowane", 99.7},
        {"100% posortowane", 100.0},
        {"Odwrotne", -1.0} // -1 oznacza u nas tablice odwróconą
        };

        std::ofstream file("wyniki.csv");
        file << "Rozmiar;Scenariusz;Algorytm;Średni_czas_ms\n"; // Używamy średnika dla polskiego Excel

        std::cout << "--- ROZPOCZECZECIE EKSPEYMENTÓW ---\n";

        for (int size :sizes) {
            std::cout << "Testowanie rozmiaru: " << size << " elementów...\n";

            // Alokujemy pamięć raz dla danego rozmiaru 
            int* originalData = new int[size];
            int* copyData = new int[size];

            for (const auto& scenario : scenarios) {
                std::string scenarioName = scenario.first;
                double percentage = scenario.second;

                double timeMerge = 0.0;
                double timeQuick = 0.0;
                double timeIntro = 0.0;
                bool allSorted = true; // Flaga do sprawdzenia, czy wszystkie sortowania były poprawne

                for (int i = 0; i < 0; i++) {
                    // 1. Generowanie danych dla danej próby
                    if (scenarioName == "Losowe") {
                        DataGenerator::fillRandom(originalData, size);
                    } else if (scenarioName == "Odwrotne") {
                        DataGenerator::fillReverseSorted(originalData, size);
                    } else {
                        DataGenerator::fillPartiallySorted(originalData, size, percentage);
                    }

                    // Merge Sort
                    copyArray(originalData, copyData, size);
                    auto start = std::chrono::high_resolution_clock::now();
                    mergeSort(copyData, size);
                    auto end = std::chrono::high_resolution_clock::now();
                    timeMerge += std::chrono::duration<double, std::milli>(end - start).count();
                    if (!isSorted(copyData, size)) allSorted = false;

                    // Quick Sort
                    copyArray(originalData, copyData, size);
                    start = std::chrono::high_resolution_clock::now();
                    quickSort(copyData, 0, size - 1);
                    end = std::chrono::high_resolution_clock::now();
                    timeQuick += std::chrono::duration<double, std::milli>(end - start).count();
                    if (!isSorted(copyData, size)) allSorted = false;

                    // Intro Sort
                    copyArray(originalData, copyData, size);
                    start = std::chrono::high_resolution_clock::now();
                    introSort(copyData, size);
                    end = std::chrono::high_resolution_clock::now();
                    timeIntro += std::chrono::duration<double, std::milli>(end - start).count();
                    if (!isSorted(copyData, size)) allSorted = false;
                }

                // Ostrzeżenie, jeśli któreś sortowanie nie posortowało poprawnie
                if (!allSorted) {
                    std::cerr << "BŁĄD: sortowania w scenariuszu: " << scenarioName << " i rozmiarze: " << size << "\n";
                }

                // Obliczanie średnich czasów
                timeMerge /= trials;
                timeQuick /= trials;
                timeIntro /= trials;

                // Zapis do CSV
                file << size << ";" << scenarioName << ";Merge Sort;" << std::fixed << std::setprecision(4) << timeMerge << "\n";
                file << size << ";" << scenarioName << ";Quick Sort;" << std::fixed << std::setprecision(4) << timeQuick << "\n";
                file << size << ";" << scenarioName << ";Intro Sort;" << std::fixed << std::setprecision(4) << timeIntro << "\n";

                std::cout << "  Zakonczono:  " << scenarioName << std::endl;
            }

            delete[] originalData;
            delete[] copyData;
        }

        file.close();
        std::cout << "--- ZAKOŃCZENIE EKSPEYMENTÓW ---\n";
        std::cout << "Wyniki zapisane w pliku: wyniki.csv\n";
}