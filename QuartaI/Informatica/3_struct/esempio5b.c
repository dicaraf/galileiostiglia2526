#include <stdlib.h>
#include <stdio.h>

typedef struct  {
    char nome[50];
    int eta;
    float stipendio;
}Persona;
struct Alunno {
    char nome[30];
    char sezione;
    int classe;
};
int main() {
    struct Alunno a1 = {"Mohamed"};
    printf("%s", a1.nome);
    scanf("%c", &a1.sezione);

    struct Alunno *a2;
    // Dichiarazione di un puntatore a struct
    Persona *p1;
    a2 = (struct Alunno*)malloc(sizeof(struct Alunno));
    // Allocazione di memoria per una struct
    //p1 = (Persona*)malloc(sizeof(Persona)); //alternativa
    p1 = malloc(sizeof(*p1));
    
    // Controllo se l'allocazione ha avuto successo
    if (p1 == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Assegnamento dei valori
    p1->eta = 30;
    (*p1).eta = 10;
    p1->stipendio = 2500.50;
    
    printf("Età: %d, stipendio: %f\n\n", p1->eta, p1->stipendio);
    // Liberazione della memoria quando non più necessaria
    free(p1);
    
    return 0;
}
