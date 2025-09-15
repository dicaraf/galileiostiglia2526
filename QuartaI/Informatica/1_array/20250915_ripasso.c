#include <stdio.h>
#define DIM 5

int main(){
    int array[]={1,2,3,4,5};
    int mat[3][4]={{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};

    for(int i=0; i<DIM; i++){
        printf("inserisci valore: ");
        scanf("%d", &array[i]);
    }
    for(int i=0; i<DIM; i++){
        printf("%d", array[i]);
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}