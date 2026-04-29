/*Scrivi un programa in C che chieda all'utente i 10 voti
che ha preso in informatica da quando la studia. 
Quindi mostra quante volte ha preso 6, 7, 8, 9 e 10.*/

#include <stdio.h>

int main() {
    int voti[10], conta[5] = {0};

    for(int i = 0; i < 10; i++) {
        printf("Inserisci il voto %d: ", i+1);
        scanf("%d", &voti[i]);
    }

    for(int i = 0; i < 10; i++) {
        if(voti[i]>=6 && voti[i]<=10) {
            conta[voti[i]-6]++;
        }
    }
    for(int i = 0; i < 5; i++) {
        printf("Ho trovato %d volte il voto %d\n", conta[i], i+6);
    }
    return 0;
}