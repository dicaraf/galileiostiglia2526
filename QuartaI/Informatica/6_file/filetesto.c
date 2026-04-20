#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nome[50];
    float voto;
} Studente;

void salvaStudentiTesto(char *nomeFile, Studente studenti[], int n) {
    FILE *f = fopen(nomeFile, "w");
    if (f == NULL) {
        printf("Errore apertura file");
        return;
    }

    // Header: numero studenti
    fprintf(f, "%d\n", n);  // scrittura formattata su file

    // Un record per riga: id|nome|voto
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d|%s|%.1f\n", studenti[i].id, studenti[i].nome, studenti[i].voto);
    }

    fclose(f);
    printf("Salvati %d studenti (testo).\n", n);
}

int caricaStudentiTesto(char *nomeFile, Studente studenti[], int maxDim) {
    FILE *f = fopen(nomeFile, "r");
    if (f == NULL) {
        printf("Errore apertura file");
        return 0;
    }

    char line[256];
    int n = 0;
    
    if (fscanf(f, "%d", &n) != 1) {  
        fclose(f);
        return 0;
    }

    if (n > maxDim) {
        printf("Attenzione: il file contiene piu' studenti del previsto.\n");
        n = maxDim;
    }

    int letti = 0;
    Studente s;
    while (letti < n && fscanf(f, "%d|%49[^|]|%f", &s.id, s.nome, &s.voto) == 3) {
        studenti[letti++] = s;
    }

    fclose(f);
    return letti;
}

int leggiStudenteTesto(char *nomeFile, int indice, Studente *s) {
    FILE *f = fopen(nomeFile, "r");
    if (f == NULL) {
        printf("Errore apertura file");
        return 0;
    }

    char line[256];
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return 0;
    }

    // Salta fino alla riga "indice"
    for (int i = 0; i <= indice; i++) {
        if (fscanf(f, "%d|%49[^|]|%f", &s->id, s->nome, &s->voto) != 3) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

int modificaStudenteTesto(char *nomeFile, int indice, Studente *nuovo) {
    FILE *in = fopen(nomeFile, "r");
    if (in == NULL) {
        printf("Errore apertura file");
        return 0;
    }

    char *tmpName = "tmp_classe.txt";
    FILE *out = fopen(tmpName, "w");
    if (out == NULL) {
        printf("Errore apertura file temporaneo");
        fclose(in);
        return 0;
    }

    char line[256];

    // Copia header (n) così com'è
    if (!fgets(line, sizeof(line), in)) {
        fclose(in);
        fclose(out);
        remove(tmpName);
        return 0;
    }
    fputs(line, out);

    int current = 0;
    while (fgets(line, sizeof(line), in)) {
        if (current == indice) {
            fprintf(out, "%d|%s|%.1f\n", nuovo->id, nuovo->nome, nuovo->voto);
        } else {
            fputs(line, out);
        }
        current++;
    }

    fclose(in);
    fclose(out);

    // Sostituisce il file originale con il temporaneo
    remove(nomeFile);
    if (rename(tmpName, nomeFile) != 0) {
        printf("Errore rename");
        return 0;
    }
    return 1;
}

int main() {
    Studente classe[3] = {
        {1, "Mario Rossi", 28.5},
        {2, "Anna Verdi", 20.0},
        {3, "Luca Bianchi", 25.0}
    };

    salvaStudentiTesto("classe.txt", classe, 3);

    Studente s;
    if (leggiStudenteTesto("classe.txt", 1, &s)) {
        printf("Studente[1]: %s, voto: %.1f\n", s.nome, s.voto);
    }

    s.voto = 30.0;
    strcpy(s.nome, "Anna Verdi (lode)");
    modificaStudenteTesto("classe.txt", 1, &s);

    Studente caricati[10];
    int n = caricaStudentiTesto("classe.txt", caricati, 10);

    printf("\n--- Elenco completo ---\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %s | Voto: %.1f\n",
               caricati[i].id, caricati[i].nome, caricati[i].voto);
    }

    return 0;
}
