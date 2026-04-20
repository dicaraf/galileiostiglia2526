#include "../include/tipi.h"
#include "../include/mappa.h"
#include "../include/eroe.h"
#include "../include/combattimento.h"
#include "../include/salvataggio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* ── Normalizza stringa: trim spazi, lowercase ── */
static void normalizza(char *s)
{
    /* trim testa */
    int inizio = 0;
    while (s[inizio] && isspace((unsigned char)s[inizio])) inizio++;
    if (inizio) memmove(s, s + inizio, strlen(s) - inizio + 1);
    /* trim coda */
    int len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len-1])) s[--len] = '\0';
    /* lowercase */
    for (int i = 0; s[i]; i++) s[i] = (char)tolower((unsigned char)s[i]);
}

/* ── Parser ── */
static TipoComando parse(const char *input, char *argomento)
{
    argomento[0] = '\0';
    char buf[MAX_INPUT];
    strncpy(buf, input, MAX_INPUT - 1);
    buf[MAX_INPUT - 1] = '\0';
    normalizza(buf);

    /* estrai prima parola e resto */
    char verbo[MAX_INPUT] = {0};
    char resto[MAX_INPUT] = {0};
    char *sp = strchr(buf, ' ');
    if (sp) {
        strncpy(verbo, buf, (size_t)(sp - buf));
        strncpy(resto, sp + 1, MAX_INPUT - 1);
    } else {
        strncpy(verbo, buf, MAX_INPUT - 1);
    }
    strncpy(argomento, resto, MAX_INPUT - 1);

    if (strcmp(verbo, "vai") == 0) {
        if (strcmp(argomento, "nord")  == 0) return CMD_NORD;
        if (strcmp(argomento, "sud")   == 0) return CMD_SUD;
        if (strcmp(argomento, "est")   == 0) return CMD_EST;
        if (strcmp(argomento, "ovest") == 0) return CMD_OVEST;
    }
    if (strcmp(verbo, "nord")  == 0) return CMD_NORD;
    if (strcmp(verbo, "sud")   == 0) return CMD_SUD;
    if (strcmp(verbo, "est")   == 0) return CMD_EST;
    if (strcmp(verbo, "ovest") == 0) return CMD_OVEST;
    if (strcmp(verbo, "n")     == 0) return CMD_NORD;
    if (strcmp(verbo, "s")     == 0) return CMD_SUD;
    if (strcmp(verbo, "e")     == 0) return CMD_EST;
    if (strcmp(verbo, "o")     == 0) return CMD_OVEST;

    if (strcmp(verbo, "guarda") == 0 || strcmp(verbo, "g") == 0) return CMD_GUARDA;
    if (strcmp(verbo, "prendi") == 0 || strcmp(verbo, "p") == 0) return CMD_PRENDI;
    if (strcmp(verbo, "usa")    == 0 || strcmp(verbo, "u") == 0) return CMD_USA;
    if (strcmp(verbo, "attacca")== 0 || strcmp(verbo, "a") == 0) return CMD_ATTACCA;
    if (strcmp(verbo, "inventario") == 0 || strcmp(verbo, "i") == 0) return CMD_INVENTARIO;
    if (strcmp(verbo, "salva") == 0)  return CMD_SALVA;
    if (strcmp(verbo, "carica") == 0) return CMD_CARICA;
    if (strcmp(verbo, "mappa")  == 0 || strcmp(verbo, "m") == 0) return CMD_MAPPA;
    if (strcmp(verbo, "aiuto")  == 0 || strcmp(verbo, "?") == 0 ||
        strcmp(verbo, "help")   == 0) return CMD_AIUTO;
    if (strcmp(verbo, "esci")   == 0 || strcmp(verbo, "exit") == 0 ||
        strcmp(verbo, "quit")   == 0) return CMD_ESCI;

    return CMD_SCONOSCIUTO;
}

/* ── Stampa descrizione stanza corrente ── */
static void guarda(const Eroe *e)
{
    Stanza *s = e->stanza_corrente;
    printf("\n>>> %s <<<\n%s\n", s->nome, s->descrizione);
    if (s->oggetti) {
        printf("\nOggetti: ");
        for (Oggetto *o = s->oggetti; o; o = o->next)
            printf("[%s] ", o->nome);
        putchar('\n');
    } else {
        printf("\nNessun oggetto qui.\n");
    }
    if (s->mostro && s->mostro->vivo)
        printf("\nNEMICO: %s (HP: %d/%d)\n",
               s->mostro->nome, s->mostro->hp, s->mostro->hp_max);
    printf("\nUscite: ");
    if (s->nord)  printf("[N] ");
    if (s->sud)   printf("[S] ");
    if (s->est)   printf("[E] ");
    if (s->ovest) printf("[O] ");
    putchar('\n');
}

