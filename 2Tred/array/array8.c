/*Scrivi un programma in C che permetta all'utente di 
riempire un'array di 7 elementi. 
Dire se l'array è palindromo.*/

#include <stdio.h>
#define DIM 100

int main() {
    int numeri[DIM], palindromo = 0;

    for(int i = 0; i < DIM; i++) {
        printf("Riempi array in posizione %d", i);
        scanf("%d", &numeri[i]);
    }

    for(int i = 0; i < DIM/2; i++) {
        if(numeri[i] == numeri[DIM - 1 - i]) {
            palindromo++;
        }
    }
    if(palindromo == DIM / 2) {
        printf("L'array è palindromoooooooooo");
    } else {
        printf("NO.");
    }
    return 0;
}