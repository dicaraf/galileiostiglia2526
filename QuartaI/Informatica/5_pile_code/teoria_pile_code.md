# Pile e Code in C: Guida Completa

## Introduzione a Pile e Code

Le **pile** (stack) e le **code** (queue) sono due strutture dati fondamentali in informatica che implementano principi di accesso diversi agli elementi memorizzati. Una **pila** segue il principio **LIFO** (Last In First Out), dove l'ultimo elemento inserito è il primo ad essere estratto. Una **coda** segue il principio **FIFO** (First In First Out), dove il primo elemento inserito è il primo ad essere estratto. Entrambe le strutture possono essere implementate utilizzando array o liste collegate, ognuna con vantaggi e svantaggi specifici.

## Pile (Stack)

### Definizione della Struttura Pila

Una pila richiede almeno un puntatore al primo elemento (top) e una variabile per tracciare la dimensione corrente:

```c
typedef struct Nodo {
    int dato;
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* top;
    int lunghezza;
} Pila;
```

In alternativa, è possibile implementare una pila utilizzando un array:

```c
typedef struct {
    int* elementi;
    int top;
    int capacita;
} PilaArray;
```

### Implementazione con Lista Collegata

**Creazione della pila:**

```c
Pila* creaPila() {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->top = NULL;
    pila->lunghezza = 0;
    return pila;
}
```

**Push (inserimento in cima):**

L'operazione di push aggiunge un elemento in cima alla pila. Poiché ogni nuovo elemento diventa la nuova testa, l'inserimento è estremamente efficiente con complessità O(1):

```c
void push(Pila* pila, int valore) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    
    if (nuovoNodo == NULL) {
        printf("Errore: memoria insufficiente\n");
        return;
    }
    
    nuovoNodo->dato = valore;
    nuovoNodo->next = pila->top;
    pila->top = nuovoNodo;
    pila->lunghezza++;
}
```

**Pop (estrazione dalla cima):**

L'operazione di pop rimuove e restituisce l'elemento in cima alla pila:

```c
int pop(Pila* pila) {
    if (pila->top == NULL) {
        printf("Errore: pila vuota, impossibile effettuare pop\n");
        return -1;  // Valore di errore
    }
    
    int valore = pila->top->dato;
    Nodo* temp = pila->top;
    pila->top = pila->top->next;
    free(temp);
    pila->lunghezza--;
    
    return valore;
}
```

