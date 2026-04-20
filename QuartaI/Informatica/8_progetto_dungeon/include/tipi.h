#ifndef TIPI_H
#define TIPI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ───── Costanti ───── */
#define MAX_INPUT       128
#define MAX_NOME        64
#define MAX_DESC        256
#define MAX_INVENTARIO  8
#define MAX_STANZE      20
#define VERSIONE_SAVE   1

/* ───── Enum ───── */
typedef enum {
    POZIONE = 0,
    ARMA,
    ARMATURA,
    CHIAVE,
    TORCIA
} TipoOggetto;

typedef enum {
    SCHELETRO = 0,
    GOBLIN,
    DRAGO,
    BOSS
} TipoMostro;

typedef enum {
    CMD_NORD = 0,
    CMD_SUD,
    CMD_EST,
    CMD_OVEST,
    CMD_GUARDA,
    CMD_PRENDI,
    CMD_USA,
    CMD_ATTACCA,
    CMD_INVENTARIO,
    CMD_SALVA,
    CMD_CARICA,
    CMD_MAPPA,
    CMD_AIUTO,
    CMD_ESCI,
    CMD_SCONOSCIUTO
} TipoComando;

/* ───── Oggetto ───── */
typedef struct Oggetto {
    char         nome[MAX_NOME];
    TipoOggetto  tipo;
    int          valore;        /* HP ripristinati, bonus attacco/difesa, id porta... */
    struct Oggetto *next;       /* lista collegata nelle stanze */
} Oggetto;

/* ───── Mostro ───── */
typedef struct {
    char        nome[MAX_NOME];
    TipoMostro  tipo;
    int         hp;
    int         hp_max;
    int         attacco;
    int         difesa;
    int         xp_ricompensa;
    int         oro_ricompensa;
    int         vivo;
} Mostro;

/* ───── Stanza ───── */
typedef struct Stanza {
    int          id;
    char         nome[MAX_NOME];
    char         descrizione[MAX_DESC];
    struct Stanza *nord;
    struct Stanza *sud;
    struct Stanza *est;
    struct Stanza *ovest;
    Oggetto      *oggetti;      /* lista collegata degli oggetti nella stanza */
    Mostro       *mostro;
    int          visitata;
    int          bloccata_nord; /* id chiave richiesta, 0 = libero */
    int          bloccata_sud;
    int          bloccata_est;
    int          bloccata_ovest;
    int          nascosta;      /* rivelata solo con torcia */
} Stanza;

/* ───── Pila inventario ───── */
typedef struct {
    Oggetto *slot[MAX_INVENTARIO];
    int      top;   /* -1 = vuota */
} Pila;

/* ───── Eroe ───── */
typedef struct {
    char    nome[MAX_NOME];
    int     hp;
    int     hp_max;
    int     attacco;
    int     difesa;
    int     xp;
    int     livello;
    int     oro;
    Pila    inventario;
    Stanza *stanza_corrente;
} Eroe;

#endif /* TIPI_H */
