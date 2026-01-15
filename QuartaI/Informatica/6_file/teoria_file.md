# Gestione dei File in C

## Definizione di File e Archivio

Un **file** è un insieme di dati memorizzati in modo permanente su un supporto (come disco o SSD). In generale, possiamo distinguere tra:

- **Archivio fisico:** rappresenta *come* i dati sono effettivamente memorizzati nel dispositivo (settori, blocchi, cluster).
- **Archivio logico:** rappresenta *come* il programmatore o l'utente vede i dati, cioè l'insieme delle informazioni organizzate in un certo modo (per esempio record, righe di testo, strutture binarie, ecc.).

In C, i file vengono gestiti come **sequenze di byte**, senza struttura interna predefinita: spetta al programmatore interpretare il contenuto.

***

## Tipi di Accesso ai File

### Accesso Sequenziale

Nel **metodo sequenziale**, i dati vengono letti o scritti **uno dopo l'altro**, proprio come accade con un nastro magnetico.
È adatto, ad esempio, per file di testo o log.

Esempio:

```c
FILE *f = fopen("dati.txt", "r");
char riga[100];
while (fgets(riga, sizeof(riga), f)) {
    printf("%s", riga); // legge riga per riga
}
fclose(f);
```


### Accesso Diretto (Random Access)

Nel **metodo diretto**, è possibile accedere a una parte qualsiasi del file tramite la posizione (offset).
Questo è utile quando si gestiscono file binari o record di dimensione fissa.

Esempio:

```c
FILE *f = fopen("numeri.bin", "rb");
int numero;

// sposta il puntatore al terzo intero (offset = 2 * sizeof(int))
fseek(f, 2 * sizeof(int), SEEK_SET);
fread(&numero, sizeof(int), 1, f);
printf("Terzo numero: %d\n", numero);
fclose(f);
```


***

## Stream di Input e Output

In C, i file sono gestiti tramite **stream**, un flusso logico di dati che viaggia tra il programma e il file.
Ogni stream è associato a un oggetto di tipo `FILE`.

Esempio di stream standard:

- `stdin`: input standard (tastiera)
- `stdout`: output standard (schermo)
- `stderr`: output errori (schermo)

Ogni volta che si apre un file con `fopen`, il sistema associa un nuovo stream al file.

***

## Apertura e Chiusura dei File

Le funzioni principali per gestire i file in C sono:

### `fopen_s`

Apre un file e restituisce un puntatore al tipo `FILE`.
È una versione "sicura" di `fopen` (standard C11).

Sintassi:

```c
errno_t fopen_s(FILE **stream, const char *filename, const char *mode);
```

Esempio:

```c
FILE *f = NULL;
if (fopen_s(&f, "dati.txt", "r") == 0) {
    printf("File aperto con successo.\n");
    fclose(f);
} else {
    perror("Errore nell'apertura del file");
}
```

I principali **modi di apertura** sono:

- `"r"` → lettura (il file deve esistere)
- `"w"` → scrittura (sovrascrive o crea un file)
- `"a"` → aggiunta (append)
- `"rb"`, `"wb"`, `"ab"` → versioni per file binari
- `"r+"`, `"w+"`, `"a+"` → lettura e scrittura


### `fclose`

Chiude il file e libera le risorse associate.

```c
if (fclose(f) != 0)
    perror("Errore nella chiusura");
```


***

## Lettura e Scrittura

Funzioni comuni:

- `fgetc(FILE *f)` / `fputc(int c, FILE *f)` → leggono/scrivono un carattere
- `fgets(char *s, int n, FILE *f)` / `fputs(const char *s, FILE *f)` → leggono/scrivono stringhe
- `fread(void *p, size_t size, size_t n, FILE *f)` / `fwrite(const void *p, size_t size, size_t n, FILE *f)` → operano su dati binari

Esempio di scrittura binaria:

```c
FILE *f;
fopen_s(&f, "valori.bin", "wb");
int x = 42;
fwrite(&x, sizeof(int), 1, f);
fclose(f);
```


***

## Fine File ed Errori

### `EOF` (End Of File)

Il simbolo `EOF` indica la **fine del file** o un **errore di lettura**.
Viene restituito, ad esempio, da `fgetc` quando non ci sono più caratteri da leggere.

Esempio:

```c
int c;
while ((c = fgetc(f)) != EOF) {
    putchar(c);
}
```


### `feof` e `ferror`

- `feof(FILE *f)` restituisce un valore diverso da zero se si è raggiunta la fine del file.
- `ferror(FILE *f)` restituisce un valore diverso da zero se è avvenuto un errore nella lettura o scrittura.

Esempio combinato:

```c
FILE *f = fopen("testo.txt", "r");
int ch;
while ((ch = fgetc(f)) != EOF) {
    putchar(ch);
}
if (feof(f)) {
    printf("\nFine del file raggiunta.\n");
} else if (ferror(f)) {
    printf("\nErrore durante la lettura.\n");
}
fclose(f);
```


***

## File Binari: Concetti Fondamentali

