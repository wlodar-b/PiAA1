import pandas as pd
import matplotlib.pyplot as plt
import os

def generuj_wykresy():
    # 1. Wczytanie danych z pliku CSV
    # separator to średnik, zgodnie z naszą implementacją w C++
    print("Wczytywanie danych z wyniki.csv...")
    try:
        df = pd.read_csv('wyniki.csv', sep=';')
    except FileNotFoundError:
        print("BŁĄD: Nie znaleziono pliku wyniki.csv. Upewnij się, że jesteś w dobrym folderze.")
        return

    # 2. Utworzenie folderu na wykresy (jeśli nie istnieje)
    if not os.path.exists('wykresy'):
        os.makedirs('wykresy')

    # Pobranie unikalnych scenariuszy (Losowe, 25%, Odwrotne, itd.)
    scenariusze = df['Scenariusz'].unique()

    print(f"Znaleziono {len(scenariusze)} scenariuszy. Generowanie wykresów...")

    # 3. Generowanie osobnego wykresu dla każdego scenariusza
    for scenariusz in scenariusze:
        # Filtrujemy dane tylko dla aktualnego scenariusza
        df_scenariusz = df[df['Scenariusz'] == scenariusz]
        
        plt.figure(figsize=(10, 6))
        
        # Pobieramy unikalne algorytmy (Merge Sort, Quick Sort, Intro Sort)
        algorytmy = df_scenariusz['Algorytm'].unique()
        
        # Rysujemy linię dla każdego algorytmu
        for algorytm in algorytmy:
            df_alg = df_scenariusz[df_scenariusz['Algorytm'] == algorytm]
            
            # Parametry wykresu: Oś X to Rozmiar, Oś Y to Czas
            plt.plot(df_alg['Rozmiar'], df_alg['Sredni_Czas_ms'], 
                     marker='o', linewidth=2, markersize=6, label=algorytm)
            
        # 4. Upiększanie wykresu
        plt.title(f'Czas sortowania - {scenariusz}', fontsize=16, fontweight='bold')
        plt.xlabel('Rozmiar tablicy (liczba elementów)', fontsize=12)
        plt.ylabel('Średni czas sortowania [ms]', fontsize=12)
        
        # Formatowanie osi X, aby nie pokazywała notacji naukowej (np. 1e6)
        plt.ticklabel_format(style='plain', axis='x')
        
        plt.legend(fontsize=12)
        plt.grid(True, linestyle='--', alpha=0.7)
        plt.tight_layout()
        
        # 5. Zapis wykresu do pliku (usuwamy znaki specjalne z nazwy pliku)
        bezpieczna_nazwa = scenariusz.replace(' ', '_').replace('%', 'proc')
        sciezka_zapisu = os.path.join('wykresy', f'{bezpieczna_nazwa}.png')
        
        plt.savefig(sciezka_zapisu, dpi=300) # Wysoka jakość 300 DPI idealna do sprawozdania
        plt.close()
        
        print(f" -> Zapisano: {sciezka_zapisu}")

    print("Gotowe! Wszystkie wykresy znajdziesz w folderze 'wykresy'.")

if __name__ == "__main__":
    generuj_wykresy()