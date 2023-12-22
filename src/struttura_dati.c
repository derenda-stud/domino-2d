#include <stdlib.h>

#include "../lib/struttura_dati.h"

void genera_tessere(unsigned int *mano_giocatore, size_t dimensione) {
    // Per ciascuna posizione nella mano
    for(size_t i=0; i<dimensione; i++) {
        // Inizializza una tessera con estremi casuali
        mano_giocatore[i] = rand() % 6 + 1;
    }
}