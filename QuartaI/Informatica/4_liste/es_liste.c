#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
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

void inserisci_in_testa(Lista* lista, int valore) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuovoNodo->dato = valore;
    nuovoNodo->next = lista->testa;
    lista->testa = nuovoNodo;
    lista->lunghezza++;
}

void inserisci_in_fondo(Lista* lista, int valore) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuovoNodo->dato = valore;
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

    inserisci_in_testa(l, 10);
    stampa_lista(l);

    inserisci_in_testa(l, 20);
    stampa_lista(l);

    inserisci_in_fondo(l, 30);
    stampa_lista(l);

    libera_lista(l);
    return 0;
}