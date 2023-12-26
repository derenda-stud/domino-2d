#include "../lib/controlli.h"

bool posizione_valida(piano_t *piano_gioco, unsigned int riga, unsigned int colonna) {
    // Inserimento a sinistra quando l'indice attuale e' vuoto e il successivo presenta un estremo
    if(!piano_gioco->posizione[riga][colonna].cardine && piano_gioco->posizione[riga][colonna + 1].cardine) {
        return true;
    }
    // Inserimento a destra quando il precedente presenta un estremo e il successivo e' vuoto
    if(colonna != 0 && piano_gioco->posizione[riga][colonna - 1].cardine && !piano_gioco->posizione[riga][colonna].cardine) {
        return true;
    }
    // La posizione indicata non e' valida
    return false;
}