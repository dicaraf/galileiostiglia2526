#include <stdlib.h>
#include <stdio.h>

struct Persona {
    char nome[50];
    int eta;
    float stipendio;
};

int main() {
    // Dichiarazione di un puntatore a struct
    struct Persona *p1;
    
    // Allocazione di memoria per una struct
    p1 = (struct Persona*)malloc(sizeof(struct Persona));
    
    // Controllo se l'allocazione ha avuto successo
    if (p1 == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Assegnamento dei valori
    p1->eta = 30;
    p1->stipendio = 2500.50;
    
    printf("Età: %d, stipendio: %f\n\n", p1->eta, p1->stipendio);
    // Liberazione della memoria quando non più necessaria
    free(p1);
    
    return 0;
}
