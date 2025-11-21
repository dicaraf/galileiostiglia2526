#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char targa[8];
    char marca[20];
    char modello[20];
    float prezzo;

}Auto;

void inserisci_auto(Auto* parco, int*n){
    Auto nuova_auto;
    printf("inserisci la targa dell'auto: ");
    fgets(nuova_auto.targa,8,stdin);
    printf("inserisci il modello dell'auto: ");
    fgets(nuova_auto.modello,20,stdin);
    printf("inserisci la marca dell' auto: ");
    fgets(nuova_auto.marca,20,stdin);
    printf("inserisci il prezzo dell' auto: ");
    scanf("%f", &nuova_auto.prezzo);
    getchar();
    parco = (Auto*)realloc(parco, ((*n)+1)*sizeof(Auto));
    if(parco == NULL){
        printf("errore di allocazione.");
        exit(1);
    }
    parco[*n] = nuova_auto;
    (*n)++;
}

void stampa_auto(Auto*parco, int n){
    printf("---elenco auto---\n");
    for(int i=0;i<n;i++){
        printf("targa %s", parco[i].targa);
        printf("marca %s", parco[i].marca);
        printf("modello %s", parco[i].modello);
        printf("prezzo %f", parco[i].prezzo);
    }
}

int main(){
    Auto*parco = NULL;
    int numero_auto = 0;
    int scelta;

    printf("1. aggiungi auto: \n 2. stampa auto: \n 3. ")
}