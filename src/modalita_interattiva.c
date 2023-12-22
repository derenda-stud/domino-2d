#include "../lib/modalita_interattiva.h"

void stampa_mano(unsigned int *mano_giocatore, size_t dimensione) {
    // Stampa gli estremi del piano in coppie da 2
    for(size_t i=0; i<dimensione; i++) {
        if(i % 2 == 0) {
            printf("[%d|", mano_giocatore[i]);
        } else {
            printf("%d]", mano_giocatore[i]);
        }
    }
    printf("\n");
}