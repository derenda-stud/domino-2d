#ifndef _MODALITA_INTERATTIVA_H_
#define _MODALITA_INTERATTIVA_H_

#include "struttura_dati.h"

/// @brief Stampa le operazioni eseguite durante il turno del giocatore
/// @param mano_giocatore Vettore contenente le tessere nella mano del giocatore
/// @param piano_gioco Matrice contenente gli estremi del piano di gioco
void stampa_turno(vect_t *mano_giocatore, matrice_t *piano_gioco);

/// @brief Seleziona la posizione della tessera da inserire
/// @param mano_giocatore Vettore dal quale selezionare la tessera
/// @param piano_gioco Matrice nella quale inserire la tessera selezionata
void seleziona_tessera(vect_t *mano_giocatore, matrice_t *piano_gioco);

/// @brief Menu per selezionare la coordinata di inserimento della tessera
/// @param coordinate Vettore di coordinate possibili per l'inserimento
/// @return Il puntatore alla coordinata selezionata
coord_t *seleziona_posizione(vect_t *coordinate);

#endif
