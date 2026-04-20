#include "../include/mappa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stanza *tutte_stanze[MAX_STANZE];
int     num_stanze = 0;

/* ── helper per allocare una stanza ── */
static Stanza *nuova_stanza(int id, const char *nome, const char *desc)
{
    Stanza *s = calloc(1, sizeof(Stanza));
    if (!s) { perror("calloc stanza"); exit(EXIT_FAILURE); }
    s->id = id;
    strncpy(s->nome,        nome, MAX_NOME - 1);
    strncpy(s->descrizione, desc, MAX_DESC - 1);
    tutte_stanze[num_stanze++] = s;
    return s;
}

/* ── helper per aggiungere un oggetto a una stanza ── */
static void aggiungi_oggetto_stanza(Stanza *s, const char *nome,
                                    TipoOggetto tipo, int valore)
{
    Oggetto *o = calloc(1, sizeof(Oggetto));
    if (!o) { perror("calloc oggetto"); exit(EXIT_FAILURE); }
    strncpy(o->nome, nome, MAX_NOME - 1);
    o->tipo   = tipo;
    o->valore = valore;
    o->next   = s->oggetti;
    s->oggetti = o;
}

/* ── helper per creare un mostro ── */
static Mostro *nuovo_mostro(const char *nome, TipoMostro tipo,
                             int hp, int att, int def,
                             int xp, int oro)
{
    Mostro *m = calloc(1, sizeof(Mostro));
    if (!m) { perror("calloc mostro"); exit(EXIT_FAILURE); }
    strncpy(m->nome, nome, MAX_NOME - 1);
    m->tipo          = tipo;
    m->hp = m->hp_max = hp;
    m->attacco        = att;
    m->difesa         = def;
    m->xp_ricompensa  = xp;
    m->oro_ricompensa = oro;
    m->vivo           = 1;
    return m;
}

/* ════════════════════════════════════════════════
   Costruisce la mappa (grafo di 10 stanze)

   Layout (coordinate logiche):

      [0]Ingresso──E──[1]Corridoio──E──[2]Armeria
                            |S                |S
                       [3]Cripta        [4]Laboratorio
                            |S                |S
                       [5]Sala Troni   [6]Prigione──E──[7]Segreta
                            |S
                       [8]Altare──E──[9]BOSS
   ════════════════════════════════════════════════ */
Stanza *costruisci_mappa(void)
{
    num_stanze = 0;

    Stanza *s0 = nuova_stanza(0,  "Ingresso del Dungeon",
        "Ti trovi all'ingresso di un tetro dungeon. L'aria e' umida e puzza di muffa. "
        "Una torcia consunta illumina le pareti di pietra.");

    Stanza *s1 = nuova_stanza(1,  "Corridoio Oscuro",
        "Un lungo corridoio buio. Le ombre si muovono sulle pareti. "
        "Si sente il gocciolio dell'acqua in lontananza.");

    Stanza *s2 = nuova_stanza(2,  "Armeria Abbandonata",
        "Scaffali arrugginiti tappezzano le pareti. Qualche arma e' ancora utilizzabile. "
        "L'odore di metallo arrugginito e' pungente.");

    Stanza *s3 = nuova_stanza(3,  "Cripta degli Antenati",
        "Sarcofagi di pietra si allineano lungo i muri. Iscrizioni in una lingua antica "
        "coprono ogni superficie. Uno scheletro cammina tra le tombe.");

    Stanza *s4 = nuova_stanza(4,  "Laboratorio del Mago",
        "Libri, alambicchi e ingredienti misteriosi riempiono ogni angolo. "
        "Un goblin sta frugando tra gli scaffali.");

    Stanza *s5 = nuova_stanza(5,  "Sala del Trono Dimenticata",
        "Un enorme trono di ossidiana domina la stanza. Tappeti rossi ormai sbiaditi "
        "coprono il pavimento. La porta nord e' sigillata con una chiave speciale.");

    Stanza *s6 = nuova_stanza(6,  "Prigione",
        "Celle arrugginite si estendono su entrambi i lati. Catene e ossa raccontano "
        "storie di prigionieri dimenticati.");

    Stanza *s7 = nuova_stanza(7,  "Camera Segreta",
        "Una stanza nascosta, rivelata solo dalla luce di una torcia. "
        "Un tesoro dimenticato giace nell'angolo. E' sorvegliato da un drago.");
    s7->nascosta = 1;   /* richiede torcia per essere visitata normalmente */

    Stanza *s8 = nuova_stanza(8,  "Altare del Sacrificio",
        "Un altare macchiato di sangue antico campeggia al centro. "
        "Rune luminose indicano che qualcosa di potente e' avvenuto qui.");

    Stanza *s9 = nuova_stanza(9,  "Sala del Boss – Mortarion",
        "Un'enorme stanza circolare. Al centro, avvolto in un manto di oscurita', "
        "siede MORTARION, il Signore delle Tenebre. I suoi occhi brillano di odio eterno.");

    /* ── Connessioni (grafo bidirezionale) ── */
    /* s0 ──E── s1 */
    s0->est = s1;  s1->ovest = s0;
    /* s1 ──E── s2 */
    s1->est = s2;  s2->ovest = s1;
    /* s1 ──S── s3 */
    s1->sud = s3;  s3->nord = s1;
    /* s2 ──S── s4 */
    s2->sud = s4;  s4->nord = s2;
    /* s3 ──S── s5 */
    s3->sud = s5;  s5->nord = s3;
    /* s4 ──S── s6 */
    s4->sud = s6;  s6->nord = s4;
    /* s6 ──E── s7 (nascosta) */
    s6->est = s7;  s7->ovest = s6;
    /* s5 ──S── s8 */
    s5->sud = s8;  s8->nord = s5;
    /* s8 ──E── s9 (bloccata: richiede Chiave del Boss, valore=99) */
    s8->est = s9;  s9->ovest = s8;
    s8->bloccata_est = 99;   /* id chiave */

    /* ── Oggetti nelle stanze ── */
    aggiungi_oggetto_stanza(s0, "Torcia",          TORCIA,   0);
    aggiungi_oggetto_stanza(s0, "Pozione Minore",  POZIONE, 20);
    aggiungi_oggetto_stanza(s2, "Spada Arrugginita", ARMA,   5);
    aggiungi_oggetto_stanza(s2, "Scudo di Legno",  ARMATURA, 3);
    aggiungi_oggetto_stanza(s4, "Pozione Maggiore",POZIONE, 50);
    aggiungi_oggetto_stanza(s4, "Chiave di Ferro", CHIAVE,  99);  /* apre s8→s9 */
    aggiungi_oggetto_stanza(s6, "Pozione Minore",  POZIONE, 20);
    aggiungi_oggetto_stanza(s7, "Spada Fiammante", ARMA,   15);
    aggiungi_oggetto_stanza(s7, "Armatura Nera",   ARMATURA, 8);
    aggiungi_oggetto_stanza(s8, "Elixir Supremo",  POZIONE, 999);

    /* ── Mostri ── */
    s3->mostro = nuovo_mostro("Scheletro Guerriero", SCHELETRO, 30, 8,  2, 40,  15);
    s4->mostro = nuovo_mostro("Goblin Maledetto",    GOBLIN,    20, 6,  1, 25,  10);
    s7->mostro = nuovo_mostro("Drago Giovane",       DRAGO,     80, 18, 5, 120, 60);
    s9->mostro = nuovo_mostro("Mortarion",           BOSS,     200, 25, 8, 500, 200);

    return s0;
}

