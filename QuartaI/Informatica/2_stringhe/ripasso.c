/*Scrivi un programma in C che chieda nome e cognome all'utente. 
Se il cognome dell'utente è "Miotto" allora si assegna allo studente
una nota che dice che lo studente parla troppo.
Se il nome dello studente inizia con "Prais" allora si assegna
una nota che dice che lo studente è troppo bello.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* inserisci_stringa(char *s){
    int scelta;
    char c;
    char seconda_parte[10];
    s = (char*) malloc(20 * sizeof(char));
    printf("Inserisci la tua stringa di 20 caratteri: ");
    fgets(s, 20, stdin); //include sia \n che \0
    //carmelo gianni piero\n\0
    printf("Ti sono bastati 20 caratteri per la stringa? 1 per no");
    scanf("%d", &scelta);
    while((c = getchar()) != '\n') {}
    if(scelta == 1) {
        int len = strlen(s);
        s[len - 1] = '\0'; //cancello il \n
        s = (char*) realloc(s, 30 * sizeof(char));
        fgets(seconda_parte, 10, stdin);
        strcat(s, seconda_parte);
    }
    return s;
}

int main(){
    char *annotazione;
    char *nome;
    char *cognome;
    char frase[] = " è troppo bello!\n";

    nome = inserisci_stringa(nome);
    cognome = inserisci_stringa(cognome);

    if(strstr(nome, "Prais") != NULL){
        printf("Prais è contenuto in nome\n");
        annotazione = (char*)malloc(50 * sizeof(char));
        strcpy(annotazione, nome);
        strcat(annotazione, frase);
    }
}