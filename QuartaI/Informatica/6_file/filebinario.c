#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float voto;
} Studente;

void salvaStudenti(char *nomeFile, Studente studenti[], int n) {
    FILE *f = fopen(nomeFile, "wb");
    if ( f == NULL) {
        printf("Errore apertura file");
        return;
    }
    
    // scrive prima il numero di studenti
    fwrite(&n, sizeof(int), 1, f);
    
    // scrive l'intero array
    fwrite(studenti, sizeof(Studente), n, f);
    
    fclose(f);
    printf("Salvati %d studenti.\n", n);
}

int caricaStudenti(char *nomeFile, Studente studenti[], int maxDim) {
    FILE *f = fopen(nomeFile, "rb");
    if ( f == NULL) {
        printf("Errore apertura file");
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

int leggiStudente(char *nomeFile, int indice, Studente *s) {
    FILE *f = fopen(nomeFile, "rb");
    if ( f == NULL) {
        printf("Errore apertura file");
        return 0;
    }
    
    // salta l'header (numero studenti) + i record precedenti
    long offset = sizeof(int) + indice * sizeof(Studente);
    
    if (fseek(f, offset, SEEK_SET) != 0) {
        printf("Errore fseek");
        fclose(f);
        return 0;
    }
    
    int letti = fread(s, sizeof(Studente), 1, f);
    fclose(f);
    
    return (letti == 1);
}

int modificaStudente(char *nomeFile, int indice, Studente *s) {
    FILE *f = fopen(nomeFile, "r+b");
    if ( f == NULL) {
        printf("Errore apertura file");
        return 0;
    }
    
    long offset = sizeof(int) + indice * sizeof(Studente);
    
    if (fseek(f, offset, SEEK_SET) != 0) {
        printf("Errore fseek");
        fclose(f);
        return 0;
    }
    
    int scritti = fwrite(s, sizeof(Studente), 1, f);
    fclose(f);
    
    return (scritti == 1);
}

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
    strcpy(s.nome, "Anna Verdi (lode)");
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