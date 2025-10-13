#include "libstring.h"
#include <stdio.h>
#include <stdlib.h>

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

Stringa crea_stringa_dimensionata(int n){
    Stringa c = (Stringa) malloc(n * sizeof(char));
    if(c == NULL){
        printf("Errore di allocazione!\n");
        exit(1);
    }
    fgets(c, n, stdin);
    clear_buffer();
    return c;
}

Stringa crea_stringa_dinamica(char terminator){
    Stringa str = NULL;
    int size = 0;       // lunghezza corrente della stringa
    int capacity = 0;   // spazio totale allocato
    char c;

    printf("Inserisci una stringa (termina con %c):\n", terminator);

    while ((c = getchar()) != terminator && c != EOF) {  // finchè l'utente non inserisce il carattere terminatore o non si raggiunge la fine di un file
        if (size + 1 >= capacity) {
            capacity += 10; // rialloco a blocchi di 10
            str = (Stringa) realloc(str, capacity * sizeof(char));
            if (str == NULL) {
                printf("Errore di allocazione\n");
                exit(1);
            }
        }
        str[size++] = c;
    }
    str[size] = '\0'; // aggiungo terminatore della stringa

    return str;
}

int calcola_lunghezza_stringa(Stringa s){
    int dim=0;
    while(s[dim]!='\0') dim++;
    
    return dim;
}

Stringa concatena_stringhe(Stringa s1, Stringa s2, char separatore){
    int dim1 = calcola_lunghezza_stringa(s1);
    int dim2 = calcola_lunghezza_stringa(s2);
    int dim3 = dim1 + dim2 + 2;
    Stringa s3 = (Stringa)malloc(dim3 * sizeof(char));
    if(s3 == NULL) {
        printf("Errore di allocazione \n");
        exit(1);
    }
    int i = 0;
    for(i = 0; i < dim1; i++){
      s3[i] = s1[i];  
    }
    s3[i] = separatore;

    for(int j = 0; j < dim2; j++){
        i++;
        s3[i] = s2[j];
        
    }
    s3[++i] = '\0';
    return s3;
}
int conta_occorrenze(Stringa s1, char carattere){
    int dim = 0;
    int cnt_carattere = 0;
    while(s1[dim] != '\0'){
        if(s1[dim] == carattere)
            cnt_carattere++;
        dim++;
    }
    return cnt_carattere;

}
int stringa_in_stringa(Stringa s1, Stringa s2){
    int dim1 = calcola_lunghezza_stringa(s1);
    int dim2 = calcola_lunghezza_stringa(s2);
    int flag = 0;
    int cnt = 0;

    for(int i = 0; i <= dim1-dim2+1; i++){
        if(s1[i] == s2[0]){
            flag = 1;
            for(int j = 1; j < dim2; j++){
                if(s1[i+j] != s2[j]){
                flag = 0;
                break;
                }
            }
            cnt += flag;
        }
    }
    return cnt;
}