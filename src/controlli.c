#include "../lib/controlli.h"

bool posizione_valida(piano_t *piano_gioco, unsigned int riga, unsigned int colonna, bool orientamento) {
    // Controlla che la posizione attuale sia libera
    if(piano_gioco->posizione[riga][colonna].cardine) return false;
    // Per le tessere posizionate in orizzontale
    if(orientamento) {
        // Controlla che la posizione adiacente sia libera
        if(piano_gioco->posizione[riga][colonna + 1].cardine) return false;
    // Altrimenti per quelle posizionate in verticale
    } else {
        // Controlla di rientrare nella riga e che la posizione sottostante sia libera
        if(riga + 1 >= piano_gioco->righe || piano_gioco->posizione[riga + 1][colonna].cardine) return false;
    }
    // Controlla che rientri nel limite sinistro e che abbia un estremo collegato
    if(colonna > 0 && piano_gioco->posizione[riga][colonna - 1].cardine) return true;
    // Controlla che rientri nel limite destro e che abbia un estremo collegato
    if(colonna < piano_gioco->colonne - (orientamento + 1) && piano_gioco->posizione[riga][colonna + orientamento + 1].cardine) return true;
    // Per tutti i casi rimanenti la posizione non risulta valida
    return false;
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