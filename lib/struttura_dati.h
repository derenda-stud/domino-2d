#ifndef _DATI_H_
#define _DATI_H_

#include <stdio.h>

// Ciascuna posizione del piano di gioco contiene un dato
typedef struct s_dato {
    unsigned int estremo;
    char cardine; // Nord, Sud, Est, Ovest
} dato_t;

// Vettore dinamico con dimensione [righe * colonne]
typedef struct s_piano {
    dato_t **posizione;
    unsigned int righe;
    unsigned int colonne;
} piano_t;

// Creazione della struttura dati contenente il piano di gioco
piano_t *crea_piano(unsigned int colonne);
// Aggiungi una nuova riga al piano di gioco
void aggiungi_riga(piano_t *piano_gioco);
// Stampa delle tessere presenti in ogni riga del piano di gioco
void stampa_piano(piano_t *piano_gioco);
// Libera la memoria occupata dal piano di gioco
void libera_piano(piano_t *piano_gioco);

#endif