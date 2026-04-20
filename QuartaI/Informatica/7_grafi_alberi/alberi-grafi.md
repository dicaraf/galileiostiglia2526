# Alberi e Grafi in C

## 1. Nozioni di base di teoria dei grafi

Un **grafo** \(G = (V, E)\) è costituito da un insieme di vertici \(V\) e da un insieme di archi \(E\) che collegano coppie di vertici.

### 1.1 Grafi orientati e non orientati

- **Grafo non orientato**: ogni arco \(\{u, v\} \in E\) non ha verso; rappresenta una relazione simmetrica tra i vertici \(u\) e \(v\).
- **Grafo orientato (digrafo)**: ogni arco \((u, v) \in E\) ha un verso; rappresenta una relazione direzionale dal vertice \(u\) al vertice \(v\).

Esempio illustrativo di grafo orientato e non orientato:

![Esempio di grafo orientato e non orientato](https://pplx-res.cloudinary.com/image/upload/pplx_search_images/c627d2558c40c1cc400573cb7a19295067bc79a6.jpg)

### 1.2 Grafi connessi e componenti connesse

- Un grafo non orientato è **connesso** se esiste un cammino tra ogni coppia di vertici.
- Un grafo orientato è **fortemente connesso** se per ogni coppia di vertici \(u, v\) esiste un cammino orientato da \(u\) a \(v\) e da \(v\) a \(u\).
- Le **componenti connesse** (o fortemente connesse) sono sotto-grafi massimali in cui ogni coppia di vertici è raggiungibile.

### 1.3 Grafi aciclici

Un grafo è **aciclico** se non contiene cicli, ossia cammini chiusi con almeno un arco in cui il primo e l’ultimo vertice coincidono e non si ripetono archi o vertici (tranne il primo/ultimo). Un esempio importante è il **DAG** (Directed Acyclic Graph), spesso usato per rappresentare dipendenze (per esempio in scheduling di attività).

---

## 2. Alberi come grafi particolari

Un **albero** è un grafo non orientato connesso e aciclico. Equivalentemente, è un grafo con \(n\) vertici e \(n-1\) archi, senza cicli.

### 2.1 Alberi liberi

Un **albero libero** è un albero considerato senza una radice designata. In questa visione, tutti i vertici sono sullo stesso piano gerarchico: non c’è un “alto” o “basso”, ma solo collegamenti.

Caratteristiche:
- Struttura puramente non orientata.
- Nessun vertice privilegiato come radice.
- Spesso usato in contesti matematici astratti, meno nella programmazione dove la radice è quasi sempre esplicita.

### 2.2 Alberi radicati

Un **albero radicato** è un albero in cui uno dei vertici è scelto come **radice**. Tutti gli archi sono concettualmente orientati “lontano” dalla radice verso le foglie.

Caratteristiche principali:
- Esiste un percorso unico dalla radice a ogni altro nodo.
- Introduce una gerarchia naturale (genitore/figlio, antenato/discendente).
- È il modello standard usato in strutture dati (alberi binari, BST, heap, ecc.).

---

## 3. Genealogia e topografia degli alberi

### 3.1 Genealogia: relazioni tra nodi

In un albero radicato, si parla spesso in termini genealogici:

- **Radice**: nodo senza genitore.
- **Genitore (padre)** di un nodo \(v\): il nodo immediatamente sopra \(v\) lungo il cammino dalla radice.
- **Figlio**: nodo immediatamente sotto un genitore.
- **Fratelli**: nodi che condividono lo stesso genitore.
- **Antenato**: un nodo che si trova sul cammino dalla radice a un dato nodo.
- **Discendente**: un nodo che si trova in qualche posizione sotto un altro nodo.
- **Foglia**: nodo senza figli (grado interno 0).
- **Nodo interno**: nodo che non è né radice né foglia, ovvero ha almeno un figlio.

### 3.2 Topografia: profondità, altezza, livello

Per descrivere la “forma” dell’albero si usano varie misure:

- **Livello** di un nodo: spesso definito come distanza (numero di archi) dalla radice. La radice ha livello 0 (o 1, a seconda delle convenzioni).
- **Profondità** di un nodo: sinonimo di livello (talvolta si intende la distanza dalla radice).
- **Altezza di un nodo**: lunghezza massima di un cammino che parte da quel nodo e arriva a una foglia.
- **Altezza dell’albero**: altezza della radice, cioè la massima profondità di qualsiasi nodo.
- **Grado di un nodo**: numero di figli (adiacenze in direzione discendente).

Queste nozioni sono fondamentali per analizzare la complessità delle operazioni sugli alberi (es. tempo di ricerca in un albero binario di ricerca).

---

## 4. Alberi ordinati e orientamento grafico

### 4.1 Albero ordinato

Un **albero ordinato** è un albero radicato in cui l’insieme dei figli di ogni nodo è **ordinato** (esiste un “primo figlio”, un “secondo figlio” e così via). Negli alberi binari, l’ordine è naturalmente dato dai puntatori `left` (sinistro) e `right` (destro).

Questo ordine è importante perché:
- Visite come preorder, inorder e postorder dipendono dall’ordine dei figli.
- In alberi con più di due figli, l’ordine può rappresentare priorità, posizionamento, ecc.

### 4.2 Ordinamento verticale e orizzontale (rappresentazione)

Quando si disegna un albero si può scegliere la disposizione grafica:

- **Albero ordinato verticalmente**: la radice in alto, i livelli successivi disposti verso il basso; è la rappresentazione più comune nei testi di informatica e nelle librerie grafiche.
- **Albero ordinato orizzontalmente**: la radice a sinistra, con i figli verso destra; spesso usato in stampe testuali (ad esempio, alberi stampati su console ruotati di 90 gradi).

La scelta è puramente di visualizzazione: la struttura logica (radice, figli, profondità) rimane identica.

---

## 5. Alberi k-ari

Un **albero k-ario** è un albero radicato in cui ogni nodo ha **al massimo k figli**. Gli alberi binari sono un caso particolare con \(k = 2\).

Esempi:
- **Albero binario**: ogni nodo ha al massimo due figli (sinistro e destro).
- **Albero ternario**: \(k = 3\), ogni nodo può avere fino a tre figli.
- **Heap binario**, **alberi B**, **trie**: sono tutti esempi di alberi k-ari (con strutture e vincoli diversi).

---

## 6. Visite di un albero: ampiezza e profondità

Le visite (o traversate) sono algoritmi che permettono di “toccare” tutti i nodi di un albero secondo un certo ordine.

### 6.1 Visita in ampiezza (BFS sugli alberi)

La **visita in ampiezza** (Breadth-First Search, BFS) esplora i nodi per livelli: prima la radice, poi tutti i nodi al livello 1, poi tutti quelli al livello 2, e così via.

Implementazione tipica:
- Si utilizza una **coda** (FIFO).
- Si inserisce la radice in coda.
- Finché la coda non è vuota: si estrae un nodo, lo si visita, poi si inseriscono in coda tutti i suoi figli non ancora visitati.

### 6.2 Visita in profondità (DFS) e varianti

La **visita in profondità** (Depth-First Search, DFS) esplora quanto più possibile lungo ciascun ramo prima di tornare indietro. Sugli alberi, la DFS ha tre varianti standard, che differiscono per l’ordine in cui si visita la radice rispetto ai sottoalberi sinistro e destro.

Per un nodo generico `n` con sottoalbero sinistro `left` e destro `right`, abbiamo:

- **Preorder** (visita anticipata):
  1. visita la radice;
  2. visita il sottoalbero sinistro;
  3. visita il sottoalbero destro.
- **Inorder** (visita simmetrica):
  1. visita il sottoalbero sinistro;
  2. visita la radice;
  3. visita il sottoalbero destro.
- **Postorder** (visita differita):
  1. visita il sottoalbero sinistro;
  2. visita il sottoalbero destro;
  3. visita la radice.

Esempio visivo di un albero binario con le tre visite:

![Visite preorder, inorder e postorder su un albero binario](https://pplx-res.cloudinary.com/image/upload/pplx_search_images/f3d4c91029cf191753531305de1a7532bff2eada.jpg)

La visita **inorder** su un **albero binario di ricerca** restituisce i nodi in ordine crescente rispetto alle chiavi memorizzate.

---

## 7. Alberi binari in C

Un **albero binario** è un albero k-ario con \(k = 2\): ogni nodo ha al più due figli, detti figlio sinistro e figlio destro. È la struttura di base su cui si costruiscono molte altre strutture dati (BST, heap, ecc.).

### 7.1 Definizione della struttura con `struct` e `typedef`

In C, un nodo di albero binario viene normalmente definito con una `struct` autoreferenziale:

```c
typedef struct Nodo {
    int info;                    // campo dato
    struct Nodo *left;           // puntatore al figlio sinistro
    struct Nodo *right;          // puntatore al figlio destro
} Nodo;

typedef Nodo *Albero;            // tipo puntatore alla radice dell'albero
```

L’uso di `typedef` permette di riferirsi alla struttura con nomi più semplici (`Albero` invece di `struct Nodo *`).

Una versione più generica può usare un tipo astratto per il dato:

```c
typedef int Tatomo;              // tipo del dato (modificabile)

typedef struct elem {
    Tatomo info;
    struct elem *sx, *dx;
} nodo, *albero;
```

### 7.2 Funzioni primitive sugli alberi binari

Alcune funzioni primitive utili sono:

```c
// Crea un albero vuoto
Albero emptytree(void) {
    return NULL;
}

// Verifica se l'albero è vuoto
int empty(Albero t) {
    return (t == NULL);
}

// Restituisce il valore della radice
int root(Albero t) {
    return t->info;
}

// Restituisce il sottoalbero sinistro
Albero left(Albero t) {
    return t->left;
}

// Restituisce il sottoalbero destro
Albero right(Albero t) {
    return t->right;
}

// Costruisce un nuovo albero con radice e e sottoalberi l e r
Albero cons_tree(int e, Albero l, Albero r) {
    Albero nuovo = (Albero)malloc(sizeof(Nodo));
    nuovo->info = e;
    nuovo->left = l;
    nuovo->right = r;
    return nuovo;
}
```

### 7.3 Visite ricorsive (DFS sugli alberi binari)

**Preorder**:

```c
void preOrder(Nodo *node) {
    if (node != NULL) {
        printf("%d ", node->info);      // visita la radice
        preOrder(node->left);           // visita sottoalbero sinistro
        preOrder(node->right);          // visita sottoalbero destro
    }
}
```

**Inorder**:

```c
void inOrder(Nodo *node) {
    if (node != NULL) {
        inOrder(node->left);            // visita sottoalbero sinistro
        printf("%d ", node->info);      // visita la radice
        inOrder(node->right);           // visita sottoalbero destro
    }
}
```

**Postorder**:

```c
void postOrder(Nodo *node) {
    if (node != NULL) {
        postOrder(node->left);          // visita sottoalbero sinistro
        postOrder(node->right);         // visita sottoalbero destro
        printf("%d ", node->info);      // visita la radice
    }
}
```

### 7.4 Visita in ampiezza (BFS) su albero binario

La BFS su un albero binario può essere implementata con una coda di puntatori a `Nodo`:

```c
void bfsTree(Nodo *root) {
    if (root == NULL) return;

    Nodo *queue[100];   // per semplicità, dimensione fissa
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front != rear) {
        Nodo *curr = queue[front++];
        printf("%d ", curr->info);

        if (curr->left != NULL)  queue[rear++] = curr->left;
        if (curr->right != NULL) queue[rear++] = curr->right;
    }
}
```

---

## 8. Alberi binari di ricerca (BST)

Un **albero binario di ricerca** (Binary Search Tree, BST) è un albero binario che soddisfa la proprietà:

> per ogni nodo `x`, tutti i nodi del sottoalbero sinistro hanno chiave minore (o uguale) a quella di `x`, e tutti i nodi del sottoalbero destro hanno chiave maggiore.

Questa proprietà permette di effettuare ricerche, inserimenti e cancellazioni in tempo proporzionale all’altezza dell’albero.

### 8.1 Struttura del BST

```c
typedef struct BinaryTreeNode {
    int key;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef BinaryTreeNode *SearchTree;
```

### 8.2 Creazione di un nuovo nodo

```c
BinaryTreeNode* newNodeCreate(int value) {
    BinaryTreeNode* temp = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    temp->key = value;
    temp->left = temp->right = NULL;
    return temp;
}
```

### 8.3 Ricerca in un BST

```c
BinaryTreeNode* searchNode(BinaryTreeNode* root, int target) {
    if (root == NULL || root->key == target) {
        return root;
    }
    if (root->key < target) {
        return searchNode(root->right, target);
    }
    return searchNode(root->left, target);
}
```

La complessità è \(O(\log n)\) nel caso medio, \(O(n)\) nel caso peggiore (albero degenerato).

### 8.4 Inserimento in un BST

```c
BinaryTreeNode* insertNode(BinaryTreeNode* node, int value) {
    if (node == NULL) {
        return newNodeCreate(value);
    }
    if (value < node->key) {
        node->left = insertNode(node->left, value);
    }
    else if (value > node->key) {
        node->right = insertNode(node->right, value);
    }
    return node;
}
```

### 8.5 Cancellazione da un BST

Tre casi principali:

1. Nodo foglia (senza figli).
2. Nodo con un solo figlio.
3. Nodo con due figli (si sostituisce con il successore inorder).

```c
BinaryTreeNode* findMin(BinaryTreeNode* root) {
    if (root == NULL) return NULL;
    if (root->left != NULL) return findMin(root->left);
    return root;
}

BinaryTreeNode* deleteNode(BinaryTreeNode* root, int x) {
    if (root == NULL) return NULL;

    if (x > root->key) {
        root->right = deleteNode(root->right, x);
    }
    else if (x < root->key) {
        root->left = deleteNode(root->left, x);
    }
    else {
        // Caso 1: nodo foglia
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Caso 2: un solo figlio
        else if (root->left == NULL || root->right == NULL) {
            BinaryTreeNode* temp = (root->left == NULL) ?
                                    root->right : root->left;
            free(root);
            return temp;
        }
        // Caso 3: due figli
        else {
            BinaryTreeNode* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}
```

### 8.6 Complessità delle operazioni su BST

| Operazione   | Caso migliore | Caso medio | Caso peggiore |
|--------------|--------------|------------|----------------|
| Ricerca      | \(O(1)\)     | \(O(\log n)\) | \(O(n)\)       |
| Inserimento  | \(O(1)\)     | \(O(\log n)\) | \(O(n)\)       |
| Cancellazione| \(O(1)\)     | \(O(\log n)\) | \(O(n)\)       |

Nel caso peggiore, l’albero diventa “sbilanciato” e si comporta come una lista concatenata.

---

## 9. Grafi in C: rappresentazione

### 9.1 Matrice di adiacenza

Rappresenta il grafo con una matrice \(V \times V\) (per \(V\) vertici), dove `adj[i][j]` indica la presenza (e opzionalmente il peso) di un arco tra `i` e `j`.

```c
#define MAX_VERTICES 100

typedef struct Graph {
    int V;                              // numero di vertici
    int adj[MAX_VERTICES][MAX_VERTICES]; // matrice di adiacenza
} Graph;

Graph* Graph_create(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->adj[i][j] = 0;
        }
    }
    return g;
}

void Graph_addEdge(Graph* g, int v, int w) {
    g->adj[v][w] = 1;
    // Per grafo non orientato: g->adj[w][v] = 1;
}
```

- **Vantaggi**: test di adiacenza `adj[u][v]` in tempo \(O(1)\).
- **Svantaggi**: uso di memoria \(O(V^2)\), inefficiente per grafi sparsi.

### 9.2 Liste di adiacenza

Ogni vertice mantiene una lista dei vertici adiacenti.

```c
typedef struct edge {
    int key;                  // vertice destinazione
    struct edge *next;        // prossimo arco nella lista
} edge;

typedef struct graph {
    int nv;                   // numero di vertici
    edge **adj;               // array di liste di adiacenza
} graph;

graph* createGraph(int vertices) {
    graph* g = (graph*)malloc(sizeof(graph));
    g->nv = vertices;
    g->adj = (edge**)malloc(vertices * sizeof(edge*));
    for (int i = 0; i < vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void addEdge(graph* g, int src, int dest) {
    edge* newEdge = (edge*)malloc(sizeof(edge));
    newEdge->key = dest;
    newEdge->next = g->adj[src];
    g->adj[src] = newEdge;
}
```

- **Vantaggi**: memoria \(O(V + E)\), adatta a grafi sparsi.
- **Svantaggi**: test di adiacenza più costoso (\(O(\text{grado}(v))\)).

---

## 10. Visite di grafi: DFS e BFS

### 10.1 DFS (Depth-First Search)

La DFS esplora il grafo andando il più in profondità possibile lungo ciascun ramo prima di fare backtracking. Con liste di adiacenza ha complessità \(O(V + E)\).

Esempio (con una struttura `Graph` che ha per ogni vertice una lista di adiacenza):

```c
void DFS(struct Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    struct Node* currentNode = graph->array[vertex].head;
    while (currentNode) {
        int adjacentVertex = currentNode->data;
        if (!visited[adjacentVertex]) {
            DFS(graph, adjacentVertex, visited);
        }
        currentNode = currentNode->next;
    }
}
```

### 10.2 BFS (Breadth-First Search)

La BFS visita tutti i vertici alla stessa distanza dalla sorgente prima di passare ai vertici più lontani.

```c
void Graph_BFS(Graph* g, int s) {
    bool visited[MAX_VERTICES];
    for (int i = 0; i < g->V; i++) visited[i] = false;

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[s] = true;
    queue[rear++] = s;

    while (front != rear) {
        s = queue[front++];
        printf("%d ", s);

        for (int adjacent = 0; adjacent < g->V; adjacent++) {
            if (g->adj[s][adjacent] && !visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear++] = adjacent;
            }
        }
    }
}
```

La BFS è anche usata per calcolare la distanza minima (in numero di archi) da una sorgente in grafi non pesati.

---

## 11. Ricerca del cammino ottimo: Dijkstra e Bellman-Ford

### 11.1 Algoritmo di Dijkstra

L’algoritmo di Dijkstra calcola i cammini minimi da una sorgente a tutti gli altri vertici in un grafo con pesi **non negativi**.

Schema generale:
1. Inizializza tutte le distanze a infinito, tranne la sorgente (0).
2. Usa un insieme (o coda di priorità) di vertici non ancora definitivi.
3. Seleziona il vertice \(u\) con distanza minima tra quelli non definitivi.
4. Per ogni vicino \(v\) di \(u\), prova a migliorare `dist[v]` tramite \(u\) (operazione di **rilassamento**).
5. Ripeti finché tutti i vertici sono definitivi.

La complessità è \(O(V^2)\) con matrice di adiacenza, riducibile a \(O((V + E) \log V)\) usando una coda di priorità (heap binario).

### 11.2 Algoritmo di Bellman-Ford

L’algoritmo di Bellman-Ford gestisce anche grafi con pesi negativi e può rilevare cicli di peso negativo.

Schema generale:
1. Inizializza `dist[src] = 0`, tutte le altre distanze a infinito.
2. Ripeti \(V - 1\) volte:
   - per ogni arco \((u, v)\) con peso \(w\), se `dist[u] + w < dist[v]` allora aggiorna `dist[v]`.
3. Fase di controllo: per ogni arco \((u, v)\), se `dist[u] + w < dist[v]` esiste un ciclo di peso negativo.

La complessità è \(O(V \times E)\).

---

## 12. Grafi euleriani e hamiltoniani

### 12.1 Grafi euleriani

Un grafo è **euleriano** se contiene un circuito euleriano, ossia un ciclo che passa **una e una sola volta per ogni arco**.

Teorema fondamentale:
- Un grafo connesso non orientato è euleriano se e solo se **tutti i vertici hanno grado pari**.
- Se esattamente due vertici hanno grado dispari, esiste un **cammino euleriano** (non chiuso) che inizia e termina in questi vertici.

#### Algoritmo di Fleury

L’algoritmo di Fleury costruisce esplicitamente un cammino/circuito euleriano scegliendo, a ogni passo, un arco che non sia un ponte (se possibile).

Idea di base:

```text
1. Scegli un vertice di partenza (uno dei vertici di grado dispari, oppure uno qualunque se tutti sono pari).
2. Finché esistono archi uscenti dal vertice corrente:
   - scegli un arco che non sia un ponte (a meno che sia l'unico disponibile);
   - attraversa l'arco, aggiungilo al cammino, e rimuovilo dal grafo;
3. Il cammino ottenuto è euleriano.
```

### 12.2 Grafi hamiltoniani

Un grafo è **hamiltoniano** se contiene un ciclo hamiltoniano, cioè un ciclo che visita **ogni vertice esattamente una volta** (eccetto il vertice di partenza/arrivo).

A differenza del caso euleriano, non esiste una caratterizzazione semplice e completa dei grafi hamiltoniani.

Alcuni risultati classici:
- **Teorema di Dirac**: se un grafo semplice con \(n \ge 3\) vertici ha grado minimo almeno \(n/2\), allora è hamiltoniano.
- **Teorema di Ore**: se per ogni coppia di vertici non adiacenti \(u, v\) vale \(\deg(u) + \deg(v) \ge n\), allora il grafo è hamiltoniano.

Il problema di stabilire se un grafo è hamiltoniano è **NP-completo**, e non si conoscono algoritmi polinomiali generali.

#### Confronto tra grafi euleriani e hamiltoniani

| Caratteristica         | Euleriano                          | Hamiltoniano                          |
|------------------------|-------------------------------------|----------------------------------------|
| Oggetto attraversato   | Ogni **arco** una volta    | Ogni **vertice** una volta    |
| Caratterizzazione      | Grado pari di tutti i vertici | Nessuna caratterizzazione semplice |
| Complessità decisionale| Polinomiale                        | NP-completo                   |
| Problema tipico        | Postino cinese                     | Commesso viaggiatore                  |

Gli algoritmi per trovare cicli hamiltoniani sono spesso basati su backtracking o euristiche e hanno complessità esponenziale nel caso generale.
