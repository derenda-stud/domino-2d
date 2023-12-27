#include "../lib/controlli.h"

bool posizione_valida(piano_t *piano_gioco, unsigned riga, unsigned int colonna, bool orientamento) {
    if(colonna < 1 || colonna + 2 >= piano_gioco->colonne) return false;
    if(!piano_gioco->posizione[riga][colonna - 1].cardine || !piano_gioco->posizione[riga][colonna + 2].cardine) return false;
    // In base all'orientamento della tessera
    if(orientamento) {
        // Posizioni valide in orizzontale
        if(piano_gioco->posizione[riga][colonna].cardine || piano_gioco->posizione[riga][colonna + 1].cardine) return false;
    } else {
        // Posizioni valide in verticale
        if(piano_gioco->posizione[riga][colonna].cardine || piano_gioco->posizione[riga + 1][colonna].cardine) return false;
    }
    // Dopo aver effettuato tutti i controlli, la posizione indicata e' valida
    return true;
    /*             x-1    x      x+1   x+2
                    attuale
    Orizzontale -> ... [vuoto | vuoto] ...
y   Verticale   -> ... [vuoto] ...         in entrambi i casi devo avere almeno un collegamento
y+1                    [vuoto]
    */
}

bool mosse_disponibili(piano_t *piano_gioco, mano_t *mano_giocatore, pos_t *posizioni) {
    // Termina la partita dopo aver esaurite le tessere
    if(mano_giocatore->dimensione == 0) return false;
    // Altrimenti per ogni tessera presente nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->dimensione; i++) {
        // Per ogni posizione valida
        for(size_t j=0; j<posizioni->dimensione; j++) {
            // Controlla se la tessera combacia in quella posizione
            if(mossa_legale(piano_gioco, mano_giocatore->tessere[i], posizioni->coordinate[j])) {
                return true;
            }
        }
    }
    // Non ho trovato nessuna mossa legale
    return false;
}

bool mossa_legale(piano_t *piano_gioco, tessera_t da_confrontare, coord_t coordinata) {
    // Quando il piano di gioco e' vuoto non sono necessari controlli
    if(piano_gioco == NULL) return true;
    return false;
}

int estremi_corrispondono() {
    return 0;
}