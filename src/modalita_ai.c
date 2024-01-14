#include "../lib/modalita_ai.h"

#include "tessera.h"

estremo_t *first_match(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato) {
    unsigned int corrispondenza;
    // Per ciascuna tessera nella mano del giocatore
    for (size_t tessera = 0; tessera < mano_giocatore->dimensione; tessera++) {
        // Per ciascuna riga del piano di gioco
        for (size_t riga = 0; riga < piano_gioco->righe; riga++) {
            // Calcola la prima ed ultima posizione utile
            unsigned int inizio = prima_posizione(piano_gioco, riga);
            unsigned int fine = ultima_posizione(piano_gioco, riga);
            // Scorri tutte le posizioni utili
            for (size_t colonna = inizio; colonna <= fine; colonna++) {
                // Nella posizione corrente
                coord_t corrente = {riga, colonna};
                if (/* e' possibile posizionarla orizzontale/verticale + ordinata/girata? */) {
                    // Modifica i parametri necessari a posizionare la tessera
                    risultato->posizione = corrente;
                    risultato->rotazione = corrispondenza - 1;
                    // Ritorna l'indice della tessera trovata
                    return elemento_ad_indice(mano_giocatore, tessera);
                }
            }
        }
    }
    // Non ho trovato nessuna tessera da posizionare
    return NULL;
}