**Peek (visualizzazione dell'elemento in cima):**

L'operazione di peek restituisce l'elemento in cima senza rimuoverlo:

```c
int peek(Pila* pila) {
    if (pila->top == NULL) {
        printf("Errore: pila vuota\n");
        return -1;
    }
    
    return pila->top->dato;
}
```

**Verifica se la pila è vuota:**

```c
int pilaVuota(Pila* pila) {
    return pila->top == NULL;
}
```

**Stampa della pila:**

```c
void stampaPila(Pila* pila) {
    if (pila->top == NULL) {
        printf("Pila vuota\n");
        return;
    }
    
    printf("Pila (dall'alto): ");
    Nodo* current = pila->top;
    
    while (current != NULL) {
        printf("[%d] ", current->dato);
        current = current->next;
    }
    printf("\nLunghezza: %d\n", pila->lunghezza);
}
```

**Liberazione della memoria:**

```c
void liberaPila(Pila* pila) {
    while (pila->top != NULL) {
        Nodo* temp = pila->top;
        pila->top = pila->top->next;
        free(temp);
    }
    free(pila);
}
```

### Implementazione con Array

L'implementazione con array è più semplice ma richiede una dimensione massima predefinita:

**Creazione della pila:**

```c
PilaArray* creaPilaArray(int capacita) {
    PilaArray* pila = (PilaArray*)malloc(sizeof(PilaArray));
    pila->elementi = (int*)malloc(capacita * sizeof(int));
    pila->top = -1;  // Indice della pila vuota
    pila->capacita = capacita;
    return pila;
}
```

**Push con array:**

```c
void pushArray(PilaArray* pila, int valore) {
    if (pila->top >= pila->capacita - 1) {
        printf("Errore: pila piena\n");
        return;
    }
    
    pila->top++;
    pila->elementi[pila->top] = valore;
}
```

**Pop con array:**

```c
int popArray(PilaArray* pila) {
    if (pila->top < 0) {
        printf("Errore: pila vuota\n");
        return -1;
    }
    
    return pila->elementi[pila->top--];
}
```

### Esempio di Utilizzo: Verifica Parentesi Bilanciate

Una classica applicazione delle pile è la verifica delle parentesi bilanciate:

```c
int parentesiBalanciate(char* espressione) {
    Pila* pila = creaPila();
    
    for (int i = 0; espressione[i] != '\0'; i++) {
        char c = espressione[i];
        
        // Parentesi di apertura
        if (c == '(' || c == '{' || c == '[') {
            push(pila, c);
        }
        // Parentesi di chiusura
        else if (c == ')' || c == '}' || c == ']') {
            if (pilaVuota(pila)) {
                liberaPila(pila);
                return 0;  // Non bilanciato
            }
            
            int top = pop(pila);
            
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                liberaPila(pila);
                return 0;  // Non bilanciato
            }
        }
    }
    
    int risultato = pilaVuota(pila);
    liberaPila(pila);
    return risultato;
}
```

## Code (Queue)

### Definizione della Struttura Coda

Una coda richiede due puntatori: uno alla testa (head, primo elemento) e uno alla coda (tail, ultimo elemento):

```c
typedef struct NodoCoda {
    int dato;
    struct NodoCoda* next;
} NodoCoda;

typedef struct {
    NodoCoda* head;
    NodoCoda* tail;
    int lunghezza;
} Coda;
```

Alternativamente, con array (buffer circolare):

```c
typedef struct {
    int* elementi;
    int head;
    int tail;
    int lunghezza;
    int capacita;
} CodaArray;
```

### Implementazione con Lista Collegata

**Creazione della coda:**

```c
Coda* creaCoda() {
    Coda* coda = (Coda*)malloc(sizeof(Coda));
    coda->head = NULL;
    coda->tail = NULL;
    coda->lunghezza = 0;
    return coda;
}
```

**Enqueue (inserimento in coda):**

L'operazione di enqueue aggiunge un elemento alla fine della coda:

```c
void enqueue(Coda* coda, int valore) {
    NodoCoda* nuovoNodo = (NodoCoda*)malloc(sizeof(NodoCoda));
    
    if (nuovoNodo == NULL) {
        printf("Errore: memoria insufficiente\n");
        return;
    }
    
    nuovoNodo->dato = valore;
    nuovoNodo->next = NULL;
    
    if (coda->tail == NULL) {
        // Coda vuota
        coda->head = nuovoNodo;
        coda->tail = nuovoNodo;
    } else {
        // Aggiungi alla fine
        coda->tail->next = nuovoNodo;
        coda->tail = nuovoNodo;
    }
    
    coda->lunghezza++;
}
```

**Dequeue (estrazione dalla testa):**

L'operazione di dequeue rimuove e restituisce l'elemento dalla testa della coda:

```c
int dequeue(Coda* coda) {
    if (coda->head == NULL) {
        printf("Errore: coda vuota, impossibile effettuare dequeue\n");
        return -1;
    }
    
    int valore = coda->head->dato;
    NodoCoda* temp = coda->head;
    coda->head = coda->head->next;
    free(temp);
    coda->lunghezza--;
    
    // Se la coda diventa vuota, aggiorna anche la coda
    if (coda->head == NULL) {
        coda->tail = NULL;
    }
    
    return valore;
}
```

**Front (visualizzazione dell'elemento in testa):**

```c
int front(Coda* coda) {
    if (coda->head == NULL) {
        printf("Errore: coda vuota\n");
        return -1;
    }
    
    return coda->head->dato;
}
```

**Rear (visualizzazione dell'elemento in coda):**

```c
int rear(Coda* coda) {
    if (coda->tail == NULL) {
        printf("Errore: coda vuota\n");
        return -1;
    }
    
    return coda->tail->dato;
}
```

**Verifica se la coda è vuota:**

```c
int codaVuota(Coda* coda) {
    return coda->head == NULL;
}
```

**Stampa della coda:**

```c
void stampaCoda(Coda* coda) {
    if (coda->head == NULL) {
        printf("Coda vuota\n");
        return;
    }
    
    printf("Coda (da testa a coda): ");
    NodoCoda* current = coda->head;
    
    while (current != NULL) {
        printf("[%d] -> ", current->dato);
        current = current->next;
    }
    printf("NULL\n");
    printf("Lunghezza: %d\n", coda->lunghezza);
}
```

**Liberazione della memoria:**

```c
void liberaCoda(Coda* coda) {
    while (coda->head != NULL) {
        NodoCoda* temp = coda->head;
        coda->head = coda->head->next;
        free(temp);
    }
    free(coda);
}
```

### Implementazione con Array Circolare

L'implementazione con array circolare è efficiente quando si conosce la dimensione massima:

**Creazione della coda circolare:**

```c
CodaArray* creaCodaArray(int capacita) {
    CodaArray* coda = (CodaArray*)malloc(sizeof(CodaArray));
    coda->elementi = (int*)malloc(capacita * sizeof(int));
    coda->head = 0;
    coda->tail = -1;
    coda->lunghezza = 0;
    coda->capacita = capacita;
    return coda;
}
```

**Enqueue con array circolare:**

```c
void enqueueArray(CodaArray* coda, int valore) {
    if (coda->lunghezza >= coda->capacita) {
        printf("Errore: coda piena\n");
        return;
    }
    
    coda->tail = (coda->tail + 1) % coda->capacita;
    coda->elementi[coda->tail] = valore;
    coda->lunghezza++;
}
```

**Dequeue con array circolare:**

```c
int dequeueArray(CodaArray* coda) {
    if (coda->lunghezza <= 0) {
        printf("Errore: coda vuota\n");
        return -1;
    }
    
    int valore = coda->elementi[coda->head];
    coda->head = (coda->head + 1) % coda->capacita;
    coda->lunghezza--;
    
    return valore;
}
```

### Esempio di Utilizzo: Simulazione di una Coda di Stampa

Ecco un esempio pratico di una coda di documenti in attesa di stampa:

```c
typedef struct {
    int idDocumento;
    int priorita;
    char nomeFile[50];
} Documento;

typedef struct NodoStampa {
    Documento doc;
    struct NodoStampa* next;
} NodoStampa;

typedef struct {
    NodoStampa* head;
    NodoStampa* tail;
    int lunghezza;
} CodaStampa;

CodaStampa* creaCodeStampa() {
    CodaStampa* coda = (CodaStampa*)malloc(sizeof(CodaStampa));
    coda->head = NULL;
    coda->tail = NULL;
    coda->lunghezza = 0;
    return coda;
}

void aggiungiDocumento(CodaStampa* coda, int id, int priorita, char* nome) {
    NodoStampa* nuovoNodo = (NodoStampa*)malloc(sizeof(NodoStampa));
    nuovoNodo->doc.idDocumento = id;
    nuovoNodo->doc.priorita = priorita;
    strcpy(nuovoNodo->doc.nomeFile, nome);
    nuovoNodo->next = NULL;
    
    if (coda->tail == NULL) {
        coda->head = nuovoNodo;
        coda->tail = nuovoNodo;
    } else {
        coda->tail->next = nuovoNodo;
        coda->tail = nuovoNodo;
    }
    coda->lunghezza++;
}

Documento stampaDocumento(CodaStampa* coda) {
    if (coda->head == NULL) {
        printf("Errore: nessun documento in coda\n");
        Documento vuoto = {-1, 0, ""};
        return vuoto;
    }
    
    Documento doc = coda->head->doc;
    NodoStampa* temp = coda->head;
    coda->head = coda->head->next;
    free(temp);
    coda->lunghezza--;
    
    if (coda->head == NULL) {
        coda->tail = NULL;
    }
    
    printf("Stampa in corso: %s (ID: %d)\n", doc.nomeFile, doc.idDocumento);
    return doc;
}
```

## Confronto tra Pile e Code

| Aspetto | Pila (Stack) | Coda (Queue) |
|---------|--------------|-------------|
| **Principio** | LIFO (Last In First Out) | FIFO (First In First Out) |
| **Inserimento** | Dalla cima (top) | Dalla coda (tail) |
| **Estrazione** | Dalla cima (top) | Dalla testa (head) |
| **Complessità Push/Pop** | O(1) | O(1) |
| **Complessità Enqueue/Dequeue** | O(1) | O(1) |
| **Casi d'uso** | Undo/Redo, Navigazione, Valutazione espressioni | Scheduling, Simulazioni, Buffer |
| **Memoria per nodo** | 1 puntatore (lista) | 1 puntatore (lista) |

## Confronto tra Implementazioni

| Aspetto | Lista Collegata | Array |
|---------|-----------------|-------|
| **Flessibilità** | Cresce dinamicamente | Dimensione fissa predefinita |
| **Memoria** | Allocazione dinamica | Allocazione statica/dinamica |
| **Accesso diretto** | No | Sì (solo per array a indice) |
| **Cache locality** | Scarsa | Buona |
| **Overhead di memoria** | 1 puntatore per nodo | Potenziale spreco se sottoutilizzata |
| **Facilità di implementazione** | Moderata | Semplice |

## Esempio Pratico Completo: Calcolatore Postfisso

Un'applicazione reale che combina le operazioni su pile è un calcolatore che valuta espressioni in notazione postfissa.
La **valutazione di un’espressione postfissa** è il processo con cui si **calcola il risultato** di un’espressione matematica scritta in **notazione postfissa** (detta anche **notazione polacca inversa – RPN**).

---
In un’espressione **postfissa** gli **operatori vengono dopo gli operandi**.

**Esempio**
- Infix (notazione normale): `(3 + 4) * 5`
- Postfissa: `3 4 + 5 *`

In questo tipo di notazione **non servono parentesi**, perché l’ordine delle operazioni è già determinato dalla posizione degli operatori.

---
“Valutare” un’espressione significa **eseguire i calcoli passo dopo passo** fino a ottenere il risultato finale.

La valutazione delle espressioni postfisse si realizza tipicamente usando una **pila (stack)**.

---

## Algoritmo di valutazione
1. Si legge l’espressione **da sinistra verso destra**
2. Se l’elemento è un **operando (numero)** → si inserisce nello stack
3. Se l’elemento è un **operatore**:
   - si estraggono (**pop**) gli ultimi **due** operandi dallo stack
   - si applica l’operatore
   - si inserisce (**push**) il risultato nello stack
4. Al termine dell’espressione, nello stack rimane **un solo valore**, che è il **risultato finale**

---

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Nodo {
    double dato;
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* top;
} PilaCalc;

PilaCalc* creaPila() {
    PilaCalc* pila = (PilaCalc*)malloc(sizeof(PilaCalc));
    pila->top = NULL;
    return pila;
}

void push(PilaCalc* pila, double valore) {
    Nodo* nuovoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuovoNodo->dato = valore;
    nuovoNodo->next = pila->top;
    pila->top = nuovoNodo;
}

double pop(PilaCalc* pila) {
    if (pila->top == NULL) {
        return 0;
    }
    
    double valore = pila->top->dato;
    Nodo* temp = pila->top;
    pila->top = pila->top->next;
    free(temp);
    
    return valore;
}

double valutaPostfissa(char* espressione) {
    PilaCalc* pila = creaPila();
    int i = 0;
    
    while (espressione[i] != '\0') {
        if (isdigit(espressione[i])) {
            // Leggi il numero
            double numero = 0;
            while (isdigit(espressione[i])) {
                numero = numero * 10 + (espressione[i] - '0');
                i++;
            }
            push(pila, numero);
            i--;
        } else if (espressione[i] == '+' || espressione[i] == '-' || 
                   espressione[i] == '*' || espressione[i] == '/') {
            double b = pop(pila);
            double a = pop(pila);
            double risultato;
            
            switch (espressione[i]) {
                case '+': risultato = a + b; break;
                case '-': risultato = a - b; break;
                case '*': risultato = a * b; break;
                case '/': risultato = a / b; break;
            }
            
            push(pila, risultato);
        }
        i++;
    }
    
    double risultatoFinale = pop(pila);
    free(pila);
    
    return risultatoFinale;
}

int main() {
    char espressione[] = "15 7 1 1 + - / 3 * 2 1 1 + + -";
    printf("Espressione postfissa: %s\n", espressione);
    printf("Risultato: %f\n", valutaPostfissa(espressione));
    
    return 0;
}
```
