/*Scrivi un programma in C che permetta di far scrivere un messaggio 
di lunghezza variabile all'utente.*/

#include <stdio.h>
#include <stdlib.h>

typedef char* String;

int main(){
    String frase = NULL;
    int cnt = 0;
    char c;
    c = getchar();
    while(c != '\n') {
        frase = (String) realloc(frase, (cnt + 2 ) * sizeof(char));
        if(frase == NULL){
            printf("Ahia ahia :(");
            return 1;
        }
        frase[cnt] = c;
        cnt++;
        
        c = getchar();
    }
    frase[cnt] = '\0';
    
    printf("%s", frase);
    free(frase);

    return 0;
}