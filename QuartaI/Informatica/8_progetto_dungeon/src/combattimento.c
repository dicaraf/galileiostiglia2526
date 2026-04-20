#include "../include/combattimento.h"
#include "../include/eroe.h"
#include <stdio.h>
#include <stdlib.h>

int calcola_danno(int attacco, int difesa)
{
    int danno = (rand() % attacco) + 1 - difesa;
    return (danno < 1) ? 1 : danno;   /* minimo 1 danno */
}

int combatti(Eroe *e, Mostro *m)
{
    if (!m || !m->vivo) {
        printf("Non c'e' nessun mostro da combattere qui.\n");
        return 1;
    }

    printf("\n╔══════════════════════════════╗\n");
    printf("║  COMBATTIMENTO INIZIATO!      ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║  %s vs %s\n", e->nome, m->nome);
    printf("╚══════════════════════════════╝\n");

    int turno = 1;
    while (e->hp > 0 && m->hp > 0) {
        printf("\n── Turno %d ──\n", turno++);

        /* turno eroe */
        int d_eroe = calcola_danno(e->attacco, m->difesa);
        m->hp -= d_eroe;
        if (m->hp < 0) m->hp = 0;
        printf("  %s colpisce %s per %d danni. (HP mostro: %d/%d)\n",
               e->nome, m->nome, d_eroe, m->hp, m->hp_max);

        if (m->hp <= 0) break;

        /* turno mostro */
        int d_mostro = calcola_danno(m->attacco, e->difesa);
        e->hp -= d_mostro;
        if (e->hp < 0) e->hp = 0;
        printf("  %s colpisce %s per %d danni. (HP eroe: %d/%d)\n",
               m->nome, e->nome, d_mostro, e->hp, e->hp_max);
    }

    if (m->hp <= 0) {
        m->vivo = 0;
        printf("\n*** Hai sconfitto %s! ***\n", m->nome);
        printf("    Guadagni: %d XP, %d oro\n", m->xp_ricompensa, m->oro_ricompensa);
        e->xp  += m->xp_ricompensa;
        e->oro += m->oro_ricompensa;
        controlla_livello(e);
        return 1;
    }

    printf("\n*** Sei stato sconfitto da %s... ***\n", m->nome);
    return 0;
}
