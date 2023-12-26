#ifndef _MODALITA_INTERATTIVA_H_
#define _MODALITA_INTERATTIVA_H_

#include "struttura_dati.h"

void stampa_turno(mano_t *mano_giocatore, piano_t *piano_gioco);
coord_t cursione_precedente(piano_t *piano_gioco, coord_t successivo);
coord_t cursore_successivo(piano_t *piano_gioco, coord_t precedente);
void stampa_cursori(piano_t *piano_gioco);

#endif