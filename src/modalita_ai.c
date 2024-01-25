#include "../lib/modalita_ai.h"

#include <stdio.h>
#include <string.h>

#include "../lib/tessera.h"
#include "../lib/controlli.h"

void esegui_algoritmo(matrice_t *piano_gioco, vect_t *mano_giocatore) {
    // Crea la combinazione dentro cui salvare il risultato delle operazioni
    comb_t *risultato = crea_combinazione((coord_t) {0, 0}, false);
    // Tessera da prelevare durante ciascun turno
    tessera_t *da_inserire;
    // Continua la partita finche' sono disponbili tessere da posizionare
    while((da_inserire = first_match(piano_gioco, mano_giocatore, risultato)) != NULL) {
        // Stampa le tessere rimaste nella mano del giocatore
        stampa_mano(mano_giocatore);
        printf("Ho deciso di posizionare la tessera [%u|%u]\n", da_inserire->sinistro, da_inserire->destro);
        // In caso di tessera speciale esegui le operazioni opportune
        if(da_inserire->speciale) {
            funzionalita_aggiuntive(piano_gioco, da_inserire, risultato);
        }
        // Esegui l'inserimento della tessera sul piano di gioco
        preleva_tessera(piano_gioco, mano_giocatore, da_inserire, risultato->inserimento, risultato);
        // Inizializza i parametri per eseguire i controlli
        inizializza_combinazione(risultato);
        // Stampa lo stato corrente del piano di gioco
        stampa_piano(piano_gioco);
    }
}

tessera_t *first_match(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato) {
    // Termina la partita dopo aver esaurite le tessere
    if(mano_giocatore->dimensione == 0) return NULL;
    do {
        // Calcola tutte le coordinate in cui e' possibile posizionare una tessera
        vect_t *coordinate = calcola_coordinate(piano_gioco, risultato->orientamento);
        // Per ciascuna tessera nella mano del giocatore
        for (size_t i=0; i < mano_giocatore->dimensione; i++) {
            // Memorizza l'indirizzo della tessera corrente
            tessera_t *tessera = elemento_ad_indice(mano_giocatore, i);
            // Per ciascuna posizione valida fornita
            for(size_t j=0; j<coordinate->dimensione; j++) {
                // Se una delle posizioni fornite permette l'inserimento della tessera
                if (mossa_legale(piano_gioco, elemento_ad_indice(coordinate, j), tessera, risultato)) {
                    // Aggiorna la nuova posizione di inserimento
                    risultato->inserimento = elemento_ad_indice(coordinate, j);
                    // Ritorna l'indirizzo della tessera trovata
                    return tessera;
                }
            }
        }
        // Libera la memoria allocata
        libera_vettore(coordinate);
    // Ripeti per le posizioni in verticale (0) e in orizzontale (1)
    } while(!risultato->orientamento++);
    // Non ho trovato nessuna tessera da posizionare
    return NULL;
}
