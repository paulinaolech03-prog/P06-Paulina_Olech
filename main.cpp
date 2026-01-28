#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generowanie losowych danych testowych
void Generuj(int *tab, int n, int nmax) {
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % nmax;
    }
}

// Wyœwietlanie tablicy
void Wypisz(int *tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

//ALGORYTMY (Wersja Naiwna i Ulepszona)


void SzukajPodtablicNaiwny(int M, int N, int k, int **A) {
    if (M >= 2 && N >= 2) {
        for (int i = 0; i <= M - 2; i++) {
            for (int j = 0; j <= N - 2; j++) {
                int suma = A[i][j] + A[i][j+1] + A[i+1][j] + A[i+1][j+1];
                if (suma > k) {
                }
            }
        }
    } else {
        printf("Brak podtablic 2x2\n");
    }
}


void SzukajPodtablicUlepszony(int M, int N, int k, int **A) {
    if (M < 2 || N < 2) return;
    for (int i = 0; i <= M - 2; i++) {
        int suma = A[i][0] + A[i][1] + A[i+1][0] + A[i+1][1];
        for (int j = 0; j <= N - 2; j++) {
            if (suma > k) { /* Wynik */ }
            if (j < N - 2) {
                // Aktualizacja sumy: odejmij lew¹ kolumnê, dodaj praw¹
                suma = suma - (A[i][j] + A[i+1][j]) + (A[i][j+2] + A[i+1][j+2]);
            }
        }
    }
}



void TestyNiewygodne() {
    printf("--- 2.3.2. Testy niewygodnych zestawow danych ---\n");

    // Test 1: Macierz za ma³a
    int r1 = 1, c1 = 3;
    int **t1 = (int **)malloc(r1 * sizeof(int *));
    t1[0] = (int *)malloc(c1 * sizeof(int));
    printf("Test 1 (Macierz 1x3): ");
    SzukajPodtablicNaiwny(r1, c1, 10, t1);

    // Test 2: Ci¹g wartoœci sta³ych
    printf("Test 2 (Wartosci stale): ");
        printf("Koniec testow.\n\n");
    free(t1[0]); free(t1);
}



int main() {
    srand(time(NULL));
    TestyNiewygodne();

    // Dane do Tabeli 2
    int N_pomiary[] = {2500, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int liczba_testow = 10;

    printf("L.p.      n       t1 [s]    t2 [s]\n");
    for (int i = 0; i < liczba_testow; i++) {
        int n = N_pomiary[i];
        int rows = 100, cols = n / 100;

        // Alokacja macierzy
        int **A = (int **)malloc(rows * sizeof(int *));
        for(int r=0; r<rows; r++) A[r] = (int *)malloc(cols * sizeof(int));

        clock_t start, stop;

        // Pomiar t1
        start = clock();
        SzukajPodtablicNaiwny(rows, cols, 1000, A);
        stop = clock();
        double t1 = (double)(stop - start) / CLOCKS_PER_SEC;

        // Pomiar t2
        start = clock();
        SzukajPodtablicUlepszony(rows, cols, 1000, A);
        stop = clock();
        double t2 = (double)(stop - start) / CLOCKS_PER_SEC;

        printf("%2d %10d %6.6f %6.6f\n", i+1, n, t1, t2);

        for(int r=0; r<rows; r++) free(A[r]); free(A);
    }
    return 0;
}
