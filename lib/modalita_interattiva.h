#ifndef _MODALITA_INTERATTIVA_H_
#define _MODALITA_INTERATTIVA_H_

#include "struttura_dati.h"

// Stampa le operazioni eseguite durante il turno del giocatore
void stampa_turno(matrice_t *mano_giocatore, matrice_t *piano_gioco);
// Menu che permette di inserire la prossima mossa da effettuare
void inserisci_scelta(matrice_t *mano_giocatore, matrice_t *piano_gioco);
// Seleziona la posizione della tessera da inserire
void seleziona_tessera(matrice_t *mano_giocatore, matrice_t *piano_gioco);
// Ritorna la tessera presente ad un particolare indice
estremo_t *inserisci_indice(matrice_t *mano_giocatore, char *azione);

#endif