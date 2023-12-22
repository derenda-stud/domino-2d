#ifndef _DATI_H_
#define _DATI_H_

#include <stdio.h>

typedef struct s_dato {
    unsigned int estremo;
    unsigned int cardine;
} dato;

// Genera gli estremi delle tessera nella mano del giocatore
void genera_tessere(unsigned int *mano_giocatore, size_t dimensione);

#endif