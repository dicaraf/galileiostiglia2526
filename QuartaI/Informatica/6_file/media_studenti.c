/*Inserire dati studenti (nome, età, media voti) e determinare
studente con media più alta*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  Studente
{
    char nome[50];
    int eta;
    float media;
}Studente;

void scriveStudenti(char *nome_file, int n_studenti) {
    FILE *f = fopen(nome_file, "ab");
    if(f == NULL) {
        printf("Errore nell'aprire il file, MALE MALE :(");
        return;
    }
    for(int i = 0; i< n_studenti; i++) {
        Studente s;
        printf("Inserisci nome studente %d", i+1);
        scanf("%49s", s.nome);
        printf("Inserisci età studente %d", i+1);
        scanf("%d", &s.eta);
        printf("Inserisci media voti studente %d", i+1);
        scanf("%f", &s.media);
        getchar();
        fwrite(&s, sizeof(Studente), 1, f);
    }
    fclose(f);
    if(ferror(f)) {
        printf("Errore nella chiusura del file....\n");
    }
}

Studente* leggiStudenti(char *nome_file, Studente *array) {
    FILE* f = fopen(nome_file, "rb");
    if(f == NULL) {
        printf("Errore nell'aprire il file, MALE MALE :(");
        return array;
    }
    int i = 0;
    array = (Studente*) realloc(array, sizeof(Studente));
    if(array == NULL) {
        printf("Errore di allocazione\n");
        return array;
    }
    while(fread(&array[i], sizeof(Studente), 1, f) != 0) {
        i++;
        array = (Studente*) realloc(array, (i+1) * sizeof(Studente));
        if(array == NULL) {
            printf("Errore di allocazione\n");
            return array;
        }
    }
    array = (Studente*) realloc(array, i * sizeof(Studente));
    if(array == NULL) {
        printf("Errore di allocazione\n");
        return array;
    }
    fclose(f);
    if(ferror(f)) {
        printf("Errore nella chiusura del file....\n");
    }
    return array;
}

Studente trova_migliore(Studente *array) {
    int dim = sizeof(array) / sizeof(Studente);
    Studente best = {"", 0, 0};

    for(int i = 0; i < dim; i++) {
        if(array[i].media > best.media) {
            best.media = array[i].media;
            best.eta = array[i].eta;
            strcpy(best.nome, array[i].nome);
        }
    }
    return best;
}

int main() {
    //fatelo voi
}