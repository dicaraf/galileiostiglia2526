#define _GNU_SOURCE
#include "../include/eroe.h"
#include "../include/mappa.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

/* ─── Pila ─── */
int pila_push(Pila *p, Oggetto *o)
{
    if (p->top >= MAX_INVENTARIO - 1) {
        printf("L'inventario e' pieno! Lascia qualcosa prima di raccogliere.\n");
        return 0;
    }
    p->slot[++(p->top)] = o;
    return 1;
}

Oggetto *pila_pop(Pila *p)
{
    if (p->top < 0) return NULL;
    return p->slot[(p->top)--];
}

Oggetto *pila_cerca(const Pila *p, const char *nome)
{
    for (int i = p->top; i >= 0; i--) {
        if (strcasecmp(p->slot[i]->nome, nome) == 0)
            return p->slot[i];
    }
    return NULL;
}

/* ─── Inizializzazione ─── */
void inizializza_eroe(Eroe *e, const char *nome, Stanza *stanza_iniziale)
{
    memset(e, 0, sizeof(Eroe));
    strncpy(e->nome, nome, MAX_NOME - 1);
    e->hp = e->hp_max = 100;
    e->attacco  = 10;
    e->difesa   = 3;
    e->xp       = 0;
    e->livello  = 1;
    e->oro      = 0;
    e->inventario.top = -1;
    e->stanza_corrente = stanza_iniziale;
    stanza_iniziale->visitata = 1;
}

/* ─── Controlla salita livello ─── */
void controlla_livello(Eroe *e)
{
    /* soglie: 100 xp per lv2, 250 per lv3, 500 per lv4, 1000 per lv5 */
    int soglie[] = {0, 100, 250, 500, 1000, 99999};
    int lv = e->livello;
    if (lv >= 5) return;
    if (e->xp >= soglie[lv]) {
        e->livello++;
        e->hp_max   += 20;
        e->hp        = e->hp_max;
        e->attacco  += 3;
        e->difesa   += 1;
        printf("\n*** SALITA DI LIVELLO! Sei ora Livello %d! ***\n", e->livello);
        printf("    HP max: %d  Attacco: %d  Difesa: %d\n\n",
               e->hp_max, e->attacco, e->difesa);
    }
}

/* ─── Stampa stato ─── */
void stampa_stato(const Eroe *e)
{
    printf("\n─────────────────────────────────\n");
    printf(" %s  [Lv%d]  HP: %d/%d  XP: %d  Oro: %d\n",
           e->nome, e->livello, e->hp, e->hp_max, e->xp, e->oro);
    printf(" Stanza: %s\n", e->stanza_corrente->nome);
    printf("─────────────────────────────────\n");
}

/* ─── Stampa inventario ─── */
static const char *nome_tipo_oggetto(TipoOggetto t)
{
    switch(t) {
        case POZIONE:  return "Pozione";
        case ARMA:     return "Arma";
        case ARMATURA: return "Armatura";
        case CHIAVE:   return "Chiave";
        case TORCIA:   return "Torcia";
        default:       return "?";
    }
}

void stampa_inventario(const Eroe *e)
{
    printf("\n══ Inventario (%d/%d) ══\n", e->inventario.top + 1, MAX_INVENTARIO);
    if (e->inventario.top < 0) {
        printf("  (vuoto)\n");
    } else {
        for (int i = e->inventario.top; i >= 0; i--) {
            Oggetto *o = e->inventario.slot[i];
            printf("  [%d] %s (%s)", i + 1, o->nome, nome_tipo_oggetto(o->tipo));
            switch (o->tipo) {
                case POZIONE:  printf(" – ripristina %d HP", o->valore); break;
                case ARMA:     printf(" – +%d attacco",       o->valore); break;
                case ARMATURA: printf(" – +%d difesa",        o->valore); break;
                case CHIAVE:   printf(" – apre porte speciali"); break;
                case TORCIA:   printf(" – rivela stanze nascoste"); break;
            }
            putchar('\n');
        }
    }
    putchar('\n');
}

