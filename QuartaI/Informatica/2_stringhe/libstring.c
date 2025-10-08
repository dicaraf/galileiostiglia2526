#include "libstring.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * 
 */
stringa crea_stringa_dimensionata(int n){
    stringa c=(stringa)malloc(n*sizeof(char));
    if(c==NULL){
        printf("Errore");
        exit(1);
    }
    fgets(c, n, stdin);
    return c;
}
/**
 * 
 */
 int calcola_lunghezza_stringa(stringa c){
    int dim=0;
    while(c[dim]!='\0'){
        dim++;
    }
    return dim;
}