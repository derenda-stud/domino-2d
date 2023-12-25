#include <stdlib.h>
#include <stdbool.h>

#include "../lib/modalita_interattiva.h"

void stampa_turno(mano_t *mano_giocatore, piano_t *piano_gioco) {
    // Stampa per la prima volta le tessere della mano del giocatore
    stampa_mano(mano_giocatore);
}