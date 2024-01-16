#ifndef _DATI_H_
#define _DATI_H_

#include "vettore.h"

// Coordinate corrispondenti del piano di gioco
typedef struct s_coord {
    unsigned int riga;
    unsigned int colonna;
} coord_t;

// Ciascuna posizione del piano di gioco contiene un dato
typedef struct s_estremo {
    unsigned int valore;
    unsigned int cardine;
} estremo_t;

// Tessere contenute nella mano del giocatore
typedef struct s_tessera {
    unsigned int sinistro;
    unsigned int destro;
} tessera_t;

// Vettore dinamico con dimensione [righe * colonne]
typedef struct s_matrice {
    estremo_t **posizione;
    unsigned int righe;
    unsigned int colonne;
} matrice_t;

// Creazione di una matrice contenente estremi
matrice_t *crea_matrice(size_t colonne);
// Aggiungi una nuova riga alla matrice
void aggiungi_riga(matrice_t *matrice);
// Libera la memoria occupata dalla matrice
void libera_matrice(matrice_t *matrice);
// Stampa gli estremi presenti in ogni riga del piano di gioco
void stampa_piano(matrice_t *piano_gioco);
// Stampa gli estremi presenti nella mano del giocatore
void stampa_mano(vect_t *mano_giocatore);
// Stampa il valore di un estremo in base al cardine
void stampa_estremi(estremo_t *estremi, size_t dimensione);

#endif