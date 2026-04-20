#ifndef SALVATAGGIO_H
#define SALVATAGGIO_H

#include "tipi.h"

#define PERCORSO_SAVE "save/partita.sav"

/* Scrive lo stato sul file binario; restituisce 1 se ok */
int salva_partita(const Eroe *e, Stanza **stanze, int n);

/* Legge lo stato dal file binario; restituisce 1 se ok */
int carica_partita(Eroe *e, Stanza **stanze, int n);

#endif /* SALVATAGGIO_H */
