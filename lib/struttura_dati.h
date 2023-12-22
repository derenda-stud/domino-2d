#ifndef _DATI_H_
#define _DATI_H_

#include <stdio.h>

typedef struct s_dato {
    unsigned int estremo;
    unsigned int cardine;
} dato;

// Creazione della struttura dati contenente il piano di gioco
dato **crea_piano(size_t righe, size_t colonne);
// Aggiungi una nuova riga al piano di gioco
void aggiungi_riga(dato **piano_gioco, size_t righe, size_t colonne);
// Stampa delle tessere presenti in ogni riga del piano di gioco
void stampa_piano(dato **piano_gioco, size_t righe, size_t colonne);
// Libera la memoria occupata dal piano di gioco
void libera_piano(dato **piano_gioco, size_t righe);

#endif