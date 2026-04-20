/*Chiedere all'utente e memorizzare in un array di 8 celle, 
8 numeri reali, dopo averli memorizzati calcolarne la somma 
e la media.*/

#include <stdio.h>

int main() {
    float array[8], somma = 0, media = 0;

    for(int i = 0; i<8; i++) {
        printf("Inserisci il valore di array[%d]:", i);
        scanf("%f", &array[i]);
        somma = somma + array[i];
    }
    media = somma / 8;

    printf("La somma è %f e la media è %f", somma, media);

    
}