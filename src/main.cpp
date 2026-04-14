#include "Tester.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "====================================================" << std::endl;
        std::cout << "   PROJEKT PAA - ANALIZA ALGORYTMOW SORTOWANIA" << std::endl;
        std::cout << "====================================================" << std::endl;

        Tester tester;
        tester.runAllTests();

        std::cout << "\nProgram zakonczyl dzialanie pomyslnie." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Wystapil krytyczny blad: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}