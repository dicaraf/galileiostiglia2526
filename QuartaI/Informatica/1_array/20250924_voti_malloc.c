/*Scrivi un programma che memorizzi i voti di uno studente.*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    float *voti = NULL;
    int num = 0;
    
    printf("quanti voti vuoi aggiungere?");
    scanf("%d", &num);
    voti = (float*) malloc(num * sizeof(float));
    if(voti == NULL){
        printf("errore di allocazione memoria!!!!!!! :((()");
        return 1;
    }
    for(int i = 0; i < num; i++){
        printf("Inserisci il voto %d", i+1);
        scanf("%f", &voti[i]);
    }
    voti = (float*)realloc(voti, (num+1)*sizeof(float));
    if(voti == NULL){
        printf("errore di allocazione memoria!!!!!!! :((()");
        return 1;
    }
    num++;
    printf("Inserisci il voto %d", num);
    scanf("%f", &voti[num-1]);

    free(voti);
    voti = NULL;
}









