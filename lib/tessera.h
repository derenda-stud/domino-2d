#ifndef _TESSERA_H_
#define _TESSERA_H_

#include <stdbool.h>

#include "struttura_dati.h"

/// @brief Genera le tessere contenute nella mano del giocatore
/// @param mano_giocatore Vettore nel quale effettuare gli inserimenti
void genera_tessere(vect_t *mano_giocatore);

/// @brief Ritorna un vettore di coordinate per ciascuna posizione valida
/// @param piano_gioco Matrice dalla quale calcolare la prima ed ultima posizione valida
/// @param orientamento Orientamento delle posizioni in orizzontale/verticale
/// @return Un vettore contenente le coordinate calcolate
/// @note La liberazione della memoria e' gestita dal chiamante
vect_t *calcola_coordinate(matrice_t *piano_gioco, bool orientamento);

/// @brief Stampa riga e colonna di ciascuna coordinata
/// @param coordinate Vettore di coordinate di inserimento
void stampa_coordinate(vect_t *coordinate);

/// @brief Preleva una tessera dalla mano del giocatore e inseriscila nel piano di gioco in base alla corrispondenza
/// @param piano_gioco Matrice dalla quale selezionare le due posizioni di inserimento
/// @param mano_giocatore Vettore dal quale viene prelevata la tessera
/// @param tessera Puntatore alla tessera da posizionare sul piano di gioco
/// @param coordinata Coordinata di inserimento relativa all'estremo sinistro
/// @param risultato Struttura dati contenente diverse informazioni per l'inserimento
void preleva_tessera(matrice_t *piano_gioco, vect_t *mano_giocatore, tessera_t *tessera, coord_t *coordinata, comb_t *risultato);

/// @brief Imposta i cardini delle due posizioni da riempire secondo l'orientamento indicato
/// @param piano_gioco Matrice nella quale vengono modificati i due cardini
/// @param coordinata Coordinata di inserimento relativa all'estremo sinistro
/// @param orientamento Orientamento orizzontale/verticale della tessera posizionata
void imposta_cardini(matrice_t *piano_gioco, coord_t *coordinata, bool orientamento);

/// @brief Ruota la tessera invertendo il valore dei suoi estremi
/// @param tessera Puntatore alla tessera da ruotare
void ruota_tessera(tessera_t *tessera);

/// @brief Incrementa tutti gli estremi presenti sul piano di gioco
/// @param piano_gioco Matrice contenente gli estremi da incrementare
void incrementa_estremi(matrice_t *piano_gioco);

/// @brief Esegui le opportune operazioni nel caso sia stata inserita una tessera speciale 
/// @param piano_gioco Matrice dalla quale vengono analizzate le due posizioni di inserimento
/// @param da_posizionare Puntatore alla tessera speciale da posizionare sul piano
/// @param risultato Struttura dati contenente le diverse informazioni necessarie all'inserimento
void funzionalita_aggiuntive(matrice_t *piano_gioco, tessera_t *da_posizionare, comb_t *risultato);

/// @brief Calcola il punteggio ottenuto al termine della partita
/// @param piano_gioco Matrice dalla quale leggere i valori degli estremi
/// @return Il punteggio calcolato sulla base di ciascun estremo
unsigned int calcola_punteggio(matrice_t *piano_gioco);

#endif
