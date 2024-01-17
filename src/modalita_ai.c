#include "../lib/modalita_ai.h"

#include "tessera.h"

tessera_t *first_match(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato) {
    do {
        // Calcola tutte le coordinate in cui e' possibile posizionare una tessera
        vect_t *coordinate = calcola_coordinate(piano_gioco, risultato->orientamento);
        // Per ciascuna tessera normale nella mano del giocatore
        for (size_t i=0; i < mano_giocatore->dimensione - risultato->speciali; i++) {
            // Ricava l'indirizzo della tessera da controllare
            tessera_t *tessera = elemento_ad_indice(mano_giocatore, tessera);
            // Se una delle posizioni fornite permette l'inserimento della tessera
            if ((risultato->rotazione = mossa_legale(piano_gioco, coordinate, tessera, risultato->orientamento)) != 0) {
                // Ritorna l'indice della tessera trovata
                return elemento_ad_indice(mano_giocatore, tessera);
            }
        }
    // Ripeti questo per le posizioni in verticale (0) e in orizzontale (1)
    } while(!risultato->orientamento++);
    // Nel caso in cui fossero rimaste tessere speciali
    if(risultato->speciali > 0) {
        // Posiziona la prima tessera speciale disponibile
        return elemento_ad_indice(mano_giocatore, mano_giocatore->dimensione - (risultato->speciali);
    }
    // Non ho trovato nessuna tessera da posizionare
    return NULL;
}