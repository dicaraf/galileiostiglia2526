/*ESERCIZIO 2 Scrivi un programma in C che riempia un vettore di 6 elementi con numeri casuali tra 1 e 100. Il programma deve stampare l'array originale, trovare il secondo elemento più grande, indicare in quale posizione (indice) si trova.*/

#include <stdio.h>
#include <stdlib.h> // necessario per rand() e srand()
#include <time.h>   // necessario per time()
#define DIM 6
int main() {

    int numeri[DIM];

    int i;

    // Variabili per trovare il massimo e il secondo massimo
    int massimo;
    int secondoMassimo;

    int indiceSecondo;

    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    // Riempimento dell'array con numeri casuali
    for(i = 0; i < DIM; i++) {

        numeri[i] = rand() % 100 + 1;
    }

    // Stampa array originale
    printf("Array generato:\n");

    for(i = 0; i < DIM; i++) {

        printf("numeri[%d] = %d\n", i, numeri[i]);
    }

    // Inizializzo massimo e secondo massimo
    massimo = numeri[0];
    secondoMassimo = numeri[0];

    // Cerco il valore massimo
    for(i = 1; i < DIM; i++) {

        if(numeri[i] > massimo) {
            massimo = numeri[i];
        }
    }

    // Cerco il secondo massimo
    for(i = 0; i < DIM; i++) {

        // Deve essere minore del massimo
        // ma più grande del secondo massimo trovato
        if(numeri[i] < massimo && numeri[i] > secondoMassimo) {

            secondoMassimo = numeri[i];

            indiceSecondo = i;
        }
    }

    // OUTPUT
    printf("\nSecondo numero piu' grande: %d\n", secondoMassimo);

    printf("Indice del secondo numero piu' grande: %d\n", indiceSecondo);

    return 0;
}