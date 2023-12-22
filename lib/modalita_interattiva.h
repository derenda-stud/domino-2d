#ifndef _MODALITA_INTERATTIVA_H_
#define _MODALITA_INTERATTIVA_H_

#include "struttura_dati.h"

// Genera gli estremi delle tessera nella mano del giocatore
void genera_tessere(unsigned int *mano_giocatore, size_t dimensione);
// Stampa in linea delle tessere nella mano del giocatore
void stampa_mano(unsigned int *mano_giocatore, size_t dimensione);

#endif