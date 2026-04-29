/*Scrivi un programma in C che permetta all'utente di 
riempire un'array di 7 elementi. 
Dire se l'array è palindromo.*/

#include <stdio.h>

int main() {
    int numeri[7], palindromo = 0;

    for(int i = 0; i < 7; i++) {
        printf("Riempi array in posizione %d", i);
        scanf("%d", &numeri[i]);
    }

    for(int i = 0; i < 7/2; i++) {
        if(numeri[i] == numeri[6 - i]) {
            palindromo++;
        }
    }
    if(palindromo == 3) {
        printf("L'array è palindromoooooooooo");
    }
}