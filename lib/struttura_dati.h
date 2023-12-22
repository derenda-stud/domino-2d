#ifndef _DATI_H_
#define _DATI_H_

#include <stdio.h>

typedef struct s_dato {
    unsigned int estremo;
    unsigned int cardine;
} dato;

// Stampa delle tessere presenti in ogni riga del piano di gioco
void stampa_piano(dato **piano_gioco, size_t righe, size_t colonne);

#endif