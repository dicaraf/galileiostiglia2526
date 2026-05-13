/*Scrivi un programma in C che riempia un vettore con 100 numeri
 casuali compresi tra 10 e 50. Il programma deve mostrare: 
 il numero che compare più volte (moda) e quante volte compare.*/

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #define DIM 100

 int main () {
    int array[DIM], max=50, min=10, conta=0, massimo=-1, valore;
    srand (time(NULL));
    for (int i=0; i<DIM; i++) {
        array[i]=rand() %(max-min+1)+min;
    } 
    for (int i=0; i<DIM; i++) {
        conta=0;
        for (int j=0; j<DIM; j++) {
            if (array[i]==array[j]) {
                conta++;
            }
        } 
        if (conta>massimo) {
            massimo=conta;
            valore=array[i];
        }

    }
    printf ("il valore massimo è %d ed è uscito %d volte\n", valore, conta);
    return 0;
 }