/* ── Aiuto ── */
static void stampa_aiuto(void)
{
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║            COMANDI DISPONIBILI        ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  vai nord/sud/est/ovest  (o n/s/e/o)  ║\n");
    printf("║  guarda          (g)                  ║\n");
    printf("║  prendi [nome]   (p)                  ║\n");
    printf("║  usa [nome]      (u)                  ║\n");
    printf("║  attacca         (a)                  ║\n");
    printf("║  inventario      (i)                  ║\n");
    printf("║  mappa           (m)                  ║\n");
    printf("║  salva / carica                       ║\n");
    printf("║  aiuto / ?                            ║\n");
    printf("║  esci                                 ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
}

/* ── esegui_comando ── */
static void esegui_comando(TipoComando cmd, const char *arg,
                           Eroe *e, int *partita_vinta)
{
    switch (cmd) {
        case CMD_NORD:
        case CMD_SUD:
        case CMD_EST:
        case CMD_OVEST:
            muovi(e, cmd);
            /* controllo vittoria: stanza 9 + boss morto */
            if (e->stanza_corrente->id == 9) {
                Mostro *boss = e->stanza_corrente->mostro;
                if (boss && !boss->vivo) {
                    printf("\n╔══════════════════════════════════╗\n");
                    printf("║  HAI VINTO! IL DUNGEON E' LIBERO! ║\n");
                    printf("╚══════════════════════════════════╝\n\n");
                    *partita_vinta = 1;
                }
            }
            break;

        case CMD_GUARDA:
            guarda(e);
            break;

        case CMD_PRENDI:
            if (arg[0] == '\0')
                printf("Cosa vuoi prendere? (usa: prendi [nome])\n");
            else
                prendi_oggetto(e, arg);
            break;

        case CMD_USA:
            if (arg[0] == '\0')
                printf("Cosa vuoi usare? (usa: usa [nome])\n");
            else
                usa_oggetto(e, arg);
            break;

        case CMD_ATTACCA: {
            Stanza *s = e->stanza_corrente;
            if (s->mostro && s->mostro->vivo) {
                int vivo = combatti(e, s->mostro);
                if (!vivo) e->hp = 0;  /* il game loop gestisce la morte */
            } else {
                printf("Non c'e' nessun nemico qui.\n");
            }
            break;
        }

        case CMD_INVENTARIO:
            stampa_inventario(e);
            break;

        case CMD_SALVA:
            salva_partita(e, tutte_stanze, num_stanze);
            break;

        case CMD_CARICA:
            carica_partita(e, tutte_stanze, num_stanze);
            break;

        case CMD_MAPPA:
            stampa_mappa(tutte_stanze, num_stanze, e->stanza_corrente);
            break;

        case CMD_AIUTO:
            stampa_aiuto();
            break;

        case CMD_ESCI:
            printf("Abbandoni il dungeon. Arrivederci, avventuriero!\n");
            exit(0);

        case CMD_SCONOSCIUTO:
        default:
            printf("Comando non riconosciuto. Digita 'aiuto' per la lista comandi.\n");
            break;
    }
}

/* ════════════════════ MAIN ════════════════════ */
int main(void)
{
    srand((unsigned int)time(NULL));

    printf("╔══════════════════════════════════════╗\n");
    printf("║           D U N G E O N  C            ║\n");
    printf("║   Un'avventura testuale in C puro     ║\n");
    printf("╚══════════════════════════════════════╝\n\n");

    /* Nome eroe */
    char nome_eroe[MAX_NOME] = {0};
    printf("Inserisci il nome del tuo eroe: ");
    fgets(nome_eroe, MAX_NOME, stdin);
    nome_eroe[strcspn(nome_eroe, "\n")] = '\0';
    if (nome_eroe[0] == '\0') strncpy(nome_eroe, "Avventuriero", MAX_NOME - 1);

    /* Costruzione mappa */
    Stanza *inizio = costruisci_mappa();

    /* Inizializzazione eroe */
    Eroe eroe;
    inizializza_eroe(&eroe, nome_eroe, inizio);

    printf("\nBenvenuto, %s! Il dungeon ti attende...\n", eroe.nome);
    printf("Digita 'aiuto' per la lista dei comandi.\n\n");

    /* Prima descrizione */
    guarda(&eroe);

    /* ── Game loop ── */
    char input[MAX_INPUT];
    char argomento[MAX_INPUT];
    int  partita_vinta = 0;

    while (eroe.hp > 0 && !partita_vinta) {
        stampa_stato(&eroe);
        printf("> ");
        fflush(stdout);

        if (!fgets(input, MAX_INPUT, stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        TipoComando cmd = parse(input, argomento);
        esegui_comando(cmd, argomento, &eroe, &partita_vinta);
    }

    if (eroe.hp <= 0 && !partita_vinta) {
        printf("\n╔══════════════════════════════╗\n");
        printf("║  SEI MORTO. GAME OVER.        ║\n");
        printf("╚══════════════════════════════╝\n");
        printf("XP raggiunti: %d  Oro: %d  Livello: %d\n\n",
               eroe.xp, eroe.oro, eroe.livello);
    }

    /* Pulizia */
    for (int i = eroe.inventario.top; i >= 0; i--)
        free(eroe.inventario.slot[i]);
    distruggi_mappa(tutte_stanze, num_stanze);

    return 0;
}