I **file binari** memorizzano i dati nella loro rappresentazione interna (byte grezzi), a differenza dei file di testo che usano caratteri ASCII/UTF-8.

Vantaggi dei file binari:

- **Efficienza:** occupano meno spazio (un `int` occupa sempre 4 byte, non i caratteri delle cifre)
- **Velocità:** lettura/scrittura più rapida
- **Precisione:** nessuna perdita di dati nella conversione numerica

Svantaggi:

- Non sono leggibili con un editor di testo
- Dipendono dall'architettura (endianness, dimensione dei tipi)

***

## Funzioni per File Binari

### `fwrite`

Scrive un blocco di dati binari su file.

Sintassi:

```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
```

- `ptr`: puntatore ai dati da scrivere
- `size`: dimensione in byte di ogni elemento
- `count`: numero di elementi da scrivere
- Ritorna il numero di elementi effettivamente scritti


### `fread`

Legge un blocco di dati binari da file.

Sintassi:

```c
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
```

- `ptr`: puntatore al buffer di destinazione
- `size`: dimensione in byte di ogni elemento
- `count`: numero di elementi da leggere
- Ritorna il numero di elementi effettivamente letti


### `fseek`

Sposta il cursore (file position indicator) a una posizione specifica.

Sintassi:

```c
int fseek(FILE *stream, long offset, int origin);
```

- `offset`: spostamento in byte
- `origin`: punto di riferimento
    - `SEEK_SET` → inizio del file
    - `SEEK_CUR` → posizione corrente
    - `SEEK_END` → fine del file
- Ritorna 0 se ha successo, diverso da 0 in caso di errore


### `ftell`

Restituisce la posizione corrente del cursore nel file.

```c
long pos = ftell(f);
printf("Posizione corrente: %ld byte\n", pos);
```


### `rewind`

Riporta il cursore all'inizio del file (equivale a `fseek(f, 0, SEEK_SET)`).

```c
rewind(f);
```


***

## Esempio Completo: Gestione di Struct su File Binario

### Definizione della Struct

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float voto;
} Studente;
```


### Scrittura di un Array di Struct

```c
void salvaStudenti(const char *nomeFile, Studente studenti[], int n) {
    FILE *f = NULL;
    if (fopen_s(&f, nomeFile, "wb") != 0) {
        perror("Errore apertura file");
        return;
    }
    
    // scrive prima il numero di studenti
    fwrite(&n, sizeof(int), 1, f);
    
    // scrive l'intero array
    fwrite(studenti, sizeof(Studente), n, f);
    
    fclose(f);
    printf("Salvati %d studenti.\n", n);
}
```


### Lettura di un Array di Struct

```c
int caricaStudenti(const char *nomeFile, Studente studenti[], int maxDim) {
    FILE *f = NULL;
    if (fopen_s(&f, nomeFile, "rb") != 0) {
        perror("Errore apertura file");
        return 0;
    }
    
    int n;
    fread(&n, sizeof(int), 1, f);
    
    if (n > maxDim) {
        printf("Attenzione: il file contiene piu' studenti del previsto.\n");
        n = maxDim;
    }
    
    fread(studenti, sizeof(Studente), n, f);
    
    fclose(f);
    return n;
}
```


### Accesso Diretto a un Record Specifico

```c
int leggiStudente(const char *nomeFile, int indice, Studente *s) {
    FILE *f = NULL;
    if (fopen_s(&f, nomeFile, "rb") != 0) {
        perror("Errore apertura file");
        return 0;
    }
    
    // salta l'header (numero studenti) + i record precedenti
    long offset = sizeof(int) + indice * sizeof(Studente);
    
    if (fseek(f, offset, SEEK_SET) != 0) {
        perror("Errore fseek");
        fclose(f);
        return 0;
    }
    
    size_t letti = fread(s, sizeof(Studente), 1, f);
    fclose(f);
    
    return (letti == 1);
}
```


### Modifica di un Record Specifico

```c
int modificaStudente(const char *nomeFile, int indice, Studente *s) {
    FILE *f = NULL;
    // "r+b" permette lettura e scrittura su file binario esistente
    if (fopen_s(&f, nomeFile, "r+b") != 0) {
        perror("Errore apertura file");
        return 0;
    }
    
    long offset = sizeof(int) + indice * sizeof(Studente);
    
    if (fseek(f, offset, SEEK_SET) != 0) {
        perror("Errore fseek");
        fclose(f);
        return 0;
    }
    
    size_t scritti = fwrite(s, sizeof(Studente), 1, f);
    fclose(f);
    
    return (scritti == 1);
}
```


### Programma Main di Esempio

```c
int main() {
    Studente classe[3] = {
        {1, "Mario Rossi", 28.5},
        {2, "Anna Verdi", 30.0},
        {3, "Luca Bianchi", 25.0}
    };
    
    // Salva gli studenti
    salvaStudenti("classe.bin", classe, 3);
    
    // Legge il secondo studente (indice 1)
    Studente s;
    if (leggiStudente("classe.bin", 1, &s)) {
        printf("Studente[1]: %s, voto: %.1f\n", s.nome, s.voto);
    }
    
    // Modifica il voto del secondo studente
    s.voto = 30.0;
    strcpy_s(s.nome, sizeof(s.nome), "Anna Verdi (lode)");
    modificaStudente("classe.bin", 1, &s);
    
    // Ricarica e stampa tutti
    Studente caricati[10];
    int n = caricaStudenti("classe.bin", caricati, 10);
    
    printf("\n--- Elenco completo ---\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %s | Voto: %.1f\n",
               caricati[i].id, caricati[i].nome, caricati[i].voto);
    }
    
    return 0;
}
```


***

## Salvataggio e Caricamento di Liste Collegate

Le **liste collegate** non possono essere salvate direttamente (i puntatori non hanno senso fuori dalla memoria). Bisogna salvare solo i **dati** di ogni nodo.

### Definizione del Nodo

```c
typedef struct Nodo {
    int dato;
    struct Nodo *next;
} Nodo;
```


### Salvataggio della Lista su File

```c
void salvaLista(const char *nomeFile, Nodo *testa) {
    FILE *f = NULL;
    if (fopen_s(&f, nomeFile, "wb") != 0) {
        perror("Errore apertura file");
        return;
    }
    
    // conta i nodi
    int count = 0;
    Nodo *p = testa;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    
    // scrive il numero di nodi
    fwrite(&count, sizeof(int), 1, f);
    
    // scrive solo il campo dato di ogni nodo
    p = testa;
    while (p != NULL) {
        fwrite(&(p->dato), sizeof(int), 1, f);
        p = p->next;
    }
    
    fclose(f);
    printf("Lista salvata: %d elementi.\n", count);
}
```


### Caricamento della Lista da File

```c
Nodo* caricaLista(const char *nomeFile) {
    FILE *f = NULL;
    if (fopen_s(&f, nomeFile, "rb") != 0) {
        perror("Errore apertura file");
        return NULL;
    }
    
    int count;
    if (fread(&count, sizeof(int), 1, f) != 1) {
        fclose(f);
        return NULL;
    }
    
    Nodo *testa = NULL;
    Nodo *coda = NULL;
    
    for (int i = 0; i < count; i++) {
        int valore;
        fread(&valore, sizeof(int), 1, f);
        
        // crea un nuovo nodo
        Nodo *nuovo = (Nodo*)malloc(sizeof(Nodo));
        nuovo->dato = valore;
        nuovo->next = NULL;
        
        // inserisce in coda per mantenere l'ordine
        if (testa == NULL) {
            testa = nuovo;
            coda = nuovo;
        } else {
            coda->next = nuovo;
            coda = nuovo;
        }
    }
    
    fclose(f);
    return testa;
}
```


### Esempio di Utilizzo

```c
#include <stdlib.h>

