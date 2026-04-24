/*Dato un array di 50 elementi riempito con numeri 
casuali tra 1 e 10, contare e mostrare quanti sono i 
valori maggiori di 8.
*/
/*Dato un array di 50 elementi riempito con numeri casuali tra 1 e 10, 
contare e mostrare quanti sono i valori maggiori di 8.
*/

#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    int array[50] , conta = 0;
    srand(time(NULL));
    for(int i=0 ; i<50 ; i++){
        
        array[i] = rand()% (10 - 1 + 1) + 1;
        
    }
    for(int i = 0 ; i<50 ; i++){
        
        if(array[i]>8){
            
            conta++;
        }
        
    }
    printf("sono atati trovati %d elementi > 8" , conta);
    return 0;
}