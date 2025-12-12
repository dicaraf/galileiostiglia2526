/*Esercizio 2 del file esercizi.md*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Auto {
    char targa[9];
    char marca[20];
    char modello[20];
    float prezzo_giorno;
    struct Auto* next;
} Auto;

typedef struct Lista{
    Auto* testa;
    int lunghezza;
}Lista;
void set_auto(Auto* nuova_auto){
    printf(" === Inserimento nuova auto ===\n");
    printf("Inserisci targa: ");
    fgets(nuova_auto->targa, 9, stdin);
    printf("Inserisci marca: ");
    fgets(nuova_auto->marca, 20, stdin);
    printf("Inserisci modello: ");
    fgets(nuova_auto->modello, 20, stdin);
    printf("Inserisci prezzo giornaliero: ");
    scanf("%f", &nuova_auto->prezzo_giorno);
    char c;
    while((c = getchar()) != '\n') {}

}
void inserisciAuto(Lista* lista) {
    Auto* nuova=(Auto*)malloc(sizeof(Auto));
    if(nuova == NULL) {
        printf("Errore di allocazione");
        exit(1);
    }
    nuova->next=NULL;

    set_auto(nuova);
    if(lista->testa==NULL){
        lista->testa=nuova;
        lista->lunghezza++;

    }else {
        Auto* temp=lista->testa;
        while(temp->next!=NULL){
            temp=temp->next;

        }
        temp->next=nuova;
        lista->lunghezza++;
    }
}

void stampaAuto(Lista* parco_auto){
    Auto* temp=parco_auto->testa;
    int i=0;
    while(temp!=NULL){
        printf("\n=== AUTO %d ===\n", i+1);
        printf("%s %s %s %f€/giorno\n", temp->targa, temp->marca, temp->modello, temp->prezzo_giorno);
        i++;
        temp=temp->next;
    }
}
Lista* crea_lista(){
    Lista *parco_auto=(Lista*)malloc(sizeof(Lista));
    parco_auto->lunghezza=0;
    parco_auto->testa=NULL;
    return parco_auto;
    
}

int main(){
    Lista *parco_auto=crea_lista();
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
                inserisciAuto(parco_auto);
                break;
            case 2:
                stampaAuto(parco_auto);
                break;
            case 0:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida!\n");
        } 
    } while (scelta != 0);

    return 0;
}