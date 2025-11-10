/*## Esercizio 1.
Si crei la struttura libro, in cui ogni libro ha un codice numerico (numero intero) 
che lo caratterizza, un numero di pagine e un costo.
Si memorizzino i dati di tre libri e si calcoli il costo medio per pagina dei libri 
e si stampino i dati dei tre libri in ordine crescente di costo per pagina.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int pagine;
    int id;
    float costo;
    char titolo[30];
}libro;

int main(){
    libro *libri;
    libri = (libro*)malloc(3*sizeof(libro));
    for (int i = 0; i < 3; i++)
    {
        printf("Dimmi il titolo del %d libro.",i+1);
        fgets(libri[i].titolo,30,stdin);
        fgets((libri + i) -> titolo,30,stdin);
        printf("Dimmi il costo del %d libro.",i+1);
        scanf("%f",&libri[i].costo);
        printf("Dimmi il codice del %d libro.",i+1);
        scanf("%d",&libri[i].id);
        printf("Dimmi il numero di pagine del %d libro.",i+1);
        scanf("%d",&libri[i].pagine);
    }
    

}