#include <stdio.h>
#include <string.h>

typedef struct {
    char cognome[30];
    char *nome;
    int voto;
} alunno;

int main() {
    alunno a1 = {"Lonighi"};
    strcpy(a1.cognome, "Rossi");
    fgets(a1.cognome, 10, stdin);
    a1.nome = (char*)malloc(20 * sizeof(char));
    strcpy(a1.nome, "Mario");
    a1.voto = 28;
    printf("Alunno: %s %s, voto: %d\n", a1.cognome, a1.nome, a1.voto);
    free(a1.nome);
    return 0;
}