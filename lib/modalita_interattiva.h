#ifndef _MODALITA_INTERATTIVA_H_
#define _MODALITA_INTERATTIVA_H_

#include "struttura_dati.h"

// Stampa le operazioni eseguite durante il turno del giocatore
void stampa_turno(vect_t *mano_giocatore, matrice_t *piano_gioco);
// Seleziona la posizione della tessera da inserire
void seleziona_tessera(vect_t *mano_giocatore, matrice_t *piano_gioco);
// Menu per selezionare dove posizionare la tessera
coord_t *seleziona_posizione(vect_t *coordinate);

#endif
