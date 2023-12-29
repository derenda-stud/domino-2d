#ifndef _CONTROLLI_H_
#define _CONTROLLI_H_

#include <stdbool.h>

#include "struttura_dati.h"

bool posizione_valida(matrice_t *piano_gioco, unsigned int riga, unsigned int colonna, bool orientamento);
bool mosse_disponibili(matrice_t *mano_giocatore, matrice_t *piano_gioco);

#endif