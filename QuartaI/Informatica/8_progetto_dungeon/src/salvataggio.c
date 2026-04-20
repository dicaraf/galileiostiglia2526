#include "../include/salvataggio.h"
#include "../include/mappa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ── Formato del file .sav ──────────────────────────────
   [int]  versione
   [int]  id stanza corrente
   [int]  hp, hp_max, attacco, difesa, xp, livello, oro
   [char] nome[MAX_NOME]
   [int]  top inventario
   Per ogni slot inventario (top+1 slot):
       [char]       nome[MAX_NOME]
       [TipoOggetto] tipo
       [int]        valore
   Per ogni stanza (num_stanze):
       [int] visitata
       [int] bloccata_nord/sud/est/ovest
       [int] mostro.vivo, mostro.hp (se mostro != NULL)
   ─────────────────────────────────────────────────────── */

int salva_partita(const Eroe *e, Stanza **stanze, int n)
{
    FILE *f = fopen(PERCORSO_SAVE, "wb");
    if (!f) { perror("Impossibile aprire il file di salvataggio"); return 0; }

    int versione = VERSIONE_SAVE;
    fwrite(&versione, sizeof(int), 1, f);

    int id_corrente = e->stanza_corrente->id;
    fwrite(&id_corrente, sizeof(int), 1, f);

    fwrite(&e->hp,      sizeof(int), 1, f);
    fwrite(&e->hp_max,  sizeof(int), 1, f);
    fwrite(&e->attacco, sizeof(int), 1, f);
    fwrite(&e->difesa,  sizeof(int), 1, f);
    fwrite(&e->xp,      sizeof(int), 1, f);
    fwrite(&e->livello, sizeof(int), 1, f);
    fwrite(&e->oro,     sizeof(int), 1, f);
    fwrite(e->nome,     sizeof(char), MAX_NOME, f);

    int top = e->inventario.top;
    fwrite(&top, sizeof(int), 1, f);
    for (int i = 0; i <= top; i++) {
        const Oggetto *o = e->inventario.slot[i];
        fwrite(o->nome,   sizeof(char),      MAX_NOME, f);
        fwrite(&o->tipo,  sizeof(TipoOggetto), 1,      f);
        fwrite(&o->valore,sizeof(int),         1,      f);
    }

    for (int i = 0; i < n; i++) {
        if (!stanze[i]) continue;
        fwrite(&stanze[i]->visitata,       sizeof(int), 1, f);
        fwrite(&stanze[i]->bloccata_nord,  sizeof(int), 1, f);
        fwrite(&stanze[i]->bloccata_sud,   sizeof(int), 1, f);
        fwrite(&stanze[i]->bloccata_est,   sizeof(int), 1, f);
        fwrite(&stanze[i]->bloccata_ovest, sizeof(int), 1, f);
        int m_vivo = 0, m_hp = 0;
        if (stanze[i]->mostro) {
            m_vivo = stanze[i]->mostro->vivo;
            m_hp   = stanze[i]->mostro->hp;
        }
        fwrite(&m_vivo, sizeof(int), 1, f);
        fwrite(&m_hp,   sizeof(int), 1, f);
    }

    fclose(f);
    printf("Partita salvata con successo!\n");
    return 1;
}

int carica_partita(Eroe *e, Stanza **stanze, int n)
{
    FILE *f = fopen(PERCORSO_SAVE, "rb");
    if (!f) { printf("Nessun salvataggio trovato.\n"); return 0; }

    int versione = 0;
    fread(&versione, sizeof(int), 1, f);
    if (versione != VERSIONE_SAVE) {
        printf("File di salvataggio incompatibile (versione %d).\n", versione);
        fclose(f);
        return 0;
    }

    /* libera inventario corrente */
    for (int i = e->inventario.top; i >= 0; i--)
        free(e->inventario.slot[i]);
    e->inventario.top = -1;

    int id_corrente = 0;
    fread(&id_corrente, sizeof(int), 1, f);

    fread(&e->hp,      sizeof(int), 1, f);
    fread(&e->hp_max,  sizeof(int), 1, f);
    fread(&e->attacco, sizeof(int), 1, f);
    fread(&e->difesa,  sizeof(int), 1, f);
    fread(&e->xp,      sizeof(int), 1, f);
    fread(&e->livello, sizeof(int), 1, f);
    fread(&e->oro,     sizeof(int), 1, f);
    fread(e->nome,     sizeof(char), MAX_NOME, f);

    int top = 0;
    fread(&top, sizeof(int), 1, f);
    for (int i = 0; i <= top; i++) {
        Oggetto *o = calloc(1, sizeof(Oggetto));
        if (!o) { fclose(f); return 0; }
        fread(o->nome,    sizeof(char),      MAX_NOME, f);
        fread(&o->tipo,   sizeof(TipoOggetto), 1,      f);
        fread(&o->valore, sizeof(int),         1,      f);
        e->inventario.slot[i] = o;
    }
    e->inventario.top = top;

    /* ricollega stanza corrente */
    if (id_corrente >= 0 && id_corrente < n && stanze[id_corrente])
        e->stanza_corrente = stanze[id_corrente];

    for (int i = 0; i < n; i++) {
        if (!stanze[i]) continue;
        fread(&stanze[i]->visitata,       sizeof(int), 1, f);
        fread(&stanze[i]->bloccata_nord,  sizeof(int), 1, f);
        fread(&stanze[i]->bloccata_sud,   sizeof(int), 1, f);
        fread(&stanze[i]->bloccata_est,   sizeof(int), 1, f);
        fread(&stanze[i]->bloccata_ovest, sizeof(int), 1, f);
        int m_vivo = 0, m_hp = 0;
        fread(&m_vivo, sizeof(int), 1, f);
        fread(&m_hp,   sizeof(int), 1, f);
        if (stanze[i]->mostro) {
            stanze[i]->mostro->vivo = m_vivo;
            stanze[i]->mostro->hp   = m_hp;
        }
    }

    fclose(f);
    printf("Partita caricata con successo!\n");
    return 1;
}