/* ─── Movimento ─── */
int muovi(Eroe *e, TipoComando dir)
{
    Stanza *s    = e->stanza_corrente;
    Stanza *dest = NULL;
    int     bloccata = 0;
    int     id_chiave = 0;

    switch (dir) {
        case CMD_NORD:  dest = s->nord;  bloccata = s->bloccata_nord; break;
        case CMD_SUD:   dest = s->sud;   bloccata = s->bloccata_sud;  break;
        case CMD_EST:   dest = s->est;   bloccata = s->bloccata_est;  break;
        case CMD_OVEST: dest = s->ovest; bloccata = s->bloccata_ovest;break;
        default: break;
    }

    if (!dest) {
        printf("Non puoi andare in quella direzione.\n");
        return 0;
    }

    /* stanza nascosta: richiede torcia */
    if (dest->nascosta) {
        int ha_torcia = 0;
        for (int i = e->inventario.top; i >= 0; i--)
            if (e->inventario.slot[i]->tipo == TORCIA) { ha_torcia = 1; break; }
        if (!ha_torcia) {
            printf("E' troppo buio per procedere. Ti serve una torcia.\n");
            return 0;
        }
        dest->nascosta = 0; /* rivelata */
    }

    /* porta bloccata */
    if (bloccata) {
        id_chiave = bloccata;
        int trovata = 0;
        for (int i = e->inventario.top; i >= 0; i--) {
            if (e->inventario.slot[i]->tipo   == CHIAVE &&
                e->inventario.slot[i]->valore == id_chiave) {
                trovata = 1;
                break;
            }
        }
        if (!trovata) {
            printf("La porta e' bloccata. Ti serve una chiave speciale.\n");
            return 0;
        }
        /* sblocca permanentemente */
        switch (dir) {
            case CMD_NORD:  s->bloccata_nord  = 0; break;
            case CMD_SUD:   s->bloccata_sud   = 0; break;
            case CMD_EST:   s->bloccata_est   = 0; break;
            case CMD_OVEST: s->bloccata_ovest = 0; break;
            default: break;
        }
        printf("Usi la chiave per aprire la porta.\n");
    }

    e->stanza_corrente = dest;
    dest->visitata = 1;
    printf("Ti sposti verso %s...\n\n", dest->nome);

    /* descrizione automatica */
    printf(">>> %s <<<\n%s\n", dest->nome, dest->descrizione);

    /* oggetti nella stanza */
    if (dest->oggetti) {
        printf("\nOggetti presenti: ");
        for (Oggetto *o = dest->oggetti; o; o = o->next)
            printf("[%s] ", o->nome);
        putchar('\n');
    }

    /* mostro */
    if (dest->mostro && dest->mostro->vivo)
        printf("\nATTENZIONE: c'e' un %s qui!\n", dest->mostro->nome);

    return 1;
}

/* ─── Prendi oggetto ─── */
int prendi_oggetto(Eroe *e, const char *nome)
{
    Stanza *s = e->stanza_corrente;
    Oggetto *prec = NULL;
    Oggetto *curr = s->oggetti;

    while (curr) {
        if (strcasecmp(curr->nome, nome) == 0) {
            /* rimuovi dalla lista */
            if (prec) prec->next  = curr->next;
            else      s->oggetti  = curr->next;
            curr->next = NULL;

            if (!pila_push(&e->inventario, curr)) {
                /* rimetti in lista */
                curr->next = s->oggetti;
                s->oggetti = curr;
                return 0;
            }
            printf("Hai raccolto: %s\n", curr->nome);

            /* effetto immediato armatura/arma */
            if (curr->tipo == ARMA) {
                e->attacco += curr->valore;
                printf("Equipaggi l'arma: +%d attacco!\n", curr->valore);
            } else if (curr->tipo == ARMATURA) {
                e->difesa += curr->valore;
                printf("Indossi l'armatura: +%d difesa!\n", curr->valore);
            }
            return 1;
        }
        prec = curr;
        curr = curr->next;
    }
    printf("Non c'e' nessun '%s' qui.\n", nome);
    return 0;
}

/* ─── Usa oggetto ─── */
int usa_oggetto(Eroe *e, const char *nome)
{
    /* cerca per nome nella pila */
    int idx = -1;
    for (int i = e->inventario.top; i >= 0; i--) {
        if (strcasecmp(e->inventario.slot[i]->nome, nome) == 0) {
            idx = i; break;
        }
    }
    if (idx < 0) {
        printf("Non hai '%s' nell'inventario.\n", nome);
        return 0;
    }

    Oggetto *o = e->inventario.slot[idx];

    switch (o->tipo) {
        case POZIONE: {
            int cura = (o->valore == 999) ? e->hp_max : o->valore;
            e->hp += cura;
            if (e->hp > e->hp_max) e->hp = e->hp_max;
            printf("Bevi la %s e recuperi %d HP. HP: %d/%d\n",
                   o->nome, cura, e->hp, e->hp_max);
            break;
        }
        case TORCIA:
            printf("Usi la torcia: l'oscurita' si dirada, "
                   "rivelando possibili passaggi nascosti.\n");
            /* la torcia rimane in inventario (consumo a discrezione) */
            return 1;
        case CHIAVE:
            printf("Usa la chiave direttamente camminando verso una porta bloccata.\n");
            return 1;
        case ARMA:
        case ARMATURA:
            printf("Lo usi automaticamente quando lo raccogli.\n");
            return 1;
    }

    /* rimuovi dalla pila spostando gli elementi */
    for (int i = idx; i < e->inventario.top; i++)
        e->inventario.slot[i] = e->inventario.slot[i+1];
    e->inventario.top--;
    free(o);
    return 1;
}
