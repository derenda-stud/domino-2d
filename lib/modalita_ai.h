#ifndef _AI_H_
#define _AI_H_

#include "struttura_dati.h"

/// @brief Esecuzione del migliore algoritmo AI stampando ciascuna azione
/// @param piano_gioco Matrice contenente gli estremi del piano di gioco
/// @param mano_giocatore Vettore contenente le tessere nella mano del giocatore
void esegui_algoritmo(matrice_t *piano_gioco, vect_t *mano_giocatore);

/// @brief Restituisci la prima tessera con una corrispondenza
/// @param piano_gioco Matrice dalla quale ricavare ciasun estremo e posizione valida
/// @param mano_giocatore Vettore per scorrere le tessere del giocatore
/// @param risultato Struttura dati contenente le diverse informazioni necessarie all'inserimento
/// @return Il puntatore alla tessera da posizionare (anche nullo)
tessera_t *first_match(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato);

#endif
