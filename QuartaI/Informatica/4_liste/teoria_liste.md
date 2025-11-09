# Liste in C: Guida Completa

## Introduzione alle Liste

Una **lista** è una struttura dati dinamica che permette di memorizzare una sequenza di elementi collegati tra loro attraverso puntatori. A differenza degli array, le liste non richiedono una quantità di memoria contigua e possono crescere o diminuire dinamicamente durante l'esecuzione del programma. Le liste sono fondamentali in informatica perché offrono flessibilità nell'allocazione della memoria e facilitano operazioni di inserimento e cancellazione.

## Struct e Typedef per le Liste

### Definizione Base di un Nodo

La struttura fondamentale di una lista è il **nodo** (node). Ogni nodo contiene due componenti essenziali:

1. **Dato** (data): l'informazione che vogliamo memorizzare
2. **Puntatore al nodo successivo** (next): collegamento al nodo seguente

Ecco come definire un nodo in C:

```c
struct Nodo {
    int dato;
    struct Nodo* next;
};
```

Tuttavia, è convenzione scrivere codice più leggibile utilizzando `typedef`, che permette di creare un alias per il tipo di dato:

```c
typedef struct {
    int dato;
    struct Nodo* next;
} Nodo;
```

Oppure, la forma più comune e consigliata:

```c
typedef struct Nodo {
    int dato;
    struct Nodo* next;
} Nodo;
```

### Definizione della Struttura Lista

Per rappresentare l'intera lista, definiamo una struttura che contiene almeno un puntatore al primo nodo (testa della lista):

```c
typedef struct {
    Nodo* testa;
    int lunghezza;
} Lista;
```

Questa struttura mantiene traccia del primo elemento della lista e, opzionalmente, della sua lunghezza per efficienze nelle operazioni.

## Liste Semplicemente Collegate

### Inizializzazione della Lista

Prima di utilizzare una lista, è necessario inizializarla, allocando memoria e impostando i valori iniziali:

```c
Lista* creaLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->testa = NULL;
    lista->lunghezza = 0;
    return lista;
}
```

### Inserimento di Elementi

L'inserimento in una lista può avvenire in tre posizioni diverse: all'inizio, alla fine o in una posizione specifica.

**Inserimento all'inizio:**

```c
void inserisciInizio(Lista* lista, int valore) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuovoNodo->dato = valore;
    nuovoNodo->next = lista->testa;
    lista->testa = nuovoNodo;
    lista->lunghezza++;
}
```

**Inserimento alla fine:**

```c
void inserisciFine(Lista* lista, int valore) {
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
```

**Inserimento in posizione specifica:**

```c
void inserisciPosizione(Lista* lista, int valore, int posizione) {
    if (posizione < 0 || posizione > lista->lunghezza) {
        printf("Posizione non valida\n");
        return;
    }
    
    if (posizione == 0) {
        inserisciInizio(lista, valore);
        return;
    }
    
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuovoNodo->dato = valore;
    
    Nodo* current = lista->testa;
    for (int i = 0; i < posizione - 1; i++) {
        current = current->next;
    }
    
    nuovoNodo->next = current->next;
    current->next = nuovoNodo;
    lista->lunghezza++;
}
```

### Ricerca di Elementi

La ricerca permette di trovare un elemento nella lista:

```c
int ricerca(Lista* lista, int valore) {
    Nodo* current = lista->testa;
    int posizione = 0;
    
    while (current != NULL) {
        if (current->dato == valore) {
            return posizione;
        }
        current = current->next;
        posizione++;
    }
    
    return -1;  // Elemento non trovato
}
```

### Cancellazione di Elementi

**Cancellazione dal principio:**

```c
void cancellaInizio(Lista* lista) {
    if (lista->testa == NULL) {
        printf("Lista vuota\n");
        return;
    }
    
    Nodo* temp = lista->testa;
    lista->testa = lista->testa->next;
    free(temp);
    lista->lunghezza--;
}
```

**Cancellazione dalla fine:**

```c
void cancellaFine(Lista* lista) {
    if (lista->testa == NULL) {
        printf("Lista vuota\n");
        return;
    }
    
    if (lista->testa->next == NULL) {
        free(lista->testa);
        lista->testa = NULL;
    } else {
        Nodo* current = lista->testa;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
    lista->lunghezza--;
}
```

**Cancellazione per valore:**

```c
void cancellaValore(Lista* lista, int valore) {
    if (lista->testa == NULL) return;
    
    // Se l'elemento è in testa
    if (lista->testa->dato == valore) {
        Nodo* temp = lista->testa;
        lista->testa = lista->testa->next;
        free(temp);
        lista->lunghezza--;
        return;
    }
    
    // Ricerca nella lista
    Nodo* current = lista->testa;
    while (current->next != NULL) {
        if (current->next->dato == valore) {
            Nodo* temp = current->next;
            current->next = current->next->next;
            free(temp);
            lista->lunghezza--;
            return;
        }
        current = current->next;
    }
}
```

