#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Studente {
    char nome[50];
    int eta;
    float media;
} Studente;

void scriveStudenti(char *nome_file, int n_studenti) {
    FILE *f = fopen(nome_file, "ab");
    if (f == NULL) {
        printf("Errore nell'aprire il file.\n");
        return;
    }

    for (int i = 0; i < n_studenti; i++) {
        Studente s;
        printf("Inserisci nome studente %d: ", i + 1);
        scanf("%49s", s.nome);
        printf("Inserisci eta' studente %d: ", i + 1);
        scanf("%d", &s.eta);
        printf("Inserisci media voti studente %d: ", i + 1);
        scanf("%f", &s.media);
        getchar();

        if (fwrite(&s, sizeof(Studente), 1, f) != 1) {
            printf("Errore nella scrittura del file.\n");
        }
    }

    if (ferror(f)) {
        printf("Errore durante la scrittura del file.\n");
    }
    if(fclose(f) != 0) {
        printf("Errore chiusura file!\n");
    }
}

Studente *leggiStudenti(char *nome_file, int *n) {
    *n = 0;
    FILE *f = fopen(nome_file, "rb");
    if (f == NULL) {
        printf("Errore nell'aprire il file.\n");
        return NULL;
    }

    Studente *array = NULL;
    Studente temp;

    while (fread(&temp, sizeof(Studente), 1, f) == 1) {
        Studente *nuovo = realloc(array, (*n + 1) * sizeof(Studente));
        if (nuovo == NULL) {
            printf("Errore di allocazione.\n");
            free(array);
            fclose(f);
            return NULL;
        }
        array = nuovo;
        array[*n] = temp;
        (*n)++;
    }

    if (ferror(f)) {
        printf("Errore durante la lettura del file.\n");
    }
    if(fclose(f) != 0) {
        printf("Errore chiusura file!\n");
    }

    return array;
}

Studente trovaMigliore(Studente *array, int dim) {
    Studente best = {"", 0, -1.0f};

    for (int i = 0; i < dim; i++) {
        if (array[i].media > best.media) {
            best = array[i];
        }
    }
    return best;
}

int main(void) {
    char nome_file[] = "studenti.bin";
    int scelta;

    do {
        printf("\n===== MENU' =====\n");
        printf("1. Inserisci studenti\n");
        printf("2. Visualizza tutti gli studenti\n");
        printf("3. Trova lo studente con la media piu' alta\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar();

        switch (scelta) {
            case 1: {
                int n;
                printf("Quanti studenti vuoi inserire? ");
                scanf("%d", &n);
                getchar();
                scriveStudenti(nome_file, n);
                printf("Studenti salvati correttamente.\n");
                break;
            }

            case 2: {
                int n;
                Studente *array = leggiStudenti(nome_file, &n);
                if (array == NULL || n == 0) {
                    printf("Nessuno studente trovato nel file.\n");
                } else {
                    printf("\n--- Lista studenti (%d) ---\n", n);
                    for (int i = 0; i < n; i++) {
                        printf("[%d] Nome: %-20s | Eta': %3d | Media: %.2f\n",
                               i + 1, array[i].nome, array[i].eta, array[i].media);
                    }
                    free(array);
                }
                break;
            }

            case 3: {
                int n;
                Studente *array = leggiStudenti(nome_file, &n);
                if (array == NULL || n == 0) {
                    printf("Nessuno studente trovato nel file.\n");
                } else {
                    Studente best = trovaMigliore(array, n);
                    printf("\n--- Studente con media piu' alta ---\n");
                    printf("Nome: %s | Eta': %d | Media: %.2f\n",
                           best.nome, best.eta, best.media);
                    free(array);
                }
                break;
            }

            case 0:
                printf("Arrivederci!\n");
                break;

            default:
                printf("Scelta non valida.\n");
        }
    } while (scelta != 0);

    return 0;
}