/*ESERCIZIO 3 Scrivi un programma in C che riempia un vettore con 20 numeri casuali compresi tra 1 e 10. Il programma deve stampare il vettore al contrario (dall'ultimo elemento al primo), verificare se il vettore è palindromo (cioè uguale letto da sinistra e da destra)*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 20
int main() {

    // Array da 20 elementi
    int numeri[DIM];

    int i;

    // Variabile usata per verificare
    // se il vettore è palindromo
    //
    // All'inizio assumiamo che lo sia.
    int palindromo = 1;

    // ==========================================
    // INIZIALIZZAZIONE GENERATORE CASUALE
    // ==========================================

    srand(time(NULL));

    // ==========================================
    // RIEMPIMENTO ARRAY
    // ==========================================
    //
    // Numeri casuali da 1 a 10
    //

    for(i = 0; i < DIM; i++) {

        numeri[i] = rand() % 10 + 1;
    }

    // ==========================================
    // STAMPA NORMALE DEL VETTORE
    // ==========================================

    printf("Vettore originale:\n");

    for(i = 0; i < DIM; i++) {

        printf("%d ", numeri[i]);
    }

    // ==========================================
    // STAMPA AL CONTRARIO
    // ==========================================
    //
    // Partiamo dall'ultimo elemento:
    //
    // indice 19
    //
    // e arriviamo fino a 0.
    //

    printf("\n\nVettore al contrario:\n");

    for(i = DIM-1; i >= 0; i--) {

        printf("%d ", numeri[i]);
    }

    // ==========================================
    // CONTROLLO PALINDROMO
    // ==========================================
    //
    // Un vettore è palindromo se:
    //
    // primo elemento = ultimo
    // secondo elemento = penultimo
    // ...
    //
    // Esempio:
    //
    // 1 2 3 2 1
    //
    // è palindromo.
    //
    // Confrontiamo quindi:
    //
    // numeri[0] con numeri[19]
    // numeri[1] con numeri[18]
    // ...
    //
    // Basta controllare metà array.
    //

    for(i = 0; i < DIM / 2; i++) {

        // Se troviamo anche una sola coppia diversa
        // il vettore NON è palindromo.
        if(numeri[i] != numeri[19 - i]) {

            palindromo = 0;
        }
    }

    // ==========================================
    // RISULTATO FINALE
    // ==========================================

    if(palindromo == 1) {

        printf("\n\nIl vettore e' palindromo.\n");

    } else {

        printf("\n\nIl vettore NON e' palindromo.\n");
    }

    return 0;
}