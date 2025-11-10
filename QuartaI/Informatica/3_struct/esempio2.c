#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    char nome[10];
} Punto;

void modificaPunto(Punto *p) {
    p->x = 10;  // Modifica la struct originale tramite puntatore
    p->y = 20;
    strcpy(p->nome, "prova");
    printf("Punto dentro funzione: (%d, %d)\n", p->x, p->y);
    printf("%s\n\n", p->nome);
}

void stampaPunto(Punto p){
    p.x = 100;
    printf("%d", p.x);
}

int main() {
    Punto p1 = {5, 6, ""};
    printf("Punto prima di chiamata funzione: (%d, %d)\n", p1.x, p1.y); 
    printf("%s\n\n", p1.nome);
    modificaPunto(&p1);
    printf("Punto fuori funzione: (%d, %d)\n", p1.x, p1.y); // è cambiato (10,20)
    printf("%s\n\n", p1.nome);
    return 0;
}