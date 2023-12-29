#ifndef _MODALITA_INTERATTIVA_H_
#define _MODALITA_INTERATTIVA_H_

#include "struttura_dati.h"

void stampa_turno(matrice_t *mano_giocatore, matrice_t *piano_gioco);
coord_t *calcola_coordinate(matrice_t *piano_gioco);
void stampa_coordinate(coord_t *coordinate);

#endif