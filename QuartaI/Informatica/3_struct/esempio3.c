#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    char cognome[30];
    char nome[20];
    int voto;
} alunno;

int main() {
    alunno a[MAX];
    int n, i, trovato;
    char cerca[20];

    // inserimento numero di alunni
    do {
        printf("Inserisci il numero di alunni: ");
        scanf("%d", &n);
    } while (n < 1 || n > MAX);

    // inserimento dati alunni
    for (i = 0; i < n; i++) {
        printf("Cognome: ");
        scanf("%s", a[i].cognome);
        printf("Nome: ");
        scanf("%s", a[i].nome);
        printf("Voto: ");
        scanf("%d", &a[i].voto);
    }

    // ricerca alunno
    printf("Inserisci cognome da cercare: ");
    scanf("%s", cerca);
    trovato = 0;
    for (i = 0; i < n; i++) {
        if (strcmp(a[i].cognome, cerca) == 0) {
            printf("Alunno trovato: %s %s, voto %d\n", a[i].nome, a[i].cognome, a[i].voto);
            trovato = 1;
            break;
        }
    }
    if (!trovato) {
        printf("Alunno non trovato.\n");
    }

    return 0;
}

