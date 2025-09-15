/*Scrivi un programma in C che permetta di memorizzare il numero
  di capelli dei clienti di un parrucchiere
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int *capelli;
    int n;

    printf("quanti clienti ci sono oggi?");
    scanf("%d", &n);

    capelli=(int*)malloc(n * sizeof(int));

    if(capelli==NULL){
        printf("troppi clienti!");
        return 1;
    }
    free(capelli);
}