
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char nome[30];
    char cognome[30];
    float media;
    struct Studente *next;
} Studente;

typedef struct {
    Studente* testa;
    int lunghezza;
} Lista;

void ricerca(Lista* lista, Studente s) {
    Studente* current = lista->testa;
    int posizione = 0;
    
    while (current != NULL) {
        if (strcmp(current->nome, s.nome)==0 && strcmp(current->cognome, s.cognome)==0) {
            printf("La media è %f", current->media);
        }
        current = current->next;
        posizione++;
    }
    
}