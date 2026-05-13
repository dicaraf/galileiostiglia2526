/*Scrivi un programma in C che riempia un vettore di 5 
elementi con numeri casuali tra 1 e 1000. 
Il programma deve mostrare un messaggio che dica se l’array 
è crescente (ogni elemento è più piccolo del successivo), 
decrescente (ogni elemento è più grande del successivo)  
o non ordinato (nessuno dei due casi precedenti).*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 5

int main() {
    int array[DIM], conta_crescente=0, conta_decrescente=0;
    srand (time(NULL));
    for (int i=0; i<DIM; i++) {
        array[i]=rand () %1000+1;
    } 
    for (int i=0; i<DIM-1; i++) {
        if (array[i]<array[i+1]) {
            conta_crescente++;
        }
        if (array[i]>array[i+1]) {
            conta_decrescente++;
        } 
    }
    if (conta_crescente==4) {
        printf ("l'array è crescente\n");
    } else if (conta_decrescente==4) {
        printf ("l'array è decrescente\n");
    } else 
        printf ("l'array è sparso\n");
    return 0;
}