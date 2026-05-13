/*ESERCIZIO 2 Scrivi un programma in C che riempia un vettore di 10 elementi con numeri casuali tra 1 e 50. Il programma deve contare quanti numeri sono multipli di 3, contare quanti numeri sono multipli di 5, contare quanti numeri sono multipli di entrambi (cioè multipli di 15)*/

#include <stdio.h>
#include <stdlib.h> // Necessario per rand() e srand()
#include <time.h>   // Necessario per time()
#define DIM 10
int main() {

    // Array da 10 elementi
    int numeri[10];

    int i;

    // Variabili contatori
    int multipli3 = 0;
    int multipli5 = 0;
    int multipli15 = 0;

    // ==========================================
    // INIZIALIZZAZIONE NUMERI CASUALI
    // ==========================================
    //
    // srand(time(NULL))
    // serve per cambiare i numeri casuali
    // ad ogni esecuzione del programma.
    //

    srand(time(NULL));

    // ==========================================
    // RIEMPIMENTO ARRAY
    // ==========================================
    //
    // rand() % 50 genera numeri da 0 a 49
    // +1 trasforma l'intervallo in 1-50
    //

    for(i = 0; i < DIM; i++) {

        numeri[i] = rand() % 50 + 1;
    }

    // ==========================================
    // STAMPA ARRAY
    // ==========================================

    printf("Vettore generato:\n");

    for(i = 0; i < DIM; i++) {

        printf("%d ", numeri[i]);
    }

    printf("\n");

    // ==========================================
    // ANALISI DEI NUMERI
    // ==========================================
    //
    // Per ogni numero controlliamo:
    //
    // - se è multiplo di 3
    // - se è multiplo di 5
    // - se è multiplo di 15
    //
    // Un numero è multiplo di N
    // se il resto della divisione è 0.
    //
    // Esempi:
    //
    // 12 % 3 = 0 --> multiplo di 3
    // 20 % 5 = 0 --> multiplo di 5
    // 30 % 15 = 0 --> multiplo di 15
    //

    for(i = 0; i < DIM; i++) {

        // Controllo multipli di 3
        if(numeri[i] % 3 == 0) {

            multipli3++;
        }

        // Controllo multipli di 5
        if(numeri[i] % 5 == 0) {

            multipli5++;
        }

        // Controllo multipli di 15
        //
        // Un numero multiplo di 15
        // è automaticamente multiplo sia di 3 sia di 5.
        //
        if(numeri[i] % 15 == 0) {

            multipli15++;
        }
    }

    // ==========================================
    // STAMPA RISULTATI
    // ==========================================

    printf("\nMultipli di 3: %d\n", multipli3);

    printf("Multipli di 5: %d\n", multipli5);

    printf("Multipli di 15: %d\n", multipli15);

    return 0;
}