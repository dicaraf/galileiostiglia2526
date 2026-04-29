/*Crea una funzione di tipo bool che dice se il contenuto del
vettore è in ordine crescente.*/

#include <stdio.h>
#include <stdbool.h>

#define DIM 5

bool is_sorted(int dim, int vett[]){
    for(int i = 0; i < dim - 1; i++) {
        if(vett[i] < vett[i+1]) return false;
    }
    return true;
}

bool all_different(int dim, int vett[]){
    for(int i = 0; i < dim - 1; i++){
        for(int j = i + 1; j < dim; j++){
            if(vett[i] == vett[j]) return false;
        }
    }
    return true;
}

int main() {
    int vettore[DIM] = {0};
    printf("Inserisci valori: ");
    for(int i = 0; i< DIM; i++) {
        scanf("%d", &vettore[i]);
    }
    if(is_sorted(DIM, vettore)){
        printf("è ordinatooooooooooooooooooooooo\n");
    } else {
        printf("NON è ordinatooooooooooooooooooooooo\n");
    }
    return 0;
}