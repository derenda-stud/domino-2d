#ifndef _CONTROLLI_H_
#define _CONTROLLI_H_

#include <stdbool.h>

#include "tessera.h"

// Chiedi all'utente il numero di tessere con cui vuole giocare
unsigned int inserisci_numero_tessere();
// Chiedi all'utente un numero compreso tra un estremo minimo e massimo
unsigned int inserisci_numero_compreso(char *messaggio, unsigned int minimo, unsigned int massimo);
// Valuta se una posizione sul piano di gioco permette l'inserimento di una tessera
bool posizione_valida(matrice_t *piano_gioco, coord_t coordinata, bool orientamento);
// Scorri in avanti le colonne del piano di gioco per trovare la prima posizione utile
unsigned int prima_posizione(matrice_t *piano_gioco, unsigned int riga);
// Scorri a ritroso le colonne del piano di gioco per trovare l'ultima posizione utile
unsigned int ultima_posizione(matrice_t *piano_gioco, unsigned int riga);
// Sposta l'indice delle coordinate alla posizione precedente/successiva
unsigned int sposta_indice(size_t dimensione, unsigned int attuale, int spostamento);
// Controlla se sia possibile aggiungere una tessera al piano di gioco
bool mosse_disponibili(vect_t *mano_giocatore, matrice_t *piano_gioco);
// Controlla che esista una mossa legale tra le posizioni valide
int mossa_legale(matrice_t *piano_gioco, coord_t *coordinata, tessera_t *tessera, comb_t *risultato);
// Controlla se la tessera da posizionare abbia almeno un estremo con una corrispondenza
int estremi_corrispondono(matrice_t *piano_gioco, coord_t *coordinata, tessera_t *tessera, comb_t *risultato);

#endif