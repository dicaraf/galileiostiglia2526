#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ---- Definizione struct necessarie ---- */
typedef struct Canzone {
    int id;
    char titolo[50];
    char artista[50];
    int durata;
    struct Canzone* next;
    struct Canzone* next_playlist;
} Canzone;

typedef struct Lista {
    Canzone* testa;
    int lunghezza;
} Lista;

/* ---- Variabile globale per gestire l'id univoco delle canzoni ---- */
int id_univoco = 0;

/* ---- Funzioni lista di canzoni disponibili ---- */
void stampa_canzone(Canzone *c);
void set_canzone(Canzone *c);
Lista* crea_lista();
void stampa_lista(Lista *l);
void inserisci_canzone_lista(Lista *l);
void ricerca_canzone_artista(Lista *l, char* artista);
void libera_memoria(Lista* l);

/* ---- Funzioni playlist (lista circolare) ---- */
void inserisci_canzone_playlist(Lista *lista_canzoni, Lista *playlist);
void stampa_playlist(Lista* playlist);
void cancella_canzone_playlist(Lista *playlist);

/* ---- MAIN ---- */

int main() {
    Lista* lista_canzoni = crea_lista();
    Lista* playlist = crea_lista();

    int scelta;
    char artista[50];

    do {
        printf("\n===== SPOTIFY 0.0.0.1 =====\n");
        printf("1. Inserisci nuova canzone nella lista\n");
        printf("2. Stampa lista canzoni\n");
        printf("3. Cerca canzoni per artista\n");
        printf("4. Aggiungi canzone alla playlist\n");
        printf("5. Stampa playlist\n");
        printf("6. Cancella canzone dalla playlist\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar(); // pulisci buffer input

        switch (scelta) {
            case 1:
                inserisci_canzone_lista(lista_canzoni);
                break;
            case 2:
                stampa_lista(lista_canzoni);
                break;
            case 3:
                printf("Inserisci artista da cercare: ");
                fgets(artista, 50, stdin);
                ricerca_canzone_artista(lista_canzoni, artista);
                break;
            case 4:
                inserisci_canzone_playlist(lista_canzoni, playlist);
                break;
            case 5:
                stampa_playlist(playlist);
                break;
            case 6:
                cancella_canzone_playlist(playlist);
                break;
            case 0:
                printf("Uscita...\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
        }

    } while (scelta != 0);

    libera_memoria(lista_canzoni);
    libera_memoria(playlist);
    return 0;
}

/* =======================================================================================
   Qui sotto vanno implementate le funzioni.
======================================================================================= */

void stampa_canzone(Canzone *c) {
    printf("%s di %s - %d secondi\n", c->titolo, c->artista, c->durata);
}

void set_canzone(Canzone *c) {
    id_univoco++;
    c->id = id_univoco;
    printf("---- Inserimento canzone con id %d ----\n", c->id);
    printf("Inserisci titolo canzone: ");
    fgets(c->titolo, 40, stdin);
    printf("Inserisci artista canzone: ");
    fgets(c->artista, 40, stdin);
    printf("Inserisci durata canzone: ");
    scanf("%d", &c->durata);
    getchar();
}

Lista* crea_lista() {
    Lista *l=(Lista*)malloc(sizeof(Lista));
    l->lunghezza=0;
    l->testa=NULL;
    return l;
}

void stampa_lista(Lista *l) {
    Canzone* temp=l->testa;
    int i=0;
    while(temp!=NULL){
        stampa_canzone(temp);
        temp=temp->next;
    }
}

void inserisci_canzone_lista(Lista *l) {
    Canzone* c = (Canzone*)malloc(sizeof(Canzone));
    set_canzone(c);
    c->next = l->testa;
    l->testa = c;
    l->lunghezza++;
}

void ricerca_canzone_artista(Lista *l, char* artista) {
    Canzone* temp = l->testa;
    int trovata = 0;
    printf("Ricerca canzoni dell'artista %s.......\n", artista);
    while (temp != NULL) {
        if (strcmp(temp->artista, artista) == 0) {
            stampa_canzone(temp);
            trovata = 1;
        }
        temp = temp->next;
    }
    if(trovata == 0) 
        printf("Non è stata trovata nessuna canzone per l'artista selezionato\n");
}

void libera_memoria(Lista* l) {
    Canzone* temp = l->testa;
    while (temp != NULL) {
        Canzone* l = temp;
        temp = temp->next;
        free(temp);
    }
    free(l);
}

void inserisci_canzone_playlist(Lista *lista, Lista *playlist) {
    Canzone* temp = lista->testa;
    int id;
    printf("Inserisci id della canzone che vuoi aggiungere ala lista: ");
    scanf("%d", &id);
    getchar();
    while (temp != NULL) {
        if (temp->id == id) {
            break;
        }
        temp = temp->next;
    }
    if(temp == NULL) {
        printf("Canzone non trovata!!!\n");
        return;
    }
    if (playlist->testa == NULL) {
        playlist->testa = temp;
        temp->next_playlist = temp;  // Punta a se stesso
    } else {
        Canzone* current = lista->testa;
        while (current->next_playlist != playlist->testa) {
            current = current->next_playlist;
        }
        temp->next_playlist = playlist->testa;
        current->next_playlist = temp;
    }
    playlist->lunghezza++;
}

void stampa_playlist(Lista* playlist) {
    Canzone* temp=playlist->testa;
    for (int i = 0; i < playlist->lunghezza; i++) {
        stampa_canzone(temp);
        temp = temp->next;
    }

}

void cancella_canzone_playlist(Lista *playlist) {
    int id;
    printf("Inserisci id della canzone che vuoi eliminare dalla playlist: ");
    scanf("%d", &id);
    getchar();

    if (playlist->testa == NULL) return;
    
    // Se l'elemento è in testa
    if (playlist->testa->id == id) {
        if (playlist->lunghezza == 1) {
            free(playlist->testa);
            playlist->testa = NULL;
        } else {
            Canzone* current = playlist->testa;
            while (current->next != playlist->testa) {
                current = current->next;
            }
            Canzone* temp = playlist->testa;
            playlist->testa = playlist->testa->next;
            current->next = playlist->testa;
            free(temp);
        }
        playlist->lunghezza--;
        return;
    }
    
    // Ricerca nella lista
    Canzone* current = playlist->testa;
    for (int i = 0; i < playlist->lunghezza; i++) {
        if (current->next->id == id) {
            Canzone* temp = current->next;
            current->next = current->next->next;
            free(temp);
            playlist->lunghezza--;
            return;
        }
        current = current->next;
    }
    printf("Canzone non trovata e non eliminata!\n");
}

