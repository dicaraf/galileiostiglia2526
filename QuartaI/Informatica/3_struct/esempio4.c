#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;
typedef struct {
    int giorno;
    int mese;
    int anno;
} data;

typedef struct {
    String nome;
    String cognome;
    int classe;
    char sezione;
    float voto;
    data data_voto;
} interrogazione;

int main(){
    interrogazione interroga;
    char c;
    scanf("%d %d %d", &interroga.data_voto.giorno, &interroga.data_voto.mese, &interroga.data_voto.anno);
    while((c = getchar()) != '\n'){}
    interroga.nome = (String) malloc(20 * sizeof(char));
    fgets(interroga.nome, 20, stdin);

    printf("%s, giorno %d/%d/%d\n\n", interroga.nome, interroga.data_voto.giorno, interroga.data_voto.mese, interroga.data_voto.anno);
}