void distruggi_mappa(Stanza **stanze, int n)
{
    for (int i = 0; i < n; i++) {
        if (!stanze[i]) continue;
        /* libera lista oggetti */
        Oggetto *o = stanze[i]->oggetti;
        while (o) {
            Oggetto *tmp = o->next;
            free(o);
            o = tmp;
        }
        free(stanze[i]->mostro);
        free(stanze[i]);
        stanze[i] = NULL;
    }
}

/* ════ Mappa ASCII ════
   Rappresentazione a griglia 5×3 (id → posizione hardcoded) */
/* (id stanza, riga, colonna) nel display */
static const int pos[][3] = {
    {0, 0, 0},
    {1, 0, 2},
    {2, 0, 4},
    {3, 1, 2},
    {4, 1, 4},
    {5, 2, 2},
    {6, 2, 4},
    {7, 2, 6},   /* fuori griglia normale, mostrata se visitata */
    {8, 3, 2},
    {9, 3, 4},
    {-1,-1,-1}
};

void stampa_mappa(Stanza **stanze, int n, Stanza *corrente)
{
    /* matrice di caratteri 7 righe × 15 colonne */
    #define MR 8
    #define MC 16
    char grid[MR][MC];
    memset(grid, ' ', sizeof(grid));
    for (int r = 0; r < MR; r++) grid[r][MC-1] = '\0';

    for (int i = 0; pos[i][0] != -1; i++) {
        int id = pos[i][0];
        int r  = pos[i][1];
        int c  = pos[i][2];
        if (id >= n || !stanze[id]) continue;
        if (!stanze[id]->visitata)  continue;
        if (r >= MR || c >= MC-2)   continue;
        if (stanze[id] == corrente)
            grid[r][c] = '@';
        else
            grid[r][c] = '#';
        /* connessioni est */
        if (c+2 < MC-1 && stanze[id]->est) {
            int eid = stanze[id]->est->id;
            if (eid < n && stanze[eid] && stanze[eid]->visitata)
                grid[r][c+1] = '-';
        }
        /* connessioni sud */
        if (r+1 < MR && stanze[id]->sud) {
            int sid = stanze[id]->sud->id;
            if (sid < n && stanze[sid] && stanze[sid]->visitata)
                grid[r+1][c] = '|';
        }
    }

    printf("\n╔═══════════════════╗\n");
    printf("║  MAPPA DUNGEON     ║\n");
    printf("╠═══════════════════╣\n");
    for (int r = 0; r < MR; r++) {
        printf("║  ");
        for (int c = 0; c < 13; c++)
            putchar(grid[r][c]);
        printf("  ║\n");
    }
    printf("╚═══════════════════╝\n");
    printf(" @ = tu   # = stanza visitata\n\n");
}
