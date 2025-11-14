/*Si vuole creare un'applicazione in C che possa gestire le partite del
torneo di istituto. Quindi si vuole registrare un elenco dell squadre 
che giocano a pallavolo: l'utente dovrà inserire la classe e la sezione della 
squadra, un nome per la squadra e un elenco di 6 nomi che memorizzi i partecipanti.
Inoltre si vogliono memorizzare i risultati delle partite: ogni risultato prevede 
le due squadre che si sono affrontate, il giorno della partita e il punteggio finale.*/

#include <stdio.h>
#include <string.h>

#define MAX_SQUADRE 10
#define MAX_PARTITE 20

typedef struct{
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char nome[30];
    int classe;
    char sezione;
    char giocatori[6][30];
} Squadra;

typedef struct {
    Squadra *squadra1;
    Squadra *squadra2;
    int punti1;
    int punti2;
    Data giorno_partita;
} Partita;

// Funzione per inserire una squadra
void inserisciSquadra(Squadra *s) {
    char c;
    printf("Inserisci il nome della tua squadra: ");
    fgets(s->nome, 30, stdin);
    printf("Inserisci la classe della squadra: ");
    scanf("%d", &s->classe);
    while((c = getchar()) != '\n') {}
    printf("Inserisci la sezione della squadra: ");
    scanf("%c", &s->sezione);
    while((c = getchar()) != '\n') {}
    for(int i = 0; i < 6; i++){
        printf("Inserisci il nome del giocatore %d", i+1);
        fgets(s->giocatori[i], 30, stdin);
    }


}

// Funzione per stampare una squadra
void stampaSquadra(Squadra s) {
    printf("nome squadra:%s",s.nome);
    printf("classe:%d%c\n",s.classe,s.sezione);
    for(int i = 0; i<6;i++){
        printf("giocatore %d:%s",i+1,s.giocatori[i]);
    }


}

// Funzione per registrare una partita
void inserisciPartita(Partita *p, Squadra squadre[], int numSquadre) {

    int num;
    char c;

    for(int i=0; i<numSquadre; i++){
        printf("Squadra[%d]", i);
        stampaSquadra(squadre[i]);
    }
        
    printf("Qual è la prima squadra che vuoi inserire?");
    scanf("%d",&num);
    while((c = getchar()) != '\n') {}
    p->squadra1=&squadre[num];

    printf("Qual è la seconda squadra che vuoi inserire?");
    scanf("%d",&num);
    while((c = getchar()) != '\n') {}
    p->squadra2=&squadre[num];

    printf("Inserisci il punteggio della squadra %s", p->squadra1->nome);
    scanf("%d", &p->punti1);
    printf("Inserisci il punteggio della squadra %s", p->squadra2->nome);
    scanf("%d", &p->punti2);

    printf("Inserisci la data della partita: ");
    scanf("%d %d %d", &p->giorno_partita.giorno, &p->giorno_partita.mese, &p->giorno_partita.anno);
}

// Funzione per stampare i risultati
void stampaPartite(const Partita partite[], int numPartite) {
    for(int i=0; i<numPartite; i++ ){
        printf("Nella data %d %d %d  : %s(%d%c) %d - %d %s(%d%c)", partite[i].giorno_partita.giorno, partite[i].giorno_partita.mese, partite[i].giorno_partita.anno, partite[i].squadra1->nome, partite[i].squadra1->classe, partite[i].squadra1->sezione, partite[i].punti1, partite[i].punti2, partite[i].squadra2->nome, partite[i].squadra2->classe, partite[i].squadra2->sezione);
    }
}

int main() {
    Squadra squadre[MAX_SQUADRE];
    Partita partite[MAX_PARTITE];
    int numSquadre = 0, numPartite = 0;
    int scelta;
    char c;

    do {
        printf("\n===== TORNEO DI PALLAVOLO =====\n");
        printf("1. Inserisci nuova squadra\n");
        printf("2. Visualizza squadre\n");
        printf("3. Registra una partita\n");
        printf("4. Visualizza risultati\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        while((c = getchar()) != '\n') {}

        switch (scelta) {
            case 1:
                if (numSquadre < MAX_SQUADRE)
                    inserisciSquadra(&squadre[numSquadre++]);
                else
                    printf("Numero massimo di squadre raggiunto!\n");
                break;
            case 2:
                for (int i = 0; i < numSquadre; i++)
                    stampaSquadra(squadre[i]);
                break;
            case 3:
                if (numSquadre < 2) {
                    printf("Devi inserire almeno due squadre!\n");
                    break;
                }
                if (numPartite < MAX_PARTITE)
                    inserisciPartita(&partite[numPartite++], squadre, numSquadre);
                else
                    printf("Numero massimo di partite raggiunto!\n");
                break;
            case 4:
                stampaPartite(partite, numPartite);
                break;
            case 0:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (scelta != 0);

    return 0;
}
