#ifndef COMBATTIMENTO_H
#define COMBATTIMENTO_H

#include "tipi.h"

/* Avvia il combattimento a turni; restituisce 1 se l'eroe sopravvive */
int combatti(Eroe *e, Mostro *m);

/* Calcola danno: rand() % attacco + 1, ridotto dalla difesa del bersaglio */
int calcola_danno(int attacco, int difesa);

#endif /* COMBATTIMENTO_H */
