#include <stdlib.h>

#include "../lib/modalita_interattiva.h"

void genera_tessere(unsigned int *mano_giocatore, size_t dimensione) {
    // Per ciascuna posizione nella mano
    for(size_t i=0; i<dimensione; i++) {
        // Inizializza una tessera con estremi casuali
        mano_giocatore[i] = rand() % 6 + 1;
    }
}

void stampa_mano(unsigned int *mano_giocatore, size_t dimensione) {
    // Stampa gli estremi del piano in coppie da 2
    for(size_t i=0; i<dimensione; i++) {
        if(i % 2 == 0) {
            printf("[%d|", mano_giocatore[i]);
        } else {
            printf("%d] ", mano_giocatore[i]);
        }
    }
    printf("\n");
    // Stampa gli indici per ogni tessera
    for(size_t i=0; i<dimensione/2; i++) {
        printf("  %d   ", i);
    }
    printf("\n");
}