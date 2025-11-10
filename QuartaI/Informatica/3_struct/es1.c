/*## Esercizio 1.
Si crei la struttura libro, in cui ogni libro ha un codice numerico (numero intero) 
che lo caratterizza, un numero di pagine e un costo.
Si memorizzino i dati di tre libri e si calcoli il costo medio per pagina dei libri 
e si stampino i dati dei tre libri in ordine crescente di costo per pagina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../2_stringhe/libstring.c"

typedef struct{
    int pagine;
    int id;
    float costo;
    char titolo[30];
}libro;

void inserisci_libro(libro *l){
    printf("Dimmi il titolo del libro.");
    //fgets(libri[i].titolo,30,stdin);
    fgets(l -> titolo,30,stdin);
    printf("Dimmi il costo del libro.");
    scanf("%f", &(l -> costo));
    clear_buffer();
    printf("Dimmi il codice del libro.");
    scanf("%d", &(l -> id));
    clear_buffer();
    printf("Dimmi il numero di pagine del libro.");
    scanf("%d", &(l -> pagine));
    clear_buffer();

}

void stampa_libro(libro l){
    printf("Titolo: %s\nCodice: %d\nNumero Pagine: %d\nCosto%.2f euro\n", l.titolo, l.id, l.pagine, l.costo);
}

int main(){
    libro *libri;
    libri = (libro*)malloc(3*sizeof(libro));
    for (int i = 0; i < 3; i++)
    {
        printf("=== Inserimento dati libro %d ===\n",i+1);
        inserisci_libro(&libri[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        printf("\n=== Stampa libro %d ===\n",i+1);
        stampa_libro(libri[i]);
    }
    
    

}