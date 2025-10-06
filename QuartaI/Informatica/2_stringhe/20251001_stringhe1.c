/*Scrivi un programma che permetta all'utente di inserire una stringa di 
20 caratteri, un carattere c e che trovi quante volte compare il carattere c
nella stringa.*/

#include<stdio.h>

int main(){
    char s[20];
    int cnt=0;
    int i=0;
    char car;

    printf("inserire la stringa");
    scanf("%19['^\n']s", s);

    printf("quale carattere si desidera cercare?");
    scanf("%c", &car);

    while(s[i]!='\0'){
        if(car==s[i]){
            cnt++;
        }
        i++;
    }
    printf("il carattere %c compare %d volte.", car, cnt);

    return 0;
}