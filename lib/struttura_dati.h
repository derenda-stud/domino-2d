#ifndef _DATI_H_
#define _DATI_H_

#include <stdio.h>
#include <stdbool.h>

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
// Stampa gli estremi presenti in ogni riga della matrice
void stampa_matrice(matrice_t *matrice);
// Stampa il valore di un estremo in base al cardine
void stampa_estremo(estremo_t estremo);
// Libera la memoria occupata dalla matrice
void libera_matrice(matrice_t *matrice);
// Genera gli estremi delle tessera nella mano del giocatore
void genera_tessere(matrice_t *mano_giocatore);
// Ritorna un vettore contenente tutte le coordinate delle posizioni valide
coord_t *calcola_coordinate(matrice_t *piano_gioco, size_t *posizioni);
// Stampa riga e colonna di ciascuna coordinata
void stampa_coordinate(coord_t *coordinate, size_t posizioni);
// Inserisci in orizzontale una tessera presente nella mano del giocatore sul piano di gioco
void inserimento_orizzontale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t coordinata);
// Inserisci in verticale una tessera presente nella mano del giocatore sul piano di gioco
void inserimento_verticale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t coordinata);
// Incrementa il valore dei cardini perche' corrispondano agli estremi posizionati in verticale
void incrementa_cardini(matrice_t *piano_gioco, coord_t coordinata);

#endif