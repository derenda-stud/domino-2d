#ifndef _DATI_H_
#define _DATI_H_

#include "vettore.h"
#include <stdbool.h>

/// @brief Coordinate per ciascuna posizione del piano di gioco
typedef struct s_coord {
    unsigned int riga;      ///< Riga corrispondente al primo indice del piano
    unsigned int colonna;   ///< Colonna corrispondente al secondo indice del piano
} coord_t;

/// @brief Dato contenuto all'interno di ciascuna posizione del piano di gioco
typedef struct s_estremo {
    unsigned int valore;    ///< Valore numero memorizzato
    unsigned int cardine;   ///< Cardine dell'estremo collegato
} estremo_t;

/// @brief Tessere contenute nella mano del giocatore
typedef struct s_tessera {
    unsigned int sinistro;  ///< Primo valore numerico
    unsigned int destro;    ///< Secondo valore numerico
    bool speciale;          ///< Stabilisce se una tessera e' speciale
} tessera_t;

/// @brief Informazioni relative all'inserimento di una tessera
typedef struct s_combinazione {
    coord_t *inserimento;   ///< Puntatore alla coordinata di inserimento
    coord_t *adiacente;     ///< Puntatore alla coordinata dell'estremo adiacente
    bool rotazione;         ///< Stabilisce se sia necessario ruotare la tessera
    bool orientamento;      ///< Stabilisce l'orientamento della tessera da inserire
} comb_t;

/// @brief Matrice dinamica contenente estremi
typedef struct s_matrice {
    estremo_t **posizione;  ///< Puntatore all'estremo in prima posizione
    unsigned int righe;     ///< Numero di righe attualmente occupate
    unsigned int colonne;   ///< Numero di colonne per ciascuna riga
} matrice_t;

/// @brief Creazione di una matrice contenente estremi
/// @param colonne Numero di colonne da memorizzare
/// @return Il puntatore alla matrice creata
matrice_t *crea_matrice(size_t colonne);

/// @brief Aggiungi una nuova riga alla matrice
/// @param matrice Puntatore alla matrice da ingrandire
void aggiungi_riga(matrice_t *matrice);

/// @brief Libera la memoria occupata dalla matrice
/// @param matrice Puntatore alla matrice da liberare
void libera_matrice(matrice_t *matrice);

/// @brief Stampa gli estremi presenti in ogni riga del piano di gioco
/// @param piano_gioco Puntatore alla matrice da stampare
void stampa_piano(matrice_t *piano_gioco);

/// @brief Stampa gli estremi presenti nella mano del giocatore
/// @param mano_giocatore Puntatore al vettore di tessere da stampare
void stampa_mano(vect_t *mano_giocatore);

/// @brief Stampa una riga di estremi entro un limite stabilito
/// @param estremi Puntatore alla riga corrente da stampare
/// @param minimo Colonna minima dell'intervallo di stampa
/// @param massimo Colonna massima dell'intervallo di stampa
void stampa_estremi(estremo_t *estremi, size_t minimo, size_t massimo);

/// @brief Creazione ed allocazione della memoria di una combinazione
/// @param inserimento Coordinata iniziale di inserimento
/// @param orientamento Valore iniziale dell'orientamento
/// @return Il puntatore alla combinazione creata
comb_t *crea_combinazione(coord_t inserimento, bool orientamento);

/// @brief Inizializza i parametri essenziali di una combinazione
/// @param combinazione Puntatore alla combinazione da inizializzare
void inizializza_combinazione(comb_t *combinazione);

/// @brief Libera la memoria occupata dalla combinazione
/// @param combinazione Puntatore alla combinazione da liberare
void libera_combinazione(comb_t *combinazione);

#endif
