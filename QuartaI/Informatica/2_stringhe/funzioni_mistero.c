#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Qual è l'output se in input fossero passati i parametri
//s = "conoscere il c mi farà diventare ricco"
//c = 'c'
char* mistero_1(char *s, char c) {    
    int len = strlen(s);
    char *ris = malloc((len + 1) * 
    sizeof(char));
    if (ris == NULL) return NULL;
    char *str1 = s;
    char *str2 = ris;
    int idx1 = 0, idx2 = 0;
    while (str1[idx1] != '\0') {
        if (str1[idx1] != c) {   
        str2[idx2] = str1[idx1];  
        idx2++;
        }
        idx1++;
    }



    str2[idx2] = '\0';
    ris = realloc(ris, strlen(str2) + 1 * sizeof(char)); 
    printf("%s", ris);
    return ris;
}

//"i l  c  m i  f a r à  r i c c o "
//c = 'c'






//Qual è l'output se in input fossero passati i parametri
//s = "tutti sono ricchi"
//c = 't'
void mistero_2(char *s, char c) {
    char *str1 = s;
    char *str2 = s;
    int fnd = 0, idx1 = 0, idx2 = 0;        //s = "tutti sono ricchi"  c='t'
    while (str1[idx1] != '\0') {
        if (str1[idx1] == c) {
            if (fnd == 0) {   
                str2[idx2++] = c;
                fnd = 1;   
            }
        } else {
            str2[idx2++] = str1[idx1];
            fnd = 0;  
        }
        idx1++;
    }
    str2[idx2] = '\0';
    printf("%s", s);
}

//Qual è l'output se in input fossero passati i parametri
//s = "conosco c.,sono ricco"
void mistero_3(char *s) {
    int len = strlen(s);

    int m = len / 2;
    int offset;
    if(len % 2 == 0) offset = m;
    else offset = m + 1; 

    for (int i = 0; i < m; i++) {
        char t = s[i];
        s[i] = s[i + offset];
        s[i + offset] = t;
    }
    printf("%s", s);
}