### Traversal e Stampa

La traversal (attraversamento) della lista permette di visitare tutti i nodi:

```c
void stampaLista(Lista* lista) {
    Nodo* current = lista->testa;
    
    printf("Lista: ");
    while (current != NULL) {
        printf("%d -> ", current->dato);
        current = current->next;
    }
    printf("NULL\n");
    printf("Lunghezza: %d\n", lista->lunghezza);
}
```

### Liberazione della Memoria

È fondamentale liberare la memoria allocata quando la lista non è più necessaria:

```c
void liberaLista(Lista* lista) {
    Nodo* current = lista->testa;
    
    while (current != NULL) {
        Nodo* temp = current;
        current = current->next;
        free(temp);
    }
    
    free(lista);
}
```

## Liste Bidirezionali (Doppiamente Collegate)

### Definizione della Struttura

Una **lista bidirezionale** (o doppiamente collegata) permette di attraversare la lista in entrambe le direzioni. Ogni nodo contiene due puntatori: uno al nodo successivo e uno al nodo precedente:

```c
typedef struct NodoBidirezionale {
    int dato;
    struct NodoBidirezionale* next;
    struct NodoBidirezionale* prev;
} NodoBidirezionale;

typedef struct {
    NodoBidirezionale* testa;
    NodoBidirezionale* coda;
    int lunghezza;
} ListaBidirezionale;
```

### Inizializzazione

```c
ListaBidirezionale* creaListaBidirezionale() {
    ListaBidirezionale* lista = (ListaBidirezionale*)malloc(sizeof(ListaBidirezionale));
    lista->testa = NULL;
    lista->coda = NULL;
    lista->lunghezza = 0;
    return lista;
}
```

### Inserimento in Lista Bidirezionale

**Inserimento alla fine:**

```c
void inserisciFine_Bidirezionale(ListaBidirezionale* lista, int valore) {
    NodoBidirezionale* nuovoNodo = (NodoBidirezionale*)malloc(sizeof(NodoBidirezionale));
    nuovoNodo->dato = valore;
    nuovoNodo->next = NULL;
    nuovoNodo->prev = NULL;
    
    if (lista->testa == NULL) {
        lista->testa = nuovoNodo;
        lista->coda = nuovoNodo;
    } else {
        nuovoNodo->prev = lista->coda;
        lista->coda->next = nuovoNodo;
        lista->coda = nuovoNodo;
    }
    lista->lunghezza++;
}
```

**Inserimento all'inizio:**

```c
void inserisciInizio_Bidirezionale(ListaBidirezionale* lista, int valore) {
    NodoBidirezionale* nuovoNodo = (NodoBidirezionale*)malloc(sizeof(NodoBidirezionale));
    nuovoNodo->dato = valore;
    nuovoNodo->next = NULL;
    nuovoNodo->prev = NULL;
    
    if (lista->testa == NULL) {
        lista->testa = nuovoNodo;
        lista->coda = nuovoNodo;
    } else {
        nuovoNodo->next = lista->testa;
        lista->testa->prev = nuovoNodo;
        lista->testa = nuovoNodo;
    }
    lista->lunghezza++;
}
```

### Traversal Bidirezionale

Una grande vantaggio delle liste bidirezionali è la possibilità di attraversare la lista sia in avanti che all'indietro:

```c
void stampaListaAvanti(ListaBidirezionale* lista) {
    NodoBidirezionale* current = lista->testa;
    
    printf("Lista (avanti): ");
    while (current != NULL) {
        printf("%d <-> ", current->dato);
        current = current->next;
    }
    printf("NULL\n");
}

void stampaListaIndietro(ListaBidirezionale* lista) {
    NodoBidirezionale* current = lista->coda;
    
    printf("Lista (indietro): ");
    while (current != NULL) {
        printf("%d <-> ", current->dato);
        current = current->prev;
    }
    printf("NULL\n");
}
```

### Cancellazione in Lista Bidirezionale

```c
void cancellaValore_Bidirezionale(ListaBidirezionale* lista, int valore) {
    if (lista->testa == NULL) return;
    
    NodoBidirezionale* current = lista->testa;
    
    while (current != NULL) {
        if (current->dato == valore) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                lista->testa = current->next;
            }
            
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                lista->coda = current->prev;
            }
            
            NodoBidirezionale* temp = current;
            current = current->next;
            free(temp);
            lista->lunghezza--;
        } else {
            current = current->next;
        }
    }
}
```

## Liste Circolari

### Definizione della Struttura

Una **lista circolare** è una lista in cui l'ultimo nodo punta al primo nodo anziché a NULL. Questo crea una struttura circolare che rappresenta un ciclo continuo:

```c
typedef struct NodoCircolare {
    int dato;
    struct NodoCircolare* next;
} NodoCircolare;

typedef struct {
    NodoCircolare* testa;
    int lunghezza;
} ListaCircolare;
```

### Inizializzazione

