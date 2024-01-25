#ifndef _CONTROLLI_H_
#define _CONTROLLI_H_

#include <stdbool.h>

#include "tessera.h"

/// @brief Chiedi all'utente il numero di tessere con cui vuole giocare
/// @return Il numero di tessere richiesto
unsigned int inserisci_numero_tessere(void);

/// @brief Chiedi all'utente un numero compreso tra un estremo minimo e massimo
/// @param messaggio Messaggio da visualizzare all'utente durante l'inserimento
/// @param minimo Numero minimo dell'intervallo
/// @param massimo Numero massimo dell'intervallo
/// @return Il numero inserito nell'intervallo prefissato
unsigned int inserisci_numero_compreso(char *messaggio, unsigned int minimo, unsigned int massimo);

/// @brief Valuta se una posizione sul piano di gioco permette l'inserimento di una tessera
/// @param piano_gioco Matrice dalla quale reperire i due estremi di inserimento
/// @param coordinata Coordinata attualmente selezionata
/// @param orientamento Orientamento corrispondente ad orizzontale/verticale
/// @return La validita' delle due posizioni analizzate
bool posizione_valida(matrice_t *piano_gioco, coord_t coordinata, bool orientamento);

/// @brief Scorri in avanti le colonne del piano di gioco per trovare la prima posizione utile
/// @param piano_gioco Matrice nella quale scorrere le colonne
/// @param riga Riga nella quale cercare la prima posizione utile
/// @return L'indice della colonna corrispondente alla prima posizione utile
unsigned int prima_posizione(matrice_t *piano_gioco, unsigned int riga);

/// @brief Scorri a ritroso le colonne del piano di gioco per trovare l'ultima posizione utile
/// @param piano_gioco Matrice nella quale scorrere le colonne
/// @param riga Riga nella quale cercare l'ultima posizione utile
/// @return L'indice della colonna corrispondente all'ultima posizione utile
unsigned int ultima_posizione(matrice_t *piano_gioco, unsigned int riga);

/// @brief Sposta l'indice delle coordinate alla posizione precedente/successiva
/// @param dimensione Dimensione del vettore di coordinate
/// @param attuale Indice del vettore attuale selezionato
/// @param spostamento Valore che indica lo spostamento nel vettore (+1/-1)
/// @return Indice selezionato alla fine dell'operazione
unsigned int sposta_indice(size_t dimensione, unsigned int attuale, int spostamento);

/// @brief Controlla se sia possibile aggiungere una tessera al piano di gioco
/// @param mano_giocatore Vettore dal quale estrarre le tessere per controllarne la validita' 
/// @param piano_gioco Matrice nella quale controllare gli estremi e le posizioni valide
/// @return Vero se e' stata trovata anche sola una mossa disponibile, falso altrimenti
bool mosse_disponibili(vect_t *mano_giocatore, matrice_t *piano_gioco);

/// @brief Controlla che esista una mossa legale tra le posizioni valide
/// @param piano_gioco Matrice dalla quale ricavare le due posizioni di inserimento 
/// @param coordinata Coordinata di inserimento relativa all'estremo sinistro
/// @param tessera Puntatore alla tessera da inserire nel piano di gioco
/// @param risultato Struttura dati contenente le diverse informazioni necessarie all'inserimento
/// @return La legalita' della mossa selezionata
bool mossa_legale(matrice_t *piano_gioco, coord_t *coordinata, tessera_t *tessera, comb_t *risultato);

/// @brief Controlla se la tessera da posizionare corrisponda correttamente sul piano di gioco
/// @param piano_gioco Matrice dalla quale ricavare l'estremo sinistro di riferimento
/// @param coordinata Coordinata di inserimento della tessera
/// @param tessera Puntatore alla tessera da inserire sul piano di gioco
/// @param risultato Struttura dati contenente le diverse informazioni necessarie all'inserimento
/// @return La modalita' di inserimento della tessera (0 = non corrisponde, 1 = mantieni ordine, 2 = ruota tessera)
int estremi_corrispondono(matrice_t *piano_gioco, coord_t coordinata, tessera_t tessera, comb_t *risultato);

#endif
