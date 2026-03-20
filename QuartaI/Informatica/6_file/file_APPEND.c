#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione per scrivere in append
void scriviAppend(const char *nomeFile) {
    FILE *fp = fopen(nomeFile, "a");

    if (fp == NULL) {
        printf("Errore apertura file\n");
        return;
    }

    char buffer[100];

    printf("Inserisci testo (scrivi 'FINE' per terminare):\n");

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);

        // rimuove newline
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "FINE") == 0) {
            break;
        }

        strcat(buffer, "\n"); // riaggiungo newline per il file
        fputs(buffer, fp);
    }

    fclose(fp);
    printf("Scrittura completata.\n");
}

// Funzione per leggere il file
void leggiFile(const char *nomeFile) {
    FILE *fp = fopen(nomeFile, "r");

    if (fp == NULL) {
        printf("Errore apertura file\n");
        return;
    }

    char buffer[100];

    printf("\nContenuto del file:\n");

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
}

int main() {
    char nomeFile[100];
    int scelta;

    printf("Inserisci il nome del file: ");
    scanf("%99s", nomeFile);
    getchar(); // pulisce il newline lasciato da scanf

    do {
        printf("\n--- MENU ---\n");
        printf("1. Scrivi nel file (append)\n");
        printf("2. Leggi il file\n");
        printf("3. Esci\n");
        printf("Scelta: ");

        scanf("%d", &scelta);
        getchar(); // pulisce il newline lasciato da scanf

        switch (scelta) {
            case 1:
                scriviAppend(nomeFile);
                break;
            case 2:
                leggiFile(nomeFile);
                break;
            case 3:
                printf("Uscita...\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }

    } while (scelta != 3);

    return 0;
}