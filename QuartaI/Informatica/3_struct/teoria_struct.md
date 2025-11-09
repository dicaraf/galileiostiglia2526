# Record e tabelle

Negli array i dati sono ordinati e omogenei (tutti dello stesso tipo).
Se abbiamo bisogno di memorizzare in una stessa struttura dati elementi eterogenei (ad esempio un intero e una stringa per memorizzare età e nome di una persona), si parla di **record**: una struttura sequenziale composta costituita da elementi di vario tipo detti campi.
Il concetto di record è fondamentale: su di esso si basano tutte le tecniche di organizzazione e memorizzazione dei dati (compresi i database).
Se creiamo un record che all’interno contiene un altro record, si parla di **record di record**.
Se creiamo un array che ha come elementi dei record di parla di **tabella**.

# Struct in C e Memoria Dinamica

## Introduzione

Le **strutture** (struct) in C sono uno strumento fondamentale per organizzare dati correlati in un unico contenitore. Quando lavoriamo con strutture, spesso abbiamo bisogno di gestire la memoria in modo dinamico, allocando spazio in memoria durante l'esecuzione del programma anziché definire la dimensione in modo statico al momento della compilazione. Questo documento esplora come dichiarare struct come puntatori, utilizzare la funzione `malloc()` per allocare memoria dinamicamente e gestire array di struct allocati dinamicamente.

---

## 1. Fondamenti di Struct in C

### 1.1 Dichiarazione di una Struct

Una struttura è un tipo di dato composito che consente di raggruppare variabili di tipi diversi sotto un unico nome. Ecco un esempio basilare:

```c
struct Persona {
    char nome[50];
    int eta;
    float stipendio;
};
```

In questa dichiarazione, la struct `Persona` contiene tre campi: un array di caratteri per il nome, un intero per l'età e un float per lo stipendio.

### 1.2 Dichiarazione di Variabili Struct (Metodo Statico)

Nel metodo tradizionale, si crea una variabile struct direttamente sullo stack:

```c
struct Persona p1;
p1.eta = 30;
```

Questo approccio alloca una quantità fissa di memoria a tempo di compilazione. Tuttavia, questa memoria viene automaticamente deallocata quando la variabile esce dal suo scope, il che rende questo metodo inadatto quando non conosciamo in anticipo quante istanze di struct avremo bisogno.

---

## 2. Struct come Puntatori

### 2.1 Introduzione ai Puntatori a Struct

Per utilizzare la memoria dinamica, dobbiamo dichiarare la struct come un **puntatore**. Un puntatore è una variabile che contiene l'indirizzo di memoria di un altro dato. Ecco come dichiarare un puntatore a una struct:

```c
struct Persona *p1;
```

A questo punto, `p1` è un puntatore che può contenere l'indirizzo di una struct di tipo `Persona`, ma non punta ancora a nessuna memoria allocata.

### 2.2 Accesso ai Campi di una Struct tramite Puntatore

Quando si lavora con un puntatore a una struct, si utilizza l'**operatore freccia** `->` per accedere ai campi della struct:

```c
p1->eta = 30;
p1->stipendio = 2500.50;
```

In alternativa, è possibile usare l'operatore di dereferenziamento `*` insieme all'operatore punto `.`:

```c
(*p1).eta = 30;
(*p1).stipendio = 2500.50;
```

Entrambi gli approcci sono equivalenti, ma l'operatore `->` è più leggibile e comunemente utilizzato.

---

## 3. Allocazione Dinamica con malloc()

### 3.1 La Funzione malloc()

La funzione `malloc()` (memory allocation) alloca un blocco di memoria sullo **heap** e restituisce un puntatore a quel blocco. La sintassi è:

```c
void* malloc(size_t size);
```

- **Parametro**: `size` è il numero di byte da allocare
- **Ritorno**: Un puntatore di tipo `void*` al blocco di memoria allocato, oppure `NULL` se l'allocazione fallisce

### 3.2 Allocazione di una Singola Struct

Per allocare memoria per una singola istanza di una struct, si utilizza `sizeof()` per determinare quanti byte sono necessari:

```c
#include <stdlib.h>
#include <stdio.h>

struct Persona {
    char nome[50];
    int eta;
    float stipendio;
};

int main() {
    // Dichiarazione di un puntatore a struct
    struct Persona *p1;
    
    // Allocazione di memoria per una struct
    p1 = (struct Persona*)malloc(sizeof(struct Persona));
    
    // Controllo se l'allocazione ha avuto successo
    if (p1 == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Assegnamento dei valori
    p1->eta = 30;
    p1->stipendio = 2500.50;
    
    // Liberazione della memoria quando non più necessaria
    free(p1);
    
    return 0;
}
```

### 3.3 Sintassi Alternativa (Raccomandato)

Una pratica consigliata è utilizzare l'operatore `sizeof()` direttamente sulla variabile puntatore, piuttosto che sul tipo, per rendere il codice più robusto:

```c
struct Persona *p1;
p1 = malloc(sizeof(*p1));  // Equivalente a malloc(sizeof(struct Persona))
```

Questo approccio ha il vantaggio che se in futuro cambieremo il tipo della variabile, il sizeof() si adatterà automaticamente senza necessità di modificare il resto del codice.

### 3.4 Controllo di Errori

È **essenziale** sempre verificare se `malloc()` ha avuto successo. Se la memoria disponibile è insufficiente, `malloc()` restituisce `NULL`:

```c
p1 = malloc(sizeof(*p1));

if (p1 == NULL) {
    printf("Errore: memoria insufficiente\n");
    return 1;
}
```

### 3.5 Liberazione della Memoria con free()

Una volta terminato l'utilizzo della memoria allocata, è **cruciale** liberarla con la funzione `free()` per evitare **perdite di memoria** (memory leaks):

```c
free(p1);
p1 = NULL;  // Pratica consigliata: impostare il puntatore a NULL
```

Impostare il puntatore a `NULL` dopo la liberazione è una pratica di sicurezza che previene l'utilizzo accidentale di un puntatore non valido (dangling pointer).

---

## 4. Array Dinamico di Struct

### 4.1 Allocazione di un Array Dinamico

Un caso molto comune è la necessità di creare un **array di strutture** con una dimensione non nota a priori. Questo si realizza allocando memoria per `n` istanze della struct:

```c
int n = 10;  // Numero di elementi
struct Persona *persone;

persone = (struct Persona*)malloc(n * sizeof(struct Persona));

if (persone == NULL) {
    printf("Errore: allocazione array fallita\n");
    return 1;
}
```

In questo caso, `persone` è un puntatore al primo elemento di un array di 10 strutture. La memoria allocata è pari a `10 * sizeof(struct Persona)` byte.

### 4.2 Accesso agli Elementi dell'Array

Grazie all'**aritmetica dei puntatori**, è possibile accedere agli elementi dell'array come se fosse un array normale:

```c
// Metodo 1: Usando notazione con indice
persone[0].eta = 25;
persone[1].stipendio = 3000.00;

// Metodo 2: Usando operatore freccia con aritmetica dei puntatori
(persone + 2)->eta = 35;

// Metodo 3: Usando dereferenziamento
(*(persone + 3)).eta = 40;
```

Tutti e tre i metodi sono equivalenti e accedono agli stessi dati.

### 4.3 Esempio Completo: Gestione di un Array di Struct

Ecco un esempio pratico che crea un array di strutture, lo riempie con dati e lo visualizza:

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Persona {
    char nome[50];
    int eta;
    float stipendio;
};

int main() {
    int n = 3;
    int i;
    struct Persona *persone;
    
    // Allocazione di memoria per 3 persone
    persone = (struct Persona*)malloc(n * sizeof(struct Persona));
    
    if (persone == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Inserimento dei dati
    strcpy(persone[0].nome, "Mario Rossi");
    persone[0].eta = 30;
    persone[0].stipendio = 2500.00;
    
    strcpy(persone[1].nome, "Giulia Bianchi");
    persone[1].eta = 28;
    persone[1].stipendio = 2800.00;
    
    strcpy(persone[2].nome, "Marco Verdi");
    persone[2].eta = 35;
    persone[2].stipendio = 3200.00;
    
    // Visualizzazione dei dati
    printf("=== Lista Persone ===\n");
    for (i = 0; i < n; i++) {
        printf("Persona %d:\n", i + 1);
        printf("  Nome: %s\n", persone[i].nome);
        printf("  Eta: %d anni\n", persone[i].eta);
        printf("  Stipendio: €%.2f\n\n", persone[i].stipendio);
    }
    
    // Liberazione della memoria
    free(persone);
    persone = NULL;
    
    return 0;
}
```

**Output previsto:**
```
=== Lista Persone ===
Persona 1:
  Nome: Mario Rossi
  Eta: 30 anni
  Stipendio: €2500.00

Persona 2:
  Nome: Giulia Bianchi
  Eta: 28 anni
  Stipendio: €2800.00

Persona 3:
  Nome: Marco Verdi
  Eta: 35 anni
  Stipendio: €3200.00
```

---

## 5. Ridimensionamento Dinamico con realloc()

### 5.1 La Funzione realloc()

A volte, dopo aver allocato un array, potremmo avere bisogno di aumentare (o ridurre) la sua dimensione. La funzione `realloc()` consente di ridimensionare un blocco di memoria precedentemente allocato:

```c
void* realloc(void* ptr, size_t new_size);
```

- **Primo parametro**: Il puntatore al blocco di memoria precedentemente allocato
- **Secondo parametro**: La nuova dimensione in byte
- **Ritorno**: Un puntatore al nuovo blocco di memoria (potrebbe essere a un indirizzo diverso)

### 5.2 Utilizzo di realloc()

```c
#include <stdlib.h>
#include <stdio.h>

struct Persona {
    char nome[50];
    int eta;
    float stipendio;
};

int main() {
    int n = 2;
    struct Persona *persone;
    
    // Allocazione iniziale per 2 persone
    persone = (struct Persona*)malloc(n * sizeof(struct Persona));
    
    if (persone == NULL) {
        printf("Errore: allocazione iniziale fallita\n");
        return 1;
    }
    
    // Riempimento dei primi due elementi
    strcpy(persone[0].nome, "Alice");
    persone[0].eta = 25;
    
    strcpy(persone[1].nome, "Bob");
    persone[1].eta = 30;
    
    printf("Array originale: %d elementi\n", n);
    
    // Ridimensionamento a 4 elementi
    n = 4;
    persone = (struct Persona*)realloc(persone, n * sizeof(struct Persona));
    
    if (persone == NULL) {
        printf("Errore: ridimensionamento fallito\n");
        return 1;
    }
    
    printf("Array ridimensionato: %d elementi\n", n);
    
    // Aggiunta di due nuovi elementi
    strcpy(persone[2].nome, "Charlie");
    persone[2].eta = 28;
    
    strcpy(persone[3].nome, "Diana");
    persone[3].eta = 32;
    
    // Visualizzazione
    for (int i = 0; i < n; i++) {
        printf("%s, eta %d\n", persone[i].nome, persone[i].eta);
    }
    
    free(persone);
    persone = NULL;
    
    return 0;
}
```

### 5.3 Considerazioni Importanti su realloc()

- **Indirizzo di memoria**: `realloc()` potrebbe allocare memoria a un indirizzo diverso. Se il ridimensionamento non può avvenire nel medesimo blocco di memoria, `realloc()` copia i dati nel nuovo blocco e libera il vecchio.
- **Gestione errori**: Se `realloc()` fallisce, restituisce `NULL` senza modificare il puntatore originale. Per questa ragione, è prudente assegnare il risultato di `realloc()` a una variabile temporanea:

```c
struct Persona *temp = (struct Persona*)realloc(persone, n * sizeof(struct Persona));

if (temp == NULL) {
    printf("Errore: realloc fallita\n");
    free(persone);  // Libera la memoria originale
    return 1;
}

persone = temp;
```

---

## 6. Struct Contenenti Puntatori a Memoria Dinamica

### 6.1 Struct con Campi Dinamici

Una situazione ancora più complessa si verifica quando i campi della struct stessa sono puntatori a memoria dinamicamente allocata. Ad esempio:

```c
struct Prodotto {
    int id;
    char *descrizione;  // Puntatore a stringa dinamica
    float prezzo;
};
```

### 6.2 Allocazione Completa

Quando si lavora con questa struct, occorre allocare memoria sia per la struct stessa che per i suoi campi dinamici:

```c
struct Prodotto *p = (struct Prodotto*)malloc(sizeof(struct Prodotto));

if (p == NULL) {
    printf("Errore: allocazione struct fallita\n");
    return 1;
}

// Allocazione della descrizione
p->descrizione = (char*)malloc(100 * sizeof(char));

if (p->descrizione == NULL) {
    printf("Errore: allocazione descrizione fallita\n");
    free(p);
    return 1;
}

p->id = 1;
strcpy(p->descrizione, "Prodotto di qualita");
p->prezzo = 19.99;
```

### 6.3 Deallocazione Completa

È cruciale liberare la memoria nell'ordine corretto: prima i campi dinamici, poi la struct stessa:

```c
free(p->descrizione);  // Libera la memoria della descrizione
free(p);               // Libera la memoria della struct
p = NULL;
```

---

## 7. Pratiche Consigliate

### 7.1 Checklist per la Memoria Dinamica

1. **Includere la libreria stdlib.h**: Necessaria per `malloc()`, `calloc()`, `realloc()` e `free()`
2. **Controllare sempre il risultato di malloc()**: Verificare che il puntatore non sia `NULL`
3. **Utilizzare sizeof(*puntatore)**: Rende il codice più robusto a cambiamenti futuri
4. **Liberare la memoria quando non necessaria**: Evitare memory leaks
5. **Impostare a NULL dopo free()**: Previene l'utilizzo di puntatori non validi
6. **Per struct con campi dinamici**: Liberare prima i campi, poi la struct
7. **Usare realloc() correttamente**: Salvare il risultato in una variabile temporanea per gestire gli errori

### 7.2 Evitare Errori Comuni

- **Memory leak**: Allocare memoria e non liberarla mai
- **Dangling pointer**: Utilizzare un puntatore dopo aver liberato la memoria a cui punta
- **Buffer overflow**: Accedere a elementi oltre i limiti dell'array allocato
- **Double free**: Liberare due volte lo stesso blocco di memoria

---
