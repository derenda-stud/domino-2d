#ifndef _AI_H_
#define _AI_H_

#include "struttura_dati.h"

// Esecuzione del migliore algoritmo AI stampando ciascuna azione
void esegui_algoritmo(matrice_t *piano_gioco, vect_t *mano_giocatore);
// Restituisci la prima tessera con una corrispondenza
tessera_t *first_match(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato);
tessera_t *most_frequent(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato);
bool sostituisci_frequenze(unsigned int *frequenze, tessera_t *corrente, tessera_t *migliore);

#endif