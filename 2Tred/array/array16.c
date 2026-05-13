/*ESERCIZIO 1 Scrivi un programma in C che chieda all'utente di inserire 12 numeri interi salvandoli in un array. Il programma deve stampare la somma dei numeri in posizione pari (indice 0, 2, 4…), la somma dei numeri in posizione dispari (indice 1, 3, 5…), quale delle due somme è più grande.*/

#include <stdio.h>
#define DIM 12
int main() {

    // Dichiarazione dell'array da 12 elementi
    int numeri[DIM];

    // Variabile contatore per i cicli
    int i;

    // Variabili che conterranno:
    // - la somma degli elementi in posizione pari
    // - la somma degli elementi in posizione dispari
    int sommaPari = 0;
    int sommaDispari = 0;

    // =========================
    // FASE 1: INPUT DEI NUMERI
    // =========================
    //
    // Chiediamo all'utente di inserire 12 numeri.
    // Ogni numero viene salvato nell'array.
    //
    // L'indice parte da 0:
    //
    // indice:   0 1 2 3 4 5 ...
    //
    // Gli indici PARI sono:
    // 0, 2, 4, 6 ...
    //
    // Gli indici DISPARI sono:
    // 1, 3, 5, 7 ...
    //

    printf("Inserisci 12 numeri interi:\n");

    for(i = 0; i < DIM; i++) {

        printf("Numero %d: ", i + 1);
        scanf("%d", &numeri[i]);

        // ====================================
        // CONTROLLO SE L'INDICE E' PARI O DISPARI
        // ====================================
        //
        // Usiamo l'operatore %
        //
        // i % 2 == 0  --> indice pari
        // i % 2 != 0  --> indice dispari
        //
        // Esempi:
        //
        // 4 % 2 = 0  --> pari
        // 5 % 2 = 1  --> dispari
        //

        if(i % 2 == 0) {

            // Se l'indice è pari
            // aggiungiamo il numero alla sommaPari
            sommaPari = sommaPari + numeri[i];

        } else {

            // Altrimenti l'indice è dispari
            // aggiungiamo il numero alla sommaDispari
            sommaDispari = sommaDispari + numeri[i];
        }
    }

    // =========================
    // FASE 2: STAMPA RISULTATI
    // =========================

    printf("\nSomma posizioni pari: %d\n", sommaPari);

    printf("Somma posizioni dispari: %d\n", sommaDispari);

    // ===================================
    // CONFRONTO TRA LE DUE SOMME
    // ===================================
    //
    // Controlliamo quale delle due
    // somme è maggiore.
    //

    if(sommaPari > sommaDispari) {

        printf("La somma delle posizioni pari e' maggiore.\n");

    } else if(sommaDispari > sommaPari) {

        printf("La somma delle posizioni dispari e' maggiore.\n");

    } else {

        // Caso particolare:
        // le due somme sono uguali
        printf("Le due somme sono uguali.\n");
    }

    return 0;
}