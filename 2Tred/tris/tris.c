#include <stdio.h>

int main() {

    /* Campo di gioco */
    char a=' ', b=' ', c=' ';
    char d=' ', e=' ', f=' ';
    char g=' ', h=' ', i=' ';

    char giocatore = 'X';
    int pos;
    int mosse = 0;
    int fine = 0;

    printf("GIOCO DEL TRIS\n");

    /* ===== MOSSA 1 ===== */
    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
    scanf("%d", &pos);

    if(pos==1 && a==' ') a=giocatore;
    else if(pos==2 && b==' ') b=giocatore;
    else if(pos==3 && c==' ') c=giocatore;
    else if(pos==4 && d==' ') d=giocatore;
    else if(pos==5 && e==' ') e=giocatore;
    else if(pos==6 && f==' ') f=giocatore;
    else if(pos==7 && g==' ') g=giocatore;
    else if(pos==8 && h==' ') h=giocatore;
    else if(pos==9 && i==' ') i=giocatore;
    else {
        printf("Mossa non valida\n");
        return 1;
    }

    mosse++;

    printf("\n %c | %c | %c\n", a,b,c);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", d,e,f);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", g,h,i);

    /* Cambio giocatore */
    if(giocatore=='X') giocatore='O';
    else giocatore='X';

    /* ===== MOSSA 2 ===== */
    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
    scanf("%d", &pos);

    if(pos==1 && a==' ') a=giocatore;
    else if(pos==2 && b==' ') b=giocatore;
    else if(pos==3 && c==' ') c=giocatore;
    else if(pos==4 && d==' ') d=giocatore;
    else if(pos==5 && e==' ') e=giocatore;
    else if(pos==6 && f==' ') f=giocatore;
    else if(pos==7 && g==' ') g=giocatore;
    else if(pos==8 && h==' ') h=giocatore;
    else if(pos==9 && i==' ') i=giocatore;
    else {
        printf("Mossa non valida\n");
        return 1;
    }

    mosse++;

    printf("\n %c | %c | %c\n", a,b,c);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", d,e,f);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", g,h,i);

    /* Cambio giocatore */
    if(giocatore=='X') giocatore='O';
    else giocatore='X';

    /* ===== MOSSA 3 ===== */
    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
    scanf("%d", &pos);

    if(pos==1 && a==' ') a=giocatore;
    else if(pos==2 && b==' ') b=giocatore;
    else if(pos==3 && c==' ') c=giocatore;
    else if(pos==4 && d==' ') d=giocatore;
    else if(pos==5 && e==' ') e=giocatore;
    else if(pos==6 && f==' ') f=giocatore;
    else if(pos==7 && g==' ') g=giocatore;
    else if(pos==8 && h==' ') h=giocatore;
    else if(pos==9 && i==' ') i=giocatore;
    else {
        printf("Mossa non valida\n");
        return 1;
    }

    mosse++;

    printf("\n %c | %c | %c\n", a,b,c);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", d,e,f);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", g,h,i);

    /* Cambio giocatore */
    if(giocatore=='X') giocatore='O';
    else giocatore='X';

    /* ===== MOSSA 4 ===== */
    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
    scanf("%d", &pos);

    if(pos==1 && a==' ') a=giocatore;
    else if(pos==2 && b==' ') b=giocatore;
    else if(pos==3 && c==' ') c=giocatore;
    else if(pos==4 && d==' ') d=giocatore;
    else if(pos==5 && e==' ') e=giocatore;
    else if(pos==6 && f==' ') f=giocatore;
    else if(pos==7 && g==' ') g=giocatore;
    else if(pos==8 && h==' ') h=giocatore;
    else if(pos==9 && i==' ') i=giocatore;
    else {
        printf("Mossa non valida\n");
        return 1;
    }

    mosse++;

    printf("\n %c | %c | %c\n", a,b,c);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", d,e,f);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", g,h,i);

    /* Cambio giocatore */
    if(giocatore=='X') giocatore='O';
    else giocatore='X';

    /* ===== MOSSA 5 ===== */
    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
    scanf("%d", &pos);

    if(pos==1 && a==' ') a=giocatore;
    else if(pos==2 && b==' ') b=giocatore;
    else if(pos==3 && c==' ') c=giocatore;
    else if(pos==4 && d==' ') d=giocatore;
    else if(pos==5 && e==' ') e=giocatore;
    else if(pos==6 && f==' ') f=giocatore;
    else if(pos==7 && g==' ') g=giocatore;
    else if(pos==8 && h==' ') h=giocatore;
    else if(pos==9 && i==' ') i=giocatore;
    else {
        printf("Mossa non valida\n");
        return 1;
    }

    mosse++;

    printf("\n %c | %c | %c\n", a,b,c);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", d,e,f);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", g,h,i);

    /* Controllo vittoria */
    if((a==giocatore && b==giocatore && c==giocatore) ||
       (d==giocatore && e==giocatore && f==giocatore) ||
       (g==giocatore && h==giocatore && i==giocatore) ||
       (a==giocatore && d==giocatore && g==giocatore) ||
       (b==giocatore && e==giocatore && h==giocatore) ||
       (c==giocatore && f==giocatore && i==giocatore) ||
       (a==giocatore && e==giocatore && i==giocatore) ||
       (c==giocatore && e==giocatore && g==giocatore)) {

        printf("\nVince il giocatore %c!\n", giocatore);
        fine = 1;
    }

    /* Cambio giocatore */
    if(giocatore=='X') giocatore='O';
    else giocatore='X';

    /* ===== MOSSA 6 ===== */
    if(fine == 0) 
    {    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
        scanf("%d", &pos);

        if(pos==1 && a==' ') a=giocatore;
        else if(pos==2 && b==' ') b=giocatore;
        else if(pos==3 && c==' ') c=giocatore;
        else if(pos==4 && d==' ') d=giocatore;
        else if(pos==5 && e==' ') e=giocatore;
        else if(pos==6 && f==' ') f=giocatore;
        else if(pos==7 && g==' ') g=giocatore;
        else if(pos==8 && h==' ') h=giocatore;
        else if(pos==9 && i==' ') i=giocatore;
        else {
            printf("Mossa non valida\n");
            return 1;
        }

        mosse++;

        printf("\n %c | %c | %c\n", a,b,c);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", d,e,f);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", g,h,i);

        /* Controllo vittoria */
        if((a==giocatore && b==giocatore && c==giocatore) ||
        (d==giocatore && e==giocatore && f==giocatore) ||
        (g==giocatore && h==giocatore && i==giocatore) ||
        (a==giocatore && d==giocatore && g==giocatore) ||
        (b==giocatore && e==giocatore && h==giocatore) ||
        (c==giocatore && f==giocatore && i==giocatore) ||
        (a==giocatore && e==giocatore && i==giocatore) ||
        (c==giocatore && e==giocatore && g==giocatore)) {

            printf("\nVince il giocatore %c!\n", giocatore);
            fine = 1;
        }

        /* Cambio giocatore */
        if(giocatore=='X') giocatore='O';
        else giocatore='X';
    }

    /* ===== MOSSA 7 ===== */
    if(fine == 0) 
    {    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
        scanf("%d", &pos);

        if(pos==1 && a==' ') a=giocatore;
        else if(pos==2 && b==' ') b=giocatore;
        else if(pos==3 && c==' ') c=giocatore;
        else if(pos==4 && d==' ') d=giocatore;
        else if(pos==5 && e==' ') e=giocatore;
        else if(pos==6 && f==' ') f=giocatore;
        else if(pos==7 && g==' ') g=giocatore;
        else if(pos==8 && h==' ') h=giocatore;
        else if(pos==9 && i==' ') i=giocatore;
        else {
            printf("Mossa non valida\n");
            return 1;
        }

        mosse++;

        printf("\n %c | %c | %c\n", a,b,c);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", d,e,f);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", g,h,i);

        /* Controllo vittoria */
        if((a==giocatore && b==giocatore && c==giocatore) ||
        (d==giocatore && e==giocatore && f==giocatore) ||
        (g==giocatore && h==giocatore && i==giocatore) ||
        (a==giocatore && d==giocatore && g==giocatore) ||
        (b==giocatore && e==giocatore && h==giocatore) ||
        (c==giocatore && f==giocatore && i==giocatore) ||
        (a==giocatore && e==giocatore && i==giocatore) ||
        (c==giocatore && e==giocatore && g==giocatore)) {

            printf("\nVince il giocatore %c!\n", giocatore);
            fine = 1;
        }

        /* Cambio giocatore */
        if(giocatore=='X') giocatore='O';
        else giocatore='X';
    }

    /* ===== MOSSA 8 ===== */
    if(fine == 0) 
    {    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
        scanf("%d", &pos);

        if(pos==1 && a==' ') a=giocatore;
        else if(pos==2 && b==' ') b=giocatore;
        else if(pos==3 && c==' ') c=giocatore;
        else if(pos==4 && d==' ') d=giocatore;
        else if(pos==5 && e==' ') e=giocatore;
        else if(pos==6 && f==' ') f=giocatore;
        else if(pos==7 && g==' ') g=giocatore;
        else if(pos==8 && h==' ') h=giocatore;
        else if(pos==9 && i==' ') i=giocatore;
        else {
            printf("Mossa non valida\n");
            return 1;
        }

        mosse++;

        printf("\n %c | %c | %c\n", a,b,c);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", d,e,f);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", g,h,i);

        /* Controllo vittoria */
        if((a==giocatore && b==giocatore && c==giocatore) ||
        (d==giocatore && e==giocatore && f==giocatore) ||
        (g==giocatore && h==giocatore && i==giocatore) ||
        (a==giocatore && d==giocatore && g==giocatore) ||
        (b==giocatore && e==giocatore && h==giocatore) ||
        (c==giocatore && f==giocatore && i==giocatore) ||
        (a==giocatore && e==giocatore && i==giocatore) ||
        (c==giocatore && e==giocatore && g==giocatore)) {

            printf("\nVince il giocatore %c!\n", giocatore);
            fine = 1;
        }

        /* Cambio giocatore */
        if(giocatore=='X') giocatore='O';
        else giocatore='X';
    }

    /* ===== MOSSA 9 ===== */
    if(fine == 0) 
    {    printf("\nGiocatore %c, scegli una posizione (1-9): ", giocatore);
        scanf("%d", &pos);

        if(pos==1 && a==' ') a=giocatore;
        else if(pos==2 && b==' ') b=giocatore;
        else if(pos==3 && c==' ') c=giocatore;
        else if(pos==4 && d==' ') d=giocatore;
        else if(pos==5 && e==' ') e=giocatore;
        else if(pos==6 && f==' ') f=giocatore;
        else if(pos==7 && g==' ') g=giocatore;
        else if(pos==8 && h==' ') h=giocatore;
        else if(pos==9 && i==' ') i=giocatore;
        else {
            printf("Mossa non valida\n");
            return 1;
        }

        mosse++;

        printf("\n %c | %c | %c\n", a,b,c);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", d,e,f);
        printf("---+---+---\n");
        printf(" %c | %c | %c\n", g,h,i);

        /* Controllo vittoria */
        if((a==giocatore && b==giocatore && c==giocatore) ||
        (d==giocatore && e==giocatore && f==giocatore) ||
        (g==giocatore && h==giocatore && i==giocatore) ||
        (a==giocatore && d==giocatore && g==giocatore) ||
        (b==giocatore && e==giocatore && h==giocatore) ||
        (c==giocatore && f==giocatore && i==giocatore) ||
        (a==giocatore && e==giocatore && i==giocatore) ||
        (c==giocatore && e==giocatore && g==giocatore)) {

            printf("\nVince il giocatore %c!\n", giocatore);
            fine = 1;
        }

        /* Cambio giocatore */
        if(giocatore=='X') giocatore='O';
        else giocatore='X';
    }

    if(fine == 0 && mosse==9)
        printf("\nPareggio!\n");

    return 0;
}