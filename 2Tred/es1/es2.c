#include <stdio.h>

int main(){
    char carattere;

    printf("Inserisci un carattere: ");
    scanf("%c", &carattere);

    if((carattere >= 'a' && carattere <= 'z') || (carattere >= 'A' && carattere <= 'Z')) {
        printf("Il carattere è una lettera\n");
        if(carattere == 'a' || carattere == 'e' || carattere == 'i' || carattere == 'o' || carattere == 'u') {
            printf("il carattere è una vocale\n");
        } else {
            printf("il carattere è una consonante\n");
        }
    } else {
        if(carattere >= '0' && carattere <= '9') {
            printf("il carattere è una cifra\n");
        } else {
            printf("è un carattere speciale\n");
        }
    }
}