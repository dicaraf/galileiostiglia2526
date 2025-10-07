#include <stdio.h>
#include <stdlib.h>
typedef char* String;
int main() {
    String str = NULL;   // puntatore alla stringa
    int size = 0;       // lunghezza corrente
    char c;

    printf("Inserisci una stringa (termina con invio):\n");

    while ((c = getchar()) != '\n' && c != EOF) {
        // aumento di 1 il buffer per il nuovo carattere
        str = realloc(str, (size + 2) * sizeof(char));
        if (str == NULL) {
            printf("Errore di allocazione\n");
            return 1;
        }

        str[size] = c;   // aggiungo il carattere
        size++;
        str[size] = '\0'; // aggiorno il terminatore
    }

    printf("Hai inserito: %s\n", str);

    free(str);
    return 0;
}