```c
ListaCircolare* creaListaCircolare() {
    ListaCircolare* lista = (ListaCircolare*)malloc(sizeof(ListaCircolare));
    lista->testa = NULL;
    lista->lunghezza = 0;
    return lista;
}
```

### Inserimento in Lista Circolare

**Inserimento alla fine (che richiede aggiornamento della circolarità):**

```c
void inserisciFine_Circolare(ListaCircolare* lista, int valore) {
    NodoCircolare* nuovoNodo = (NodoCircolare*)malloc(sizeof(NodoCircolare));
    nuovoNodo->dato = valore;
    
    if (lista->testa == NULL) {
        lista->testa = nuovoNodo;
        nuovoNodo->next = nuovoNodo;  // Punta a se stesso
    } else {
        NodoCircolare* current = lista->testa;
        while (current->next != lista->testa) {
            current = current->next;
        }
        nuovoNodo->next = lista->testa;
        current->next = nuovoNodo;
    }
    lista->lunghezza++;
}
```

**Inserimento all'inizio:**

```c
void inserisciInizio_Circolare(ListaCircolare* lista, int valore) {
    NodoCircolare* nuovoNodo = (NodoCircolare*)malloc(sizeof(NodoCircolare));
    nuovoNodo->dato = valore;
    
    if (lista->testa == NULL) {
        lista->testa = nuovoNodo;
        nuovoNodo->next = nuovoNodo;
    } else {
        NodoCircolare* current = lista->testa;
        while (current->next != lista->testa) {
            current = current->next;
        }
        nuovoNodo->next = lista->testa;
        current->next = nuovoNodo;
        lista->testa = nuovoNodo;
    }
    lista->lunghezza++;
}
```

### Traversal di Lista Circolare

Con le liste circolari è importante contare i nodi visitati per evitare cicli infiniti:

```c
void stampaLista_Circolare(ListaCircolare* lista) {
    if (lista->testa == NULL) {
        printf("Lista vuota\n");
        return;
    }
    
    NodoCircolare* current = lista->testa;
    printf("Lista circolare: ");
    
    for (int i = 0; i < lista->lunghezza; i++) {
        printf("%d -> ", current->dato);
        current = current->next;
    }
    printf("(ritorno a %d)\n", lista->testa->dato);
}
```

### Cancellazione in Lista Circolare

```c
void cancellaValore_Circolare(ListaCircolare* lista, int valore) {
    if (lista->testa == NULL) return;
    
    // Se l'elemento è in testa
    if (lista->testa->dato == valore) {
        if (lista->lunghezza == 1) {
            free(lista->testa);
            lista->testa = NULL;
        } else {
            NodoCircolare* current = lista->testa;
            while (current->next != lista->testa) {
                current = current->next;
            }
            NodoCircolare* temp = lista->testa;
            lista->testa = lista->testa->next;
            current->next = lista->testa;
            free(temp);
        }
        lista->lunghezza--;
        return;
    }
    
    // Ricerca nella lista
    NodoCircolare* current = lista->testa;
    for (int i = 0; i < lista->lunghezza; i++) {
        if (current->next->dato == valore) {
            NodoCircolare* temp = current->next;
            current->next = current->next->next;
            free(temp);
            lista->lunghezza--;
            return;
        }
        current = current->next;
    }
}
```

## Confronto tra i Tipi di Liste

| Aspetto | Semplice | Bidirezionale | Circolare |
|---------|----------|---------------|-----------|
| **Attraversamento** | Solo in avanti | Avanti e indietro | Solo in avanti (circolare) |
| **Complessità spaziale** | Bassa (1 puntatore) | Media (2 puntatori) | Bassa (1 puntatore) |
| **Accesso al fine** | Richiede traversal | Diretto (coda) | Richiede traversal |
| **Casi d'uso** | Uso generale | Queue doppia, Undo/Redo | Gestione di buffer circolari |
| **Memoria per nodo** | Minima | Doppia | Minima |

## Esempio Pratico Completo

Ecco un esempio di utilizzo di una lista semplicemente collegata:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* testa;
    int lunghezza;
} Lista;

Lista* creaLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->testa = NULL;
    lista->lunghezza = 0;
    return lista;
}

void inserisciFine(Lista* lista, int valore) {
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

void stampaLista(Lista* lista) {
    Nodo* current = lista->testa;
    printf("Lista: ");
    while (current != NULL) {
        printf("%d -> ", current->dato);
        current = current->next;
    }
    printf("NULL\n");
}

void liberaLista(Lista* lista) {
    Nodo* current = lista->testa;
    while (current != NULL) {
        Nodo* temp = current;
        current = current->next;
        free(temp);
    }
    free(lista);
}

int main() {
    Lista* lista = creaLista();
    
    inserisciFine(lista, 10);
    inserisciFine(lista, 20);
    inserisciFine(lista, 30);
    
    stampaLista(lista);
    
    liberaLista(lista);
    return 0;
}
```