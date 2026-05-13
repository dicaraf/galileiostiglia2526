/*ESERCIZIO 1 Scrivi un programma in C che chieda all'utente di inserire 8 numeri interi salvandoli in un array. Il programma deve stampare la media dei valori inseriti, quanti numeri sono maggiori della media e quanti numeri sono negativi.*/
#include <stdio.h>
#define DIM 8
int main() {

    // Dichiarazione dell'array di 8 elementi
    int numeri[DIM];

    int i;
    int somma = 0;
    int negativi = 0;
    int maggioriMedia = 0;

    float media;

    // INPUT DEI NUMERI
    printf("Inserisci 8 numeri interi:\n");

    for(i = 0; i < DIM; i++) {

        printf("Numero %d: ", i + 1);
        scanf("%d", &numeri[i]);

        // Aggiungo il numero alla somma
        somma = somma + numeri[i];

        // Controllo se il numero è negativo
        if(numeri[i] < 0) {
            negativi++;
        }
    }

    // Calcolo della media
    media = (float)somma / DIM;

    // Conto quanti numeri sono maggiori della media
    for(i = 0; i < DIM; i++) {

        if(numeri[i] > media) {
            maggioriMedia++;
        }
    }

    // OUTPUT
    printf("\nMedia = %.2f\n", media);

    printf("Numeri maggiori della media: %d\n", maggioriMedia);

    printf("Numeri negativi: %d\n", negativi);

    return 0;
}