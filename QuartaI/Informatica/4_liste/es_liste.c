#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    int dato;
    struct Nodo *next;
}Nodo;

typedef struct {
    Nodo* testa;
    int lunghezza;
} Lista;

Lista* crea_lista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->testa = NULL;
    lista->lunghezza = 0;
    return lista;
}

void set_nodo(Nodo *n){
    printf("Inserisci il valore per il nuovo nodo: ");
    scanf("%d",&n->dato);
}

void inserisci_in_testa(Lista* lista) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    set_nodo(nuovoNodo);
    nuovoNodo->next = lista->testa;
    lista->testa = nuovoNodo;
    lista->lunghezza++;
}

void inserisci_in_fondo(Lista* lista) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    set_nodo(nuovoNodo);
    nuovoNodo->next = NULL;
    
    if (lista->testa == NULL) {
        lista->testa = nuovoNodo;
    } else {
        Nodo* current = lista->testa;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = nuovoNodo;
    }
    lista->lunghezza++;
}

void stampa_lista(Lista* lista) {
    Nodo* current = lista->testa;
    
    printf("Lista: ");
    while (current != NULL) {
        printf("%d -> ", current->dato);
        current = current->next;
    }
    printf("FINE LISTA\n");
    printf("Lunghezza: %d\n", lista->lunghezza);
}

void libera_lista(Lista* lista) {
    Nodo* current = lista->testa;
    
    while (current != NULL) {
        Nodo* temp = current;
        current = current->next;
        free(temp);
    }
    
    free(lista);
}

int main() {
    Lista *l = crea_lista();

    inserisci_in_testa(l);
    stampa_lista(l);

    inserisci_in_testa(l);
    stampa_lista(l);

    inserisci_in_fondo(l);
    stampa_lista(l);

    libera_lista(l);
    return 0;
}