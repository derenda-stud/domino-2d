#ifndef _MODALITA_INTERATTIVA_H_
#define _MODALITA_INTERATTIVA_H_

#include "struttura_dati.h"

// Stampa le operazioni eseguite durante il turno del giocatore
void stampa_turno(vect_t *mano_giocatore, matrice_t *piano_gioco);
// Menu che permette di inserire la prossima mossa da effettuare
void inserisci_scelta(vect_t *mano_giocatore, matrice_t *piano_gioco);
// Ritorna la tessera presente ad un particolare indice
tessera_t *inserisci_indice(vect_t *mano_giocatore, char *azione);
// Seleziona la posizione della tessera da inserire
void seleziona_tessera(vect_t *mano_giocatore, matrice_t *piano_gioco);
// Menu per selezionare dove posizionare la tessera
coord_t *seleziona_posizione(vect_t *coordinate);

#endif