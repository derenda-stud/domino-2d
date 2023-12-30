#ifndef _CONTROLLI_H_
#define _CONTROLLI_H_

#include <stdbool.h>

#include "struttura_dati.h"

// Valuta se una posizione sul piano di gioco e' valida per l'inserimento di una tessera
bool posizione_valida(matrice_t *piano_gioco, unsigned int riga, unsigned int colonna, bool orizzontale);
// Controlla se sia possibile aggiungere una tessera al piano di gioco
bool mosse_disponibili(matrice_t *mano_giocatore, matrice_t *piano_gioco, coord_t *coordinate, size_t posizioni);
// Controlla che la tessera combaci nella posizione indicata
bool mossa_legale(matrice_t *mano_giocatore, matrice_t *piano_gioco, size_t indice, coord_t coordinata);

#endif