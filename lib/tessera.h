#ifndef _TESSERA_H_
#define _TESSERA_H_

#include <stdbool.h>

#include "struttura_dati.h"

// Genera le tessere contenute nella mano del giocatore
void genera_tessere(vect_t *mano_giocatore);
// Ritorna un vettore contenente le coordinate delle posizioni valide
vect_t *calcola_coordinate(matrice_t *piano_gioco, bool orientamento);
// Scorri in avanti le colonne del piano di gioco per trovare la prima posizione utile
unsigned int prima_posizione(matrice_t *piano_gioco, unsigned int riga);
// Scorri a ritroso le colonne del piano di gioco per trovare l'ultima posizione utile
unsigned int ultima_posizione(matrice_t *piano_gioco, unsigned int riga);
// Stampa riga e colonna di ciascuna coordinata
void stampa_coordinate(vect_t *coordinate);
// Preleva una tessera dalla mano del giocatore e inseriscila nel piano di gioco seguendo le indicazioni
void preleva_tessera(matrice_t *piano_gioco, vect_t *mano_giocatore, size_t indice, coord_t *coordinata, bool orientamento);
// Imposta i cardini delle due posizioni da riempire secondo l'orientamento stabilito
void imposta_cardini(matrice_t *piano_gioco, coord_t *coordinata, bool orientamento);
// Ruota la tessera presente ad un determinato indice
void ruota_tessera(vect_t *mano_giocatore, size_t indice);

#endif