// Funzione ausiliaria per aggiungere in testa
Nodo* aggiungiInTesta(Nodo *testa, int valore) {
    Nodo *nuovo = (Nodo*)malloc(sizeof(Nodo));
    nuovo->dato = valore;
    nuovo->next = testa;
    return nuovo;
}

// Funzione per stampare la lista
void stampaLista(Nodo *testa) {
    printf("Lista: ");
    while (testa != NULL) {
        printf("%d -> ", testa->dato);
        testa = testa->next;
    }
    printf("NULL\n");
}

int main() {
    // Crea una lista: 10 -> 20 -> 30 -> NULL
    Nodo *lista = NULL;
    lista = aggiungiInTesta(lista, 30);
    lista = aggiungiInTesta(lista, 20);
    lista = aggiungiInTesta(lista, 10);
    
    stampaLista(lista);  // Output: 10 -> 20 -> 30 -> NULL
    
    // Salva su file
    salvaLista("lista.bin", lista);
    
    // Ricarica da file
    Nodo *listaNuova = caricaLista("lista.bin");
    
    printf("Dopo caricamento:\n");
    stampaLista(listaNuova);  // Output: 10 -> 20 -> 30 -> NULL
    
    return 0;
}
```


***

## Riepilogo delle Funzioni Principali

| Funzione | Descrizione | Esempio d'uso |
| :-- | :-- | :-- |
| `fopen_s` | Apre un file in modo sicuro | `fopen_s(&f, "file.bin", "rb")` |
| `fclose` | Chiude il file | `fclose(f)` |
| `fread` | Legge dati binari | `fread(&x, sizeof(x), 1, f)` |
| `fwrite` | Scrive dati binari | `fwrite(&x, sizeof(x), 1, f)` |
| `fseek` | Sposta il cursore | `fseek(f, 100, SEEK_SET)` |
| `ftell` | Restituisce posizione corrente | `long pos = ftell(f)` |
| `rewind` | Torna all'inizio del file | `rewind(f)` |
| `feof` | Verifica fine file | `if (feof(f)) …` |
| `ferror` | Controlla errori | `if (ferror(f)) …` |


***


