#ifndef EROE_H
#define EROE_H

#include "tipi.h"

/* Inizializza l'eroe con valori base */
void inizializza_eroe(Eroe *e, const char *nome, Stanza *stanza_iniziale);

/* Movimento — restituisce 1 se lo spostamento è avvenuto */
int muovi(Eroe *e, TipoComando dir);

/* Stampa inventario */
void stampa_inventario(const Eroe *e);

/* Prendi oggetto dalla stanza */
int prendi_oggetto(Eroe *e, const char *nome);

/* Usa oggetto dall'inventario */
int usa_oggetto(Eroe *e, const char *nome);

/* Controlla salita di livello */
void controlla_livello(Eroe *e);

/* Stampa stato eroe (HP, livello, stanza) */
void stampa_stato(const Eroe *e);

/* ─── Operazioni sulla pila ─── */
int     pila_push(Pila *p, Oggetto *o);
Oggetto *pila_pop(Pila *p);
Oggetto *pila_cerca(const Pila *p, const char *nome);

#endif /* EROE_H */
