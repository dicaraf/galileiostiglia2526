/*ESERCIZIO 3 Scrivi un programma in C che riempia un vettore con 50 numeri casuali compresi tra 1 e 20. Il programma deve mostrare quanti numeri distinti (unici) sono presenti nel vettore, quali sono questi numeri (stampali una sola volta ciascuno).*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int numeri[50];

    int i, j;

    int trovato;

    int distinti = 0;

    // Inizializza il generatore casuale
    srand(time(NULL));

    // Riempimento array con valori casuali tra 1 e 20
    for(i = 0; i < 50; i++) {

        numeri[i] = rand() % 20 + 1;
    }

    // Stampa del vettore
    printf("Vettore generato:\n");

    for(i = 0; i < 50; i++) {

        printf("%d ", numeri[i]);
    }

    printf("\n\nNumeri distinti presenti:\n");

    // Ricerca dei numeri unici
    for(i = 0; i < 50; i++) {

        trovato = 0;

        // Controllo se il numero era gia' comparso
        for(j = 0; j < i; j++) {

            if(numeri[i] == numeri[j]) {

                trovato = 1;
            }
        }

        // Se non era mai comparso lo stampo
        if(trovato == 0) {

            printf("%d ", numeri[i]);

            distinti++;
        }
    }

    // Stampa totale numeri distinti
    printf("\n\nQuantita' di numeri distinti: %d\n", distinti);

    return 0;
}