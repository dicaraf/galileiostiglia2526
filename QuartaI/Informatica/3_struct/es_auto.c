/*Esercizio 2 del file esercizi.md*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Auto {
    char targa[9];
    char marca[50];
    char modello[50];
    float prezzo_giorno;
    //struct Auto* next;
} Auto;

Auto* inserisciAuto(Auto* parco, int* n) {
    parco = (Auto*)realloc(parco, (*n + 1) * sizeof(Auto));
    char c;
    if(parco == NULL) {
        printf("Errore di allocazione");
        exit(1);
    }
    Auto nuova_auto;
    printf(" === Inserimento nuova auto ===\n");
    printf("Inserisci targa: ");
    fgets(nuova_auto.targa, 9, stdin);
    printf("Inserisci marca: ");
    fgets(nuova_auto.marca, 20, stdin);
    printf("Inserisci modello: ");
    fgets(nuova_auto.modello, 20, stdin);
    printf("Inserisci prezzo giornaliero: ");
    scanf("%f", &nuova_auto.prezzo_giorno);
    while((c = getchar()) != '\n') {}
    parco[*n] = nuova_auto;
    (*n)++;
    return parco;
}

void stampaAuto(Auto* parco, int n){
    for(int i = 0; i < n; i++) {
        printf("\n=== AUTO %d ===\n", i+1);
        printf("%s %s %s %f€/giorno\n", parco[i].targa, parco[i].marca, parco[i].modello, parco[i].prezzo_giorno);
    }
}

int main(){
    int num_auto = 10;
    Auto* tante_auto = (Auto*)malloc(num_auto*sizeof(Auto));
    tante_auto = (Auto*)realloc(tante_auto, 11*sizeof(Auto));
    for(int i=0; i<11; i++) {
        tante_auto[i].prezzo_giorno = i;

    }
    //eliminare auto con prezzo = 5
    for(int i = 0; i < 11; i++){
        if(tante_auto[i].prezzo_giorno == 5) {
            for(int j = i + 1; j < 11; j++){
                tante_auto[j-1] = tante_auto[j];
            }
        }
    }
    tante_auto = (Auto*)realloc(tante_auto, 10*sizeof(Auto));
    int n_auto = 0;

    int scelta;
    char c;

    do {
        printf("\n===== AUTONOLEGGIO 2000 =====\n");
        printf("1. Inserisci nuova auto\n");
        printf("2. Visualizza auto\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        while((c = getchar()) != '\n') {}

        switch (scelta) {
            case 1:
                parco = inserisciAuto(parco, &n_auto);\
            case 2:
                stampaAuto(parco, n_auto);
            case 0:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida!\n");
        } 
    } while (scelta != 0);

    return 0;
}