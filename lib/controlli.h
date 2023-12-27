#ifndef _CONTROLLI_H_
#define _CONTROLLI_H_

#include <stdbool.h>

#include "struttura_dati.h"

bool posizione_valida(piano_t *piano_gioco, unsigned int riga, unsigned int colonna, bool orientamento);
bool mosse_disponibili(piano_t *piano_gioco, mano_t *mano_giocatore, pos_t *posizioni);
bool mossa_legale(piano_t *piano_gioco, tessera_t da_confrontare, coord_t coordinata);
int estremi_corrispondono();

#endif