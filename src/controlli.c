#include "../lib/controlli.h"

bool posizione_valida(matrice_t *piano_gioco, unsigned int riga, unsigned int colonna, bool orizzontale) {
    // Controlla che la posizione attuale sia libera
    if(piano_gioco->posizione[riga][colonna].cardine) return false;
    // Controlla che rientri nel limite sinistro e che abbia un estremo collegato
    if(colonna > 0 && piano_gioco->posizione[riga][colonna - 1].cardine) return true;
    // Controlla che rientri nel limite destro e che abbia un estremo collegato
    if(colonna < piano_gioco->colonne - (orizzontale + 1) && piano_gioco->posizione[riga][colonna + orizzontale + 1].cardine) return true;
    // Controlla che la posizione adiacente/sottostante sia libera
    if(piano_gioco->posizione[riga + !orizzontale][colonna + orizzontale].cardine) return false;
    // Per tutti i casi rimanenti la posizione non risulta valida
    return false;
}

bool mosse_disponibili(matrice_t *mano_giocatore, matrice_t *piano_gioco, coord_t *coordinate, size_t posizioni) {
    // Termina la partita dopo aver esaurite le tessere
    if(mano_giocatore->colonne == 0) return false;
    // Altrimenti per ogni tessera presente nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->colonne; i++) {
        // Per ogni posizione valida
        for(size_t j=0; j<posizioni; j++) {
            // Controlla se la tessera combacia in quella posizione
            if(mossa_legale(mano_giocatore, piano_gioco, i, coordinate[j])) {
                return true;
            }
        }
    }
    // Non ho trovato nessuna mossa legale
    return false;
}

bool mossa_legale(matrice_t *mano_giocatore, matrice_t *piano_gioco, size_t indice, coord_t coordinata) {
    return true;
}