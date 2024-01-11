#ifndef _TESSERA_H_
#define _TESSERA_H_

#include <stdbool.h>

#include "struttura_dati.h"

// Genera gli estremi contenuti nella mano del giocatore
void genera_estremi(vect_t *mano_giocatore);
// Ritorna un vettore contenente le coordinate delle posizioni valide
vect_t *calcola_coordinate(matrice_t *piano_gioco, estremo_t *da_confrontare, bool orientamento);
// Stampa riga e colonna di ciascuna coordinata
void stampa_coordinate(vect_t *coordinate);
// Inserisci in orizzontale una tessera presente nella mano del giocatore sul piano di gioco
void inserimento_orizzontale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t *coordinata);
// Inserisci in verticale una tessera presente nella mano del giocatore sul piano di gioco
void inserimento_verticale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t *coordinata);
// Incrementa il valore dei cardini perche' corrispondano agli estremi posizionati in verticale
void incrementa_cardini(matrice_t *piano_gioco, coord_t *coordinata);

#endif