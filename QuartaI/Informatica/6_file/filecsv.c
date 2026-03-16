#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nome[50];
    float voto;
} Studente;

void salvaStudentiCSV(char *nomeFile, Studente studenti[], int n) {
    FILE *f = fopen(nomeFile, "w");
    if (f == NULL) {
        printf("Errore apertura file");
        return;
    }

    // Riga di intestazione CSV
    fprintf(f, "id,nome,voto\n");

    // Un record per riga: id,nome,voto
    for (int i = 0; i < n; i++) {
        // Se il nome potesse contenere virgole, andrebbe messo tra doppi apici
        fprintf(f, "%d,%s,%.1f\n", studenti[i].id, studenti[i].nome, studenti[i].voto);
    }

    fclose(f);
    printf("Salvati %d studenti (CSV).\n", n);
}

int caricaStudentiCSV(char *nomeFile, Studente studenti[], int maxDim) {
    FILE *f = fopen(nomeFile, "r");
    if (f == NULL) {
        printf("Errore apertura file");
        return 0;
    }

    char line[256];

    // Salta header CSV
    if (fgets(line, sizeof(line), f) == NULL) {
        fclose(f);
        return 0;
    }

    int letti = 0;
    Studente s;
    while (letti < maxDim && fscanf(f, "%d,%49[^,],%f", &s.id, s.nome, &s.voto) == 3) {
        //studenti = (Studente*)realloc(studenti, (letti+1)*sizeof(Studente));
        studenti[letti++] = s;
    }

    fclose(f);
    return letti;
}

int leggiStudenteCSV(char *nomeFile, int indice, Studente *s) {
    FILE *f = fopen(nomeFile, "r");
    if (f == NULL) {
        printf("Errore apertura file");
        return 0;
    }

    char line[256];

    // Salta header
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return 0;
    }

    // Salta fino alla riga "indice"
    for (int i = 0; i <= indice; i++) {
        if (fscanf(f, "%d,%49[^,],%f", &s->id, s->nome, &s->voto) != 3) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

int modificaStudenteCSV(char *nomeFile, int indice, Studente *nuovo) {
    FILE *in = fopen(nomeFile, "r");
    if (in == NULL) {
        printf("Errore apertura file");
        return 0;
    }

    char *tmpName = "tmp_classe.csv";
    FILE *out = fopen(tmpName, "w");
    if (out == NULL) {
        printf("Errore apertura file temporaneo");
        fclose(in);
        return 0;
    }

    char line[256];

    // Copia header così com'è
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
            // Scrive la nuova riga CSV
            fprintf(out, "%d,%s,%.1f\n", nuovo->id, nuovo->nome, nuovo->voto);
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

    salvaStudentiCSV("classe.csv", classe, 3);

    Studente s;
    if (leggiStudenteCSV("classe.csv", 1, &s)) {
        printf("Studente[1]: %s, voto: %.1f\n", s.nome, s.voto);
    }

    s.voto = 30.0;
    strcpy(s.nome, "Anna Verdi (lode)");
    modificaStudenteCSV("classe.csv", 1, &s);

    Studente caricati[10];
    int n = caricaStudentiCSV("classe.csv", caricati, 10);

    printf("\n--- Elenco completo ---\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %s | Voto: %.1f\n",
               caricati[i].id, caricati[i].nome, caricati[i].voto);
    }

    return 0;
}
