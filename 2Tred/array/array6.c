/*Dato un array di 5000 elementi riempito con numeri 
casuali tra 1 e 10, contare e mostrare quante volte
 compare ogni valore tra 1 e 10.
.*/

#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    int array[5000] , conta[10] = {0};
    srand(time(NULL));
    for(int i=0 ; i<5000 ; i++){
        array[i] = rand()% (10 - 1 + 1) + 1;
    }
    for(int i = 0; i< 5000; i++){
        conta[array[i]-1]++;
    }
    for(int i = 0; i < 10; i++) {
        printf("%d è comparso %d volte\n", i+1, conta[i]);
    }
    return 0;
}