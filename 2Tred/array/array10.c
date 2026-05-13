/*Riempi un array di 100 elementi con numeri casuali
tra 0 e 1000. Quindi mostra il valore minimo e massimo contenuti
nell'array.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 100

int main(){
    int array[DIM], massimo, minimo, pari = 0;
    srand(time(NULL));
    for(int i = 0; i < DIM; i++){
        array[i] = rand()%1001; //%(1000 - 0 + 1) + 0;
    }
    massimo = array[0];
    minimo = array[0];
    for(int i = 1; i < DIM; i++) {
        if(array[i] > massimo) {
            massimo = array[i];
        }
        if(array[i] < minimo) {
            minimo = array[i];
        }
        if(array[i] % 2 == 0) pari++;
    }
    printf("Il minimo è %d, il massimo è %d\n", minimo, massimo);
    printf("I numeri pari trovati sono %d\n", pari);
    return 0;
}