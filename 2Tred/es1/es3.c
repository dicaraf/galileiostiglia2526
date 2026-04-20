#include <stdio.h>

int main() {

    char utente;
    int PIN;
    printf("Inserisci il tuo ruolo:");
    scanf("%c", &utente);
    printf("Inserisci PIN: ");
    scanf("%d", &PIN);

    if(utente == 'A' || utente == 'U' || utente == 'G') {
        if(utente == 'A' && PIN % 2 == 0 && PIN >= 0 && PIN <= 9999){
            printf("Accesso garantito");
        } else {
            if(utente == 'U' && PIN >= 1000 && PIN <= 5000) {
                printf("Accesso garantito");
            } else {
                if(utente == 'G' && PIN == 0){
                    printf("Accesso garantito");
                } else {
                    printf("ACCESSO Negato");
                }
            }
        }
    } else {
        printf("Tipo utente non valido\n");
    }
}