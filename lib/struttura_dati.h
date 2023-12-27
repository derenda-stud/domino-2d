#ifndef _DATI_H_
#define _DATI_H_

#include <stdio.h>

// Posizione del cursore dove inserire le tessere
typedef struct s_coord {
    unsigned int riga;
    unsigned int colonna;
} coord_t;

typedef struct s_pos {
    coord_t *coordinate;
    unsigned int dimensione;
} pos_t;

// Estremi contenuti dentro le tessere nella mano del giocatore
typedef struct s_tessera {
    unsigned int estremo_sinistro;
    unsigned int estremo_destro;
} tessera_t;

typedef struct s_mano {
    tessera_t *tessere;
    unsigned int dimensione;
} mano_t;

// Ciascuna posizione del piano di gioco contiene un dato
typedef struct s_estremo {
    unsigned int valore;
    char cardine; // Nord, Sud, Est, Ovest
} estremo_t;

// Vettore dinamico con dimensione [righe * colonne]
typedef struct s_piano {
    estremo_t **posizione;
    unsigned int righe;
    unsigned int colonne;
} piano_t;

// Creazione della struttura dati contenente la mano del giocatore
mano_t *crea_mano(unsigned int numero_tessere);
// Genera gli estremi delle tessera nella mano del giocatore
void genera_tessere(mano_t *mano_giocatore);
// Stampa in linea delle tessere nella mano del giocatore
void stampa_mano(mano_t *mano_giocatore);
// Libera la memoria occupata dalla mano del giocatore
void libera_mano(mano_t *mano_giocatore);
// Creazione della struttura dati contenente il piano di gioco
piano_t *crea_piano(unsigned int colonne);
// Aggiungi una nuova riga al piano di gioco
void aggiungi_riga(piano_t *piano_gioco);
// Stampa delle tessere presenti in ogni riga del piano di gioco
void stampa_piano(piano_t *piano_gioco);
// Libera la memoria occupata dal piano di gioco
void libera_piano(piano_t *piano_gioco);

#endif