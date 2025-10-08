#include <stdio.h>
#include <stdlib.h>

typedef char* String;

int main() {
    String str = NULL;
    int size = 0;       // lunghezza corrente
    int capacity = 0;   // spazio allocato
    char c;

    printf("Inserisci una stringa (termina con invio):\n");

    while ((c = getchar()) != '\n' && c != EOF) {
        if (size + 1 >= capacity) {
            capacity += 10; // rialloco a blocchi di 10
            str = (String) realloc(str, capacity * sizeof(char));
            if (str == NULL) {
                printf("Errore di allocazione\n");
                return 1;
            }
        }
        str[size++] = c;
    }
    str[size] = '\0'; // aggiungo terminatore

    printf("Hai inserito: %s\n", str);

    free(str);
    return 0;
}
