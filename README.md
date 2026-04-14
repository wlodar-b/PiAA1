# 📊 Analiza Efektywności Algorytmów Sortowania

Projekt zrealizowany w ramach przedmiotu **Projektowanie i Analiza Algorytmów**. Celem aplikacji jest samodzielna implementacja i zaawansowana analiza wydajnościowa trzech algorytmów sortowania: **Merge Sort**, **Quick Sort** oraz **Intro Sort**.

## 🚀 Opis Projektu

Program generuje duże zbiory danych (od 10 000 do 1 000 000 elementów), a następnie mierzy czas ich sortowania w milisekundach. Aby testy były jak najbardziej miarodajne, każdy scenariusz jest powtarzany **100 razy**, a wynik uśredniany. 

Projekt został zoptymalizowany pod kątem wydajności w C++ i posiada zabezpieczenia przed automatycznym usuwaniem kodu (Dead Code Elimination) przez kompilator, co gwarantuje wysoką dokładność pomiarów.

### ✨ Kluczowe cechy implementacji
* **Szablony (Templates):** Algorytmy są generyczne i potrafią sortować dowolne typy danych, dla których zdefiniowano operatory porównania.
* **Optymalizacja Pamięci (Merge Sort):** Bufor pomocniczy jest alokowany tylko raz na cały proces sortowania, co zapobiega wyciekom pamięci i drastycznie przyspiesza działanie na milionach elementów.
* **Optymalny Pivot (Quick Sort):** Zastosowano wybór środkowego elementu jako osiowego (pivot), co skutecznie chroni algorytm przed degradacją złożoności do O(n^2) w przypadku danych odwrotnie posortowanych.
* **Mechanizm Introspektywny (Intro Sort):** Hybrydowe połączenie Quick Sorta i Heap Sorta – algorytm dynamicznie przełącza się na sortowanie przez kopcowanie, gdy głębokość rekurencji przekroczy limit `2 * log2(N)`.

---

## 📂 Struktura Katalogów

```text
.
├── include/
│   ├── DataGenerator.hpp  # Narzędzia do generowania różnorodnych zestawów danych
│   ├── Sorts.hpp          # Samodzielne implementacje algorytmów sortujących
│   ├── Tester.hpp         # Silnik automatyzujący eksperymenty
│   └── Utils.hpp          # Funkcje pomocnicze (np. weryfikacja poprawności isSorted)
├── src/
│   ├── DataGenerator.cpp
│   ├── main.cpp           # Punkt wejścia programu
│   └── Tester.cpp         # Logika mierzenia czasu i zapisu do pliku
└── README.md