#ifndef _TESSERA_H_
#define _TESSERA_H_

#include <stdbool.h>

#include "struttura_dati.h"

// Genera le tessere contenute nella mano del giocatore
void genera_tessere(vect_t *mano_giocatore);
// Ritorna un vettore contenente le coordinate delle posizioni valide
vect_t *calcola_coordinate(matrice_t *piano_gioco, bool orientamento);
// Stampa riga e colonna di ciascuna coordinata
void stampa_coordinate(vect_t *coordinate);
// Preleva una tessera dalla mano del giocatore e inseriscila nel piano di gioco in base alla corrispondenza
void preleva_tessera(matrice_t *piano_gioco, vect_t *mano_giocatore, tessera_t *tessera, coord_t *coordinata, comb_t *risultato);
// Imposta i cardini delle due posizioni da riempire secondo l'orientamento stabilito
void imposta_cardini(matrice_t *piano_gioco, coord_t *coordinata, bool orientamento);
// Ruota la tessera invertendo il valore dei suoi estremi
void ruota_tessera(tessera_t *tessera);
// Incrementa tutti gli estremi presenti sul piano di gioco
void incrementa_estremi(matrice_t *piano_gioco);
// Esegui le opportune operazione nel caso sia stata inserita una tessera speciale 
void funzionalita_aggiuntive(matrice_t *piano_gioco, tessera_t *da_posizionare, comb_t *risultato);
// Calcola il punteggio ottenuto al termine della partita
unsigned int calcola_punteggio(matrice_t *piano_gioco);

#endif
