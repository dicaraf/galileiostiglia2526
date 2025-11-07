#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

String inserisci_nome(){
    String s = NULL;
    int l = 0;
    char c;
    while ((c = getchar()) != '\n'){
        s = (String) realloc(s, (l + 2) * sizeof(char));
        if(s == NULL) {
            printf("Errore di allocazione!\n");
            exit(1);
        }
        if(c >= 'A' && c <= 'Z') {
            s[l++] = c;
        } else if(c >= 'a' && c <= 'z'){
            s[l++] = c - 32;
        }
        else {
            printf("\nHai inserito una lettera non valida!\n");
        }
        s[l] = '\0';
    }
    return s;
}

String inserisci_data(char sesso){
    String data = (String) malloc(9); 
    if(data == NULL) {
            printf("Errore di allocazione!\n");
            exit(1);
    }
    strcpy(data, "GG/MM/AA");
    int giorno, mese, anno;
    do{
        printf("Inserisci giorno di nascita: ");
        scanf("%d", &giorno);
    }while(giorno < 1 || giorno > 31);
    if(sesso == 'F') giorno += 40;
    data[0] = giorno / 10 + 48;
    data[1] = giorno % 10 + 48;
    printf("\nData attuale: %s\n", data);
    do{
        printf("Inserisci mese di nascita: ");
        scanf("%d", &mese);
    }while(mese < 1 || mese > 12);
    data[3] = mese / 10 + 48;
    data[4] = mese % 10 + 48;
    printf("\nData attuale: %s\n", data);
    do{
        printf("Inserisci anno di nascita: ");
        scanf("%d", &anno);
    }while(anno < 1900 || anno > 2025);
    data[6] = (anno / 10) % 10 + 48;
    data[7] = anno % 10 + 48;
    printf("\nData attuale: %s\n", data);
    return data;
}

String get_cgn(String s, int is_nome){
    int i = 0, j = 0, cnt = 0;
    String letters = (String) malloc(4 * sizeof(char));
    if(letters == NULL) {
        printf("Errore di allocazione!\n");
        exit(1);
    }
    letters[3] = '\0';
    while(s[i] != '\0' && j < 3) {
        if(s[i] != 'A' && s[i] != 'E' && s[i] != 'I' && s[i] != 'O' && s[i] != 'U' ) {
            letters[j++] = s[i];
            cnt++;
            if(is_nome == 1 && cnt == 2) j--;
        }
        i++;
    }
    i = 0;
    while(s[i] != '\0' && j < 3) {
        if(s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U' ) {
            letters[j++] = s[i];
        }
        i++;
    }
    return letters;
    
}

char get_month(int mese) {
    switch(mese){
        case 1:
            return 'A';
        case 2:
            return 'B';
        case 3:
            return 'C';
        case 4:
            return 'D';
        case 5:
            return 'E';
        case 6:
            return 'H';
        case 7:
            return 'L';
        case 8:
            return 'M';
        case 9:
            return 'P';
        case 10:
            return 'R';
        case 11:
            return 'S';
        case 12:
            return 'T';
        default:
            printf("Qualcosa è andato storto...");
            return 'X';
    }
}

char lettera_controllo(String cf){
    char lettere_dispari[] = "BAKPLCQDREVOSFTGUHMINJWZYX";
    int numeri_dispari[] = {1,0,5,7,9,13,15,17,19,21};
    int somma = 0;
    for(int i = 0; i < 16; i++) {
        if(i%2 == 0){
            if(cf[i]>='0' && cf[i]<='9'){
                somma += numeri_dispari[cf[i]];
            } else {
                int k = 0;
                while(lettere_dispari[k++] != cf[i]) somma++;
            }
        }else {
            if(cf[i]>='0' && cf[i]<='9'){
                somma += cf[i] - 48;
            } else {
                somma += cf[i] - 65;
            }
        }
    }
    return somma % 26 + 65;
}


int main(){
    String nome, cognome, data;
    char cf[17] = "";
    char sesso;

    printf("Inserisci il nome tutto in maiuscolo: ");
    nome = inserisci_nome();
    printf("Inserisci il cognome tutto in maiuscolo: ");
    cognome = inserisci_nome();
    printf("Inserisci il tuo sesso in maiuscolo: ");
    do {
        scanf("%c", &sesso);
        if(sesso != 'M' && sesso != 'F') {
            printf("\nInserimento errato, M o F in maiuscolo!\n");
        }
    }while(sesso != 'M' && sesso != 'F');
    data = inserisci_data(sesso);

    strcat(cf, get_cgn(cognome, 0));
    strcat(cf, get_cgn(nome, 1));
    cf[6] = data[6];
    cf[7] = data[7];
    cf[8] = get_month((data[3] - 48) * 10 + (data[4] - 48));
    cf[9] = data[0];
    cf[10] = data[1];
    cf[11] = 'G';
    cf[12] = '8';
    cf[13] = '2';
    cf[14] = '6';
    cf[15] = lettera_controllo(cf);
    cf[16] = '\0';

    printf("\nIl codice fiscale è: %s\n", cf);
    
    return 0;
}