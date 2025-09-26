/*scrivi un programma che chieda all'utente un numero di studenti 
e per ogni studenti un numero di voti*/

#include <stdio.h>
#include <stdlib.h>

void alloca_righe(float** matrice, int num_righe){
    matrice = realloc(matrice, num_righe * sizeof(float*));
    if(matrice == NULL) {
        printf("Errore allocazione numero righe");
        exit(1);
    }
}

void alloca_riga(float *arr, int num_elementi){
    arr = realloc(arr, num_elementi * sizeof(float));
    if(arr == NULL) {
        printf("Errore allocazione singola riga");
        exit(1);
    }
}

int main(){
    float **mat=NULL;
    int numero_voti=0;
    int righe_studenti=0;
    printf("quanti studenti devi valutare?");
    scanf("%d", &righe_studenti);
    mat=(float**)malloc(righe_studenti * sizeof(float*));

    for(int i=0; i<righe_studenti; i++){

        printf("quanti voti ha lo studente? ");
        scanf("%d",&numero_voti);
        mat[i]=(float*)malloc(numero_voti* sizeof(float));

        for(int j=0; j<numero_voti; j++){
            printf("inserisci il voto dello studente: ");
            scanf("%f",&mat[i][j]);
            printf("%f", mat[i][j]);
        }
    }
    mat=(float**)realloc(mat,(righe_studenti+1) * sizeof(float*));
    mat[righe_studenti]=malloc(5 * sizeof(float));

    for(int i=0; i<=righe_studenti; i++){
        free(mat[i]);
    }
    free(mat);
}