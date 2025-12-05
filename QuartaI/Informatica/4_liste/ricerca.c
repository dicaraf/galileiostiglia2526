#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    float voto;
    char nome[20];
    char materia[20];
    struct Nodo *next;
}Nodo;

typedef struct {
    Nodo* testa;
    int lunghezza;
} Lista;

Nodo* ricerca(Lista* lista, Nodo valore) {
    Nodo* current = lista->testa;
    int posizione = 0;
    
    while (current != NULL) {
        if (current->voto == valore.voto && strcmp(current->nome, valore.nome) && strcmp(current->materia, valore.materia)) {
            return posizione;
        }
        current = current->next;
        posizione++;
    }
    return current;
}

int main() {
    Nodo cerca;
    Lista *l = (Lista*)malloc(sizeof(Lista));
    l->testa = NULL;
    l->lunghezza = 0;
    //abbiamo riempito la lista 
    printf("Inserisci voto che vuoi cercare: ");
    scanf("%f", &cerca.voto);
    printf("Inserisci il nome che vuoi cercare: ");
    fgets(cerca.nome, 20, stdin);
    printf("Inserisci il nome che vuoi cercare: ");
    fgets(cerca.materia, 20, stdin);
    int posizione = ricerca(l, cerca);


}