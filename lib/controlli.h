#ifndef _CONTROLLI_H_
#define _CONTROLLI_H_

#include <stdbool.h>

#include "tessera.h"

// Chiedi all'utente il numero di tessere con cui vuole giocare
unsigned int inserisci_numero_tessere();
// Chiedi all'utente un numero compreso tra un estremo minimo e massimo
unsigned int inserisci_numero_compreso(char *messaggio, unsigned int minimo, unsigned int massimo);
// Valuta se una posizione sul piano di gioco e' valida per l'inserimento di una tessera
bool posizione_valida(matrice_t *piano_gioco, estremo_t *da_confrontare, coord_t coordinata, bool orientamento);
// Sposta l'indice delle coordinate alla posizione precedente/successiva
unsigned int sposta_indice(size_t posizioni, unsigned int attuale, int spostamento);
// Controlla se sia possibile aggiungere una tessera al piano di gioco
bool mosse_disponibili(matrice_t *mano_giocatore, matrice_t *piano_gioco);
// Controlla che la tessera combaci nella posizione indicata
bool mossa_legale(matrice_t *mano_giocatore, matrice_t *piano_gioco, size_t indice, coord_t coordinata);